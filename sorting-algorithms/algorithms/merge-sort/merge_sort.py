"""Merge Sort - Python implementation.

Returns a NEW sorted list; the input is never modified.
Time: O(n log n) in all cases.  Space: O(n) extra.  Stable: yes.
"""


def _merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        # "<=" (not "<") keeps equal elements in original order -> stable
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result


def merge_sort(arr):
    a = list(arr)
    if len(a) <= 1:
        return a
    mid = len(a) // 2
    return _merge(merge_sort(a[:mid]), merge_sort(a[mid:]))


if __name__ == "__main__":
    print(merge_sort([5, 2, 9, 1, 5, 6]))  # [1, 2, 5, 5, 6, 9]
