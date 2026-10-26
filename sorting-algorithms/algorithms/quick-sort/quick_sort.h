#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>

/* Sorts arr[0..n-1] in place, ascending. O(n log n) expected time,
 * O(log n) stack, not stable. Random pivot + 3-way partition. */
void quick_sort(int arr[], size_t n);

#endif
