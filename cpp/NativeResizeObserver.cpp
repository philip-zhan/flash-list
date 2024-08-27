#include "NativeResizeObserver.h"
#include <chrono>
#include <react/renderer/core/ShadowNode.h>
#include <react/renderer/uimanager/UIManagerBinding.h>
#include <react/renderer/uimanager/primitives.h>

struct DOMRect {
  double x = 0;
  double y = 0;
  double width = 0;
  double height = 0;
};

namespace facebook::react {

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

void NativeResizeObserver::registerBoundsChangeCallback(jsi::Runtime& rt, jsi::Object target, jsi::Function callback) {
  auto& uiManager = getUIManagerFromRuntime(rt);
  auto shadowNode = shadowNodeFromValue(rt, std::move(target));
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

void NativeResizeObserver::unregisterBoundsChangeCallback(jsi::Runtime& rt, jsi::Object target) {
	auto shadowNode = shadowNodeFromValue(rt, std::move(target));
	auto tag = shadowNode->getTag();
	auto it = observedNodes_.find(tag);
	if (it != observedNodes_.end()) {
		observedNodes_.erase(it);
		callbacks_.erase(tag);

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

				PropsParserContext propsParserContext{
					newRootShadowNode->getSurfaceId(), *newRootShadowNode->getContextContainer()};
//				auto cloneNewRoot = newRootShadowNode->clone(propsParserContext,
//															 newRootShadowNode->getConcreteProps().layoutConstraints,
//															 newRootShadowNode->getConcreteProps().layoutContext);

				auto oldNode = getShadowNodeInRevision(oldRootShadowNode, *shadowNode);
				auto newNode = getShadowNodeInRevision(newRootShadowNode, *shadowNode);
				
				std::vector<const LayoutableShadowNode*> affectedLayoutableNodes{};
				affectedLayoutableNodes.reserve(1024);
				
				newRootShadowNode->layoutIfNeeded(&affectedLayoutableNodes);

				bool isSameNode = (oldNode == newNode);
				if (newNode) {
					auto layoutableNewNode = dynamic_cast<const YogaLayoutableShadowNode*>(newNode.get());
					if (layoutableNewNode) {
						auto isClean = layoutableNewNode->getIsLayoutClean();
						auto measurements = layoutableNewNode->measure(newRootShadowNode->getConcreteProps().layoutContext, newRootShadowNode->getConcreteProps().layoutConstraints);
//						auto cloneNewNode = dynamic_cast<const YogaLayoutableShadowNode*>(layoutableNewNode->clone({}).get());
//						cloneNewNode->layoutTree
						// Now you can use layoutableNewNode for layout-related operations
						// For example: layoutableNewNode->getLayoutMetrics();
						// Use layoutableNewNode here
					}
				}

				auto newRect = getBoundingClientRect(newRootShadowNode, *shadowNode, false);

				if (true) {
					for (const auto& [callback, runtime] : callbacks_[tag]) {
						auto oldRectObject = jsi::Object(*runtime);
						auto newRectObject = jsi::Object(*runtime);

						oldRectObject.setProperty(*runtime, "width", jsi::Value(oldRect.width));
						oldRectObject.setProperty(*runtime, "height", jsi::Value(oldRect.height));
						oldRectObject.setProperty(*runtime, "x", jsi::Value(oldRect.x));
						oldRectObject.setProperty(*runtime, "y", jsi::Value(oldRect.y));

						newRectObject.setProperty(*runtime, "width", jsi::Value(newRect.width));
						newRectObject.setProperty(*runtime, "height", jsi::Value(newRect.height));
						newRectObject.setProperty(*runtime, "x", jsi::Value(newRect.x));
						newRectObject.setProperty(*runtime, "y", jsi::Value(newRect.y));

						auto value = jsi::Object(*runtime);
						value.setProperty(*runtime, "oldRect", oldRectObject);
						value.setProperty(*runtime, "newRect", newRectObject);

						auto result = callback.call(*runtime, std::move(value));
						if (shouldCommit && result.isBool() && !result.asBool()) {
							shouldCommit = false;
						}
					}
				}
			} } catch (const std::exception& e) {
	  // Log the error, but don't crash
	  // You might want to use a proper logging mechanism here
				printf("Error");
	  //vbvcstd::cerr << "Error in resize observer callback: " << e.what() << std::endl;
	}

  return shouldCommit ? newRootShadowNode : nullptr;
}

} // namespace facebook::react
