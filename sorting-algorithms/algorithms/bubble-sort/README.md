# Bubble Sort

## Idea

Repeatedly walk through the array, comparing each pair of neighbours and swapping
them if they are in the wrong order. After each full pass the largest remaining
element has "bubbled up" to its final position at the end.

Example on `[5, 2, 9, 1]`:

```
pass 1: [5,2,9,1] -> [2,5,9,1] -> [2,5,9,1] -> [2,5,1,9]     (9 is in place)
pass 2: [2,5,1,9] -> [2,5,1,9] -> [2,1,5,9]                   (5 is in place)
pass 3: [2,1,5,9] -> [1,2,5,9]                                (sorted)
```

## Pseudocode

```
BUBBLE-SORT(A, n):
    for i = 0 to n-2:
        swapped = false
        for j = 0 to n-2-i:
            if A[j] > A[j+1]:
                swap A[j], A[j+1]
                swapped = true
        if not swapped: return          // early exit: already sorted
```

## Correctness (loop invariant)

**Invariant of the outer loop:** after `i` passes, the last `i` positions of the
array hold the `i` largest elements, in sorted order.

- *Initialization* (`i = 0`): the claim is about zero elements, so it is trivially true.
- *Maintenance:* during a pass, whenever the inner loop compares `A[j]` and `A[j+1]`,
  the larger of the two is moved to position `j+1`. By induction on `j`, the
  maximum of the unsorted prefix is carried all the way to its end. This element
  is ≥ everything before it and ≤ everything already placed after it, so it is in
  its final position; the invariant holds for `i + 1`.
- *Termination:* after `n - 1` passes the last `n - 1` positions are correct, and
  the single remaining element must also be correct. The early exit is valid
  because a pass with no swap means every neighbouring pair is ordered, i.e. the
  array is sorted.

## Complexity

The number of comparisons in the worst case is

```
(n-1) + (n-2) + ... + 1 = n(n-1)/2 = Θ(n²)
```

| Case | Time | Why |
|------|------|-----|
| Best | O(n) | already sorted: one pass, no swap, early exit |
| Average / Worst | O(n²) | roughly n²/2 comparisons (and up to n²/2 swaps on reversed input) |
| Space | O(1) | only a few variables |

**Stable:** yes, because we only swap when `A[j] > A[j+1]` (strictly greater).
**In place:** yes.

## When to use it

Almost never in production. It is taught because it is simple and because it
introduces invariants, early exit and complexity analysis. Prefer
[Merge Sort](../merge-sort/README.md) or [Quick Sort](../quick-sort/README.md).

## Exercises

1. Prove that the number of swaps equals the number of *inversions* in the array
   (pairs `i < j` with `A[i] > A[j]`).
2. Implement *Cocktail Shaker Sort* (bubble in both directions). Does it improve
   the worst case?
3. Remember the position of the last swap in each pass and shrink the inner loop
   to it. Measure the improvement with the benchmark.
