/**
 * Quick Sort - JavaScript implementation (random pivot, 3-way partition).
 *
 * Returns a NEW sorted array; the input is never modified.
 * Time: O(n log n) expected, O(n^2) worst (very unlikely with a random pivot).
 * Space: O(log n) stack.  Stable: no.
 */
function quick(a, lo, hi) {
  while (lo < hi) {
    const pivot = a[lo + Math.floor(Math.random() * (hi - lo + 1))];
    let lt = lo;
    let i = lo;
    let gt = hi;
    // invariant: a[lo..lt-1] < pivot, a[lt..i-1] == pivot, a[gt+1..hi] > pivot
    while (i <= gt) {
      if (a[i] < pivot) {
        [a[lt], a[i]] = [a[i], a[lt]];
        lt++;
        i++;
      } else if (a[i] > pivot) {
        [a[i], a[gt]] = [a[gt], a[i]];
        gt--;
      } else {
        i++;
      }
    }
    // a[lt..gt] are all equal to pivot: already in final position
    if (lt - lo < hi - gt) { // recurse on the smaller side, loop on the larger
      quick(a, lo, lt - 1);
      lo = gt + 1;
    } else {
      quick(a, gt + 1, hi);
      hi = lt - 1;
    }
  }
}

function quickSort(arr) {
  const a = [...arr];
  quick(a, 0, a.length - 1);
  return a;
}

module.exports = { quickSort };

if (require.main === module) {
  console.log(quickSort([5, 2, 9, 1, 5, 6])); // [1, 2, 5, 5, 6, 9]
}
