import type { TurboModule } from "react-native";
import { TurboModuleRegistry } from "react-native";

interface DOMRect {
  x: number;
  y: number;
  width: number;
  height: number;
}

interface Params {
  oldRect: DOMRect;
  newRect: DOMRect;
}

export interface Spec extends TurboModule {
  /**
   * Register a callback to be invoked when the bounds of the target change.
   * Return a boolean to indicate if the render should continue.
   */
  readonly registerBoundsChangeCallback: (
    target: unknown,
    callback: (params: Params) => boolean
  ) => void;
  readonly unregisterBoundsChangeCallback: (target: unknown) => void;
}

export default TurboModuleRegistry.getEnforcing<Spec>("NativeResizeObserver");
