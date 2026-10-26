# Merge Sort

## Idea

A **divide and conquer** algorithm:

1. **Divide** the array into two halves.
2. **Conquer** by sorting each half recursively.
3. **Combine** by *merging* the two sorted halves into one sorted array.

```
[38, 27, 43, 3]
   /          \
[38, 27]    [43, 3]
 /    \      /    \
[38] [27]  [43]  [3]
 \    /      \    /
[27, 38]    [3, 43]
   \          /
[3, 27, 38, 43]
```

The merge step walks through both sorted halves with two pointers, always
taking the smaller front element.

## Pseudocode

```
MERGE-SORT(A):
    if length(A) <= 1: return A
    mid = length(A) / 2
    L = MERGE-SORT(A[0 .. mid))
    R = MERGE-SORT(A[mid .. end))
    return MERGE(L, R)

MERGE(L, R):
    result = []; i = 0; j = 0
    while i < |L| and j < |R|:
        if L[i] <= R[j]: append L[i++] to result
        else:            append R[j++] to result
    append the remaining elements of L and R
    return result
```

## Correctness

*Merge:* **invariant** — at the start of each iteration, `result` contains the
`i + j` smallest elements of `L ∪ R` in sorted order. Each step appends the
smaller of the two front elements, which is the smallest element not yet used
(because `L` and `R` are sorted), so the invariant is preserved. When one list is
exhausted, the rest of the other is already sorted and ≥ everything in `result`.

*Merge sort:* by **strong induction on n**. Arrays of size 0 or 1 are sorted. For
`n ≥ 2`, both halves are smaller, so by the induction hypothesis they are
returned sorted; merging two sorted arrays gives a sorted array.

## Complexity

The recurrence for the running time is

```
T(n) = 2·T(n/2) + Θ(n)
```

**Recursion tree argument:** level `k` of the tree has `2^k` subproblems of size
`n / 2^k`, so the merge work on that level is `2^k · c·n/2^k = c·n`. The tree has
`log₂ n + 1` levels, therefore

```
T(n) = c·n·(log₂ n + 1) = Θ(n log n)
```

This also follows from the **Master Theorem** (case 2: `a = 2, b = 2, f(n) = Θ(n)`).

| Case | Time |
|------|------|
| Best / Average / Worst | Θ(n log n) |
| Extra space | O(n) for the merge buffer |

**Stable:** yes (the merge takes from the left half on ties: `<=`).
**In place:** no.

## Implementation notes

- **Python / JS:** each call returns a new array (simple and clear, but allocates a lot).
- **C:** allocates a single scratch buffer of size `n` once, sorts the half-open
  range `[lo, hi)` in place, and returns `0` / `-1` depending on whether the
  allocation succeeded. `mid = lo + (hi - lo) / 2` avoids integer overflow.

## When to use it

When you need guaranteed O(n log n), stability, or you sort linked lists or data
that does not fit in memory (external sorting).

## Exercises

1. Write a **bottom-up** (iterative) version that merges runs of size 1, 2, 4, …
2. Count the **inversions** of an array in O(n log n) by modifying the merge step.
3. Switch to Insertion Sort for sub-arrays smaller than ~16 elements and benchmark it.
