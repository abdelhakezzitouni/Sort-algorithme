#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stddef.h>

/* Sorts arr[0..n-1] in place, ascending. O(n log n) time, O(n) extra space,
 * stable. Returns 0 on success, -1 if the temporary buffer cannot be
 * allocated (the array is then left untouched). */
int merge_sort(int arr[], size_t n);

#endif
