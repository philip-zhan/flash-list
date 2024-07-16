import { RVDimension, RVLayoutManager } from "./LayoutManager";
import { RecycleKeyManagerImpl, RecycleKeyManager } from "./RecycleKeyManager";
import {
  RVViewabilityManager,
  RVViewabilityManagerImpl,
} from "./ViewabilityManager";

export class RecyclerViewManager {
  INITIAL_NUM_TO_RENDER = 10;
  private viewabilityManager: RVViewabilityManager;
  private recycleKeyManager: RecycleKeyManager;
  private layoutManager: RVLayoutManager;
  private windowSize: RVDimension;
  // Map of index to key
  private renderStack: Map<number, string> = new Map();

  constructor() {
    this.viewabilityManager = new RVViewabilityManagerImpl();
    this.viewabilityManager.setOnEngagedIndicesChangedListener(
      this.updateRenderStack
    );
    this.recycleKeyManager = new RecycleKeyManagerImpl();
  }

  // updates render stack based on the engaged indices which are sorted. Recycles unused keys.
  // TODO: Call getKey anyway if stableIds are present
  private updateRenderStack = (engagedIndices: number[]): void => {
    for (const [index, key] of this.renderStack) {
      if (!engagedIndices.includes(index)) {
        this.recycleKeyManager.recycleKey(key);
      }
    }
    const newRenderStack = new Map<number, string>();
    for (const index of engagedIndices) {
      const key = this.renderStack.get(index);
      if (key) {
        newRenderStack.set(index, key);
      } else {
        const newKey = this.recycleKeyManager.getKey("type1");
        newRenderStack.set(index, newKey);
      }
    }
    // DANGER
    for (const [index, key] of this.renderStack) {
      if (this.recycleKeyManager.hasKeyInPool(key)) {
        newRenderStack.set(index, key);
      }
    }

    this.renderStack = newRenderStack;
  };

  updateLayoutManager(layoutManager: RVLayoutManager, windowSize: RVDimension) {
    this.layoutManager = layoutManager;
    this.windowSize = windowSize;
  }

  updateScrollOffset(offset: number) {
    this.viewabilityManager.updateScrollOffset(
      offset,
      this.layoutManager,
      this.windowSize
    );
  }

  getLayout(index: number) {
    return this.layoutManager.getLayout(index);
  }

  getRenderStack() {
    return this.renderStack;
  }
}