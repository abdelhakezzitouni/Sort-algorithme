/**
 * Bubble Sort - JavaScript implementation.
 *
 * Returns a NEW sorted array; the input is never modified.
 * Time: O(n^2) worst/average, O(n) best (already sorted).  Space: O(1) extra.
 * Stable: yes.
 */
function bubbleSort(arr) {
  const a = [...arr]; // work on a copy
  const n = a.length;
  for (let i = 0; i < n - 1; i++) {
    let swapped = false;
    // after pass i, the last i elements are already in their final place
    for (let j = 0; j < n - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        [a[j], a[j + 1]] = [a[j + 1], a[j]];
        swapped = true;
      }
    }
    if (!swapped) break; // no swap in a full pass -> already sorted
  }
  return a;
}

module.exports = { bubbleSort };

if (require.main === module) {
  console.log(bubbleSort([5, 2, 9, 1, 5, 6])); // [1, 2, 5, 5, 6, 9]
}
