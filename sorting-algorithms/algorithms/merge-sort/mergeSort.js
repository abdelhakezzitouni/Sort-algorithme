/**
 * Merge Sort - JavaScript implementation.
 *
 * Returns a NEW sorted array; the input is never modified.
 * Time: O(n log n) in all cases.  Space: O(n) extra.  Stable: yes.
 */
function merge(left, right) {
  const result = [];
  let i = 0;
  let j = 0;
  while (i < left.length && j < right.length) {
    // "<=" (not "<") keeps equal elements in original order -> stable
    if (left[i] <= right[j]) result.push(left[i++]);
    else result.push(right[j++]);
  }
  while (i < left.length) result.push(left[i++]);
  while (j < right.length) result.push(right[j++]);
  return result;
}

function mergeSort(arr) {
  if (arr.length <= 1) return [...arr];
  const mid = Math.floor(arr.length / 2);
  return merge(mergeSort(arr.slice(0, mid)), mergeSort(arr.slice(mid)));
}

module.exports = { mergeSort };

if (require.main === module) {
  console.log(mergeSort([5, 2, 9, 1, 5, 6])); // [1, 2, 5, 5, 6, 9]
}
