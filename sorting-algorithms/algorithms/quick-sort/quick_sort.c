#include "quick_sort.h"
#include <stdlib.h>

static void quick_range(int *a, long lo, long hi) {
    while (lo < hi) {
        int pivot = a[lo + rand() % (hi - lo + 1)];
        long lt = lo, i = lo, gt = hi;
        /* invariant: a[lo..lt-1] < pivot, a[lt..i-1] == pivot, a[gt+1..hi] > pivot */
        while (i <= gt) {
            if (a[i] < pivot) {
                int t = a[lt]; a[lt] = a[i]; a[i] = t;
                lt++; i++;
            } else if (a[i] > pivot) {
                int t = a[i]; a[i] = a[gt]; a[gt] = t;
                gt--;
            } else {
                i++;
            }
        }
        /* a[lt..gt] are all equal to pivot: already in final position */
        if (lt - lo < hi - gt) { /* recurse on the smaller side, loop on the larger */
            quick_range(a, lo, lt - 1);
            lo = gt + 1;
        } else {
            quick_range(a, gt + 1, hi);
            hi = lt - 1;
        }
    }
}

void quick_sort(int arr[], size_t n) {
    if (n < 2) return;
    quick_range(arr, 0, (long)n - 1);
}
