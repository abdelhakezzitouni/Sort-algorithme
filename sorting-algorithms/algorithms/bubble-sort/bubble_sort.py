"""Bubble Sort - Python implementation.

Returns a NEW sorted list; the input is never modified.
Time: O(n^2) worst/average, O(n) best (already sorted).  Space: O(1) extra.
Stable: yes.
"""


def bubble_sort(arr):
    a = list(arr)  # work on a copy
    n = len(a)
    for i in range(n - 1):
        swapped = False
        # after pass i, the last i elements are already in their final place
        for j in range(n - 1 - i):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swapped = True
        if not swapped:  # no swap in a full pass -> already sorted
            break
    return a


if __name__ == "__main__":
    print(bubble_sort([5, 2, 9, 1, 5, 6]))  # [1, 2, 5, 5, 6, 9]
