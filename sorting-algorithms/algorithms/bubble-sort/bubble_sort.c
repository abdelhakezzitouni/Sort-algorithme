#include "bubble_sort.h"
#include <stdbool.h>

void bubble_sort(int arr[], size_t n) {
    if (n < 2) return;
    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;
        /* after pass i, the last i elements are already in their final place */
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break; /* no swap in a full pass -> already sorted */
    }
}
