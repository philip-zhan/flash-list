import { useLayoutEffect, useState } from "react";

import { RecyclerViewManager } from "../RecyclerVIewManager";

export function useContentOffsetManagement(
  recyclerViewManager: RecyclerViewManager
) {
  const [contentOffset, setContentOffset] = useState({ x: 0, y: 0 });
  const firstVisibleItem = recyclerViewManager.getLayoutManager()
    ? recyclerViewManager.getVisibleIndices()[0]
    : 0;

  // eslint-disable-next-line react-hooks/exhaustive-deps
  const firstVisibleItemLayout = recyclerViewManager.getLayoutManager()
    ? {
        ...recyclerViewManager.getLayout(firstVisibleItem),
      }
    : undefined;

  //const firstVisibleItemKey = recyclerViewManager.getStableId(firstVisibleItem);

  useLayoutEffect(() => {
    if (!firstVisibleItemLayout) return;
    const newLayout = recyclerViewManager.getLayout(firstVisibleItem);
    if (newLayout.y !== firstVisibleItemLayout.y) {
      setContentOffset({
        x: 0,
        y:
          recyclerViewManager.getLastScrollOffset() +
          (newLayout.y - firstVisibleItemLayout.y),
      });
    }
  }, [firstVisibleItem, firstVisibleItemLayout, recyclerViewManager]);
  console.log("ContentOffset", contentOffset);
  return contentOffset;
}

/**
 * Not scrolling and something resize
 * check for change in first visible item
 *
 * Not scrolling and data is changed
 * key extractor required
 *
 * scrolling while resizing
 *
 * scrolling while data is changed
 * key extractor required

 */
