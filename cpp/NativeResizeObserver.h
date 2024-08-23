#pragma once

#if __has_include(<React-Codegen/rnflashlistJSI.h>) // CocoaPod headers on Apple
#include <React-Codegen/rnflashlistJSI.h>
#elif __has_include("rnflashlistJSI.h") // CMake headers on Android
#include "rnflashlistJSI.h"
#endif
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <react/renderer/core/ShadowNode.h>
#include <react/renderer/uimanager/UIManagerBinding.h>
#include <react/renderer/uimanager/primitives.h>
#include <react/renderer/uimanager/UIManagerCommitHook.h>
#include <react/renderer/uimanager/UIManager.h>
#include <react/renderer/core/LayoutableShadowNode.h>

namespace facebook::react {

class NativeResizeObserver : public NativeResizeObserverCxxSpec<NativeResizeObserver>, public UIManagerCommitHook {
 public:
  NativeResizeObserver(std::shared_ptr<CallInvoker> jsInvoker);

  void registerBoundsChangeCallback(jsi::Runtime& rt, double target, jsi::Function callback);
  void unregisterBoundsChangeCallback(jsi::Runtime& rt, double target);

  #pragma mark - UIManagerCommitHook

  void commitHookWasRegistered(const UIManager& uiManager) noexcept override;
  void commitHookWasUnregistered(const UIManager& uiManager) noexcept override;

  RootShadowNode::Unshared shadowTreeWillCommit(
	  const ShadowTree& shadowTree,
	  const RootShadowNode::Shared& oldRootShadowNode,
	  const RootShadowNode::Unshared& newRootShadowNode) noexcept override;

 private:
	jsi::Runtime* runtime_;
  std::unordered_map<Tag, ShadowNode::Shared> observedNodes_;
  std::unordered_map<Tag, std::vector<std::pair<jsi::Function, jsi::Runtime*>>> callbacks_;
  bool isHookRegistered_ = false;
};

}; // namespace facebook::react
