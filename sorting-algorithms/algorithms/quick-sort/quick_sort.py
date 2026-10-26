"""Quick Sort - Python implementation (random pivot, 3-way partition).

Returns a NEW sorted list; the input is never modified.
Time: O(n log n) expected, O(n^2) worst (very unlikely with a random pivot).
Space: O(log n) stack.  Stable: no.

The 3-way (Dutch national flag) partition makes arrays with many duplicates
fast, and recursing only on the smaller side keeps the stack depth O(log n).
"""
import random


def _quick(a, lo, hi):
    while lo < hi:
        pivot = a[random.randint(lo, hi)]
        lt, i, gt = lo, lo, hi
        # invariant: a[lo:lt] < pivot, a[lt:i] == pivot, a[gt+1:hi+1] > pivot
        while i <= gt:
            if a[i] < pivot:
                a[lt], a[i] = a[i], a[lt]
                lt += 1
                i += 1
            elif a[i] > pivot:
                a[i], a[gt] = a[gt], a[i]
                gt -= 1
            else:
                i += 1
        # a[lt..gt] are all equal to pivot: already in final position
        if lt - lo < hi - gt:  # recurse on the smaller side, loop on the larger
            _quick(a, lo, lt - 1)
            lo = gt + 1
        else:
            _quick(a, gt + 1, hi)
            hi = lt - 1


def quick_sort(arr):
    a = list(arr)
    _quick(a, 0, len(a) - 1)
    return a


if __name__ == "__main__":
    print(quick_sort([5, 2, 9, 1, 5, 6]))  # [1, 2, 5, 5, 6, 9]
