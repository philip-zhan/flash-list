#include "NativeResizeObserver.h"
#include <chrono>
#include <react/renderer/core/ShadowNode.h>
#include <react/renderer/uimanager/UIManagerBinding.h>
#include <react/renderer/uimanager/primitives.h>
#include <react/renderer/components/view/YogaLayoutableShadowNode.h>
#include <yoga/YGNode.h>

struct DOMRect {
  double x = 0;
  double y = 0;
  double width = 0;
  double height = 0;
};

namespace facebook::react {

static ShadowNode* getShadowNodeInRevisionUnshared(const RootShadowNode::Unshared& currentRevision, Tag tag) {
	auto currentRootChildren = currentRevision->getChildren();

	// Helper function to recursively search for the node
	std::function<ShadowNode*(const ShadowNode::ListOfShared&)> findNode;
	findNode = [&](const ShadowNode::ListOfShared& children) -> ShadowNode* {
		for (const auto& child : children) {
			if (child->getTag() == tag) {
				// We found the node, return a non-const pointer
				return const_cast<ShadowNode*>(child.get());
			}
			// If this node has children, search them
			if (child->getChildren().size() > 0) {
				auto result = findNode(child->getChildren());
				if (result != nullptr) {
					return result;
				}
			}
		}
		return nullptr;
	};

	return findNode(currentRootChildren);
}

static ShadowNode::Shared getShadowNodeInRevision(
	const RootShadowNode::Shared& currentRevision,
	const ShadowNode& shadowNode) {
  if (ShadowNode::sameFamily(*currentRevision, shadowNode)) {
	return currentRevision;
  }

  auto ancestors = shadowNode.getFamily().getAncestors(*currentRevision);

  if (ancestors.empty()) {
	return nullptr;
  }

  auto pair = ancestors.rbegin();
  return pair->first.get().getChildren().at(pair->second);
}

static UIManager& getUIManagerFromRuntime(jsi::Runtime& runtime) {
  return UIManagerBinding::getBinding(runtime)->getUIManager();
}

static LayoutMetrics getRelativeLayoutMetrics(
	const ShadowNode& ancestorNode,
	const ShadowNode& shadowNode,
	LayoutableShadowNode::LayoutInspectingPolicy policy) {
  auto layoutableAncestorShadowNode =
	  dynamic_cast<const LayoutableShadowNode*>(&ancestorNode);

  if (layoutableAncestorShadowNode == nullptr) {
	return EmptyLayoutMetrics;
  }

  return LayoutableShadowNode::computeRelativeLayoutMetrics(
	  shadowNode.getFamily(), *layoutableAncestorShadowNode, policy);
}

static DOMRect getBoundingClientRect(
	const RootShadowNode::Shared& currentRevision,
	const ShadowNode& shadowNode,
	bool includeTransform) {
  auto shadowNodeInCurrentRevision =
	  getShadowNodeInRevision(currentRevision, shadowNode);
  if (shadowNodeInCurrentRevision == nullptr) {
	return DOMRect{};
  }

  auto layoutMetrics = getRelativeLayoutMetrics(
	  *currentRevision,
	  shadowNode,
	  {.includeTransform = includeTransform, .includeViewportOffset = true});

  if (layoutMetrics == EmptyLayoutMetrics) {
	return DOMRect{};
  }

  auto frame = layoutMetrics.frame;
  return DOMRect{
	  .x = frame.origin.x,
	  .y = frame.origin.y,
	  .width = frame.size.width,
	  .height = frame.size.height};
}

NativeResizeObserver::NativeResizeObserver(std::shared_ptr<CallInvoker> jsInvoker)
	: NativeResizeObserverCxxSpec(std::move(jsInvoker)) {}

void NativeResizeObserver::registerBoundsChangeCallback(jsi::Runtime& rt, double target, jsi::Function callback) {
  auto& uiManager = getUIManagerFromRuntime(rt);
  auto shadowNode = uiManager.findShadowNodeByTag_DEPRECATED(target);
	runtime_=&rt;

  if (shadowNode) {
	auto tag = shadowNode->getTag();
	callbacks_[tag].push_back(std::make_pair(std::move(callback), &rt));

	if (observedNodes_.find(tag) == observedNodes_.end()) {
	  observedNodes_[tag] = shadowNode;
	  if (!isHookRegistered_) {
		uiManager.registerCommitHook(*this);
		isHookRegistered_ = true;
	  }
	}
  }
}

void NativeResizeObserver::unregisterBoundsChangeCallback(jsi::Runtime& rt, double target) {
  auto it = observedNodes_.find(target);
  if (it != observedNodes_.end()) {
	observedNodes_.erase(it);
	callbacks_.erase(target);

	if (observedNodes_.empty() && isHookRegistered_) {
	  getUIManagerFromRuntime(rt).unregisterCommitHook(*this);
	  isHookRegistered_ = false;
	}
  }
}

void NativeResizeObserver::commitHookWasRegistered(const UIManager& uiManager) noexcept {}
void NativeResizeObserver::commitHookWasUnregistered(const UIManager& uiManager) noexcept {}

RootShadowNode::Unshared NativeResizeObserver::shadowTreeWillCommit(
	const ShadowTree& shadowTree,
	const RootShadowNode::Shared& oldRootShadowNode,
	const RootShadowNode::Unshared& newRootShadowNode) noexcept {

  bool shouldCommit = true;

		try {
			for (const auto& [tag, shadowNode] : observedNodes_) {
				auto oldRect = getBoundingClientRect(oldRootShadowNode, *shadowNode, false);
				
				auto newNode = getShadowNodeInRevisionUnshared(newRootShadowNode, shadowNode->getTag());
				
				if (newNode) {
					auto layoutableNewNode = dynamic_cast<YogaLayoutableShadowNode*>(newNode);
					if (layoutableNewNode) {
						// Calculate the layout on the cloned node
						if (!layoutableNewNode->getIsLayoutClean()) {
							layoutableNewNode->layoutTree(newRootShadowNode->getConcreteProps().layoutContext, newRootShadowNode->getConcreteProps().layoutConstraints);
							
							// Get the layout metrics from the cloned node
							auto layoutMetrics = layoutableNewNode->getLayoutMetrics();
							
							for (const auto& [callback, runtime] : callbacks_[tag]) {
								auto oldRectObject = jsi::Object(*runtime);
								auto newRectObject = jsi::Object(*runtime);
								
								oldRectObject.setProperty(*runtime, "width", jsi::Value(oldRect.width));
								oldRectObject.setProperty(*runtime, "height", jsi::Value(oldRect.height));
								oldRectObject.setProperty(*runtime, "x", jsi::Value(oldRect.x));
								oldRectObject.setProperty(*runtime, "y", jsi::Value(oldRect.y));
								
								newRectObject.setProperty(*runtime, "width", jsi::Value(layoutMetrics.frame.size.width));
								newRectObject.setProperty(*runtime, "height", jsi::Value(layoutMetrics.frame.size.height));
								newRectObject.setProperty(*runtime, "x", jsi::Value(layoutMetrics.frame.origin.x));
								newRectObject.setProperty(*runtime, "y", jsi::Value(layoutMetrics.frame.origin.y));
								
								auto value = jsi::Object(*runtime);
								value.setProperty(*runtime, "oldRect", oldRectObject);
								value.setProperty(*runtime, "newRect", newRectObject);
								
								auto result = callback.call(*runtime, std::move(value));
								if (shouldCommit && result.isBool() && !result.asBool()) {
									shouldCommit = false;
									break;
								}
							}
						}
					}
				}
			}
		} catch (const std::exception& e) {
	  // Log the error, but don't crash
	  // You might want to use a proper logging mechanism here
				printf("Error");
	  //vbvcstd::cerr << "Error in resize observer callback: " << e.what() << std::endl;
	}

  return shouldCommit ? newRootShadowNode : nullptr;
}

} // namespace facebook::react
