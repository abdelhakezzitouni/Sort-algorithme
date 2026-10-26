#include "merge_sort.h"
#include <stdlib.h>
#include <string.h>

/* Sorts the half-open range [lo, hi) using tmp as scratch space. */
static void sort_range(int *a, int *tmp, size_t lo, size_t hi) {
    if (hi - lo < 2) return;

    size_t mid = lo + (hi - lo) / 2; /* avoids overflow of (lo + hi) */
    sort_range(a, tmp, lo, mid);
    sort_range(a, tmp, mid, hi);

    size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        /* "<=" keeps equal elements in original order -> stable */
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < hi)  tmp[k++] = a[j++];

    memcpy(a + lo, tmp + lo, (hi - lo) * sizeof(int));
}

int merge_sort(int arr[], size_t n) {
    if (n < 2) return 0;
    int *tmp = malloc(n * sizeof(int));
    if (tmp == NULL) return -1;
    sort_range(arr, tmp, 0, n);
    free(tmp);
    return 0;
}
