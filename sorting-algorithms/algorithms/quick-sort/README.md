# Quick Sort

## Idea

Another **divide and conquer** algorithm, but the work is done *before* the
recursion instead of after:

1. Pick a **pivot** element.
2. **Partition** the array so that elements smaller than the pivot come first,
   elements equal to it are in the middle, and larger ones come last.
3. Recursively sort the "smaller" part and the "larger" part. The "equal" part is
   already in its final position.

```
[7, 2, 9, 4, 7, 1]   pivot = 7
   smaller: [2, 4, 1]   equal: [7, 7]   larger: [9]
```

## Pseudocode (3-way partition, random pivot)

```
QUICK-SORT(A, lo, hi):
    while lo < hi:
        pivot = A[random index in lo..hi]
        lt = lo; i = lo; gt = hi
        while i <= gt:
            if   A[i] < pivot: swap A[lt], A[i]; lt++; i++
            elif A[i] > pivot: swap A[i], A[gt]; gt--
            else:              i++
        // now: A[lo..lt-1] < pivot,  A[lt..gt] == pivot,  A[gt+1..hi] > pivot
        recurse on the SMALLER of the two sides, loop on the larger one
```

This is the *Dutch national flag* partition by Dijkstra. Compared with the
textbook two-way (Lomuto/Hoare) partition it stays fast when many values are
equal, where the simple version degrades to O(n²).

## Correctness

**Partition invariant** (checked at the start of each inner iteration):

```
A[lo..lt-1]  <  pivot
A[lt..i-1]   == pivot
A[i..gt]     unprocessed
A[gt+1..hi]  >  pivot
```

Initially `lt = i = lo` and `gt = hi`, so the first three regions are empty. Each
branch preserves the invariant: a smaller element is swapped to the end of the
"smaller" region; a larger one is swapped to the start of the "larger" region (and
the swapped-in element is still unprocessed, hence `i` does not advance); an equal
one just extends the "equal" region. The loop ends when `i > gt`, leaving no
unprocessed elements.

Quick Sort itself is correct by induction on `n`: after partitioning, every
element of the left part ≤ pivot ≤ every element of the right part, both parts
are strictly smaller than `n` (the pivot is in the middle part, so the parts
shrink by at least 1), and they get sorted recursively.

## Complexity

- **Worst case, Θ(n²):** if every pivot is the minimum or maximum, the sizes are
  `n-1, n-2, …`, giving `n(n-1)/2` comparisons. A random pivot makes this
  astronomically unlikely.
- **Best case, Θ(n log n):** the pivot always splits the array in half
  (`T(n) = 2T(n/2) + Θ(n)`, same as Merge Sort).
- **Expected case, Θ(n log n):** let `z₁ < z₂ < … < zₙ` be the elements in sorted
  order. Elements `zᵢ` and `zⱼ` are compared **iff** one of them is the first
  pivot chosen among `zᵢ, …, zⱼ`. With a uniformly random pivot, this happens with
  probability `2 / (j - i + 1)`. By linearity of expectation:

```
E[comparisons] = Σᵢ<ⱼ 2/(j-i+1)  ≤  2n · Σₖ 1/k  =  2n·Hₙ  ≈  2n·ln n  ≈ 1.39·n·log₂ n
```

| Case | Time |
|------|------|
| Best / Expected | Θ(n log n) |
| Worst | Θ(n²) (very unlikely with a random pivot) |
| Space | O(log n) — we always recurse on the smaller side, so the stack depth is ≤ log₂ n |

**Stable:** no (the partition swaps non-adjacent elements).
**In place:** yes (apart from the recursion stack).

## Why is Quick Sort often faster than Merge Sort?

It has a worse worst case but a better constant factor: it sorts in place, makes
sequential memory accesses and does no allocation. This is why it (or a variant,
like Intro Sort in C++) is the default in many standard libraries.

## Exercises

1. Make the pivot the *median of three* instead of random. Construct an input
   that is bad for it.
2. Add **Intro Sort**: switch to Heap Sort when the recursion depth exceeds `2·log₂ n`.
3. Implement **Quick Select** to find the k-th smallest element in expected O(n).
