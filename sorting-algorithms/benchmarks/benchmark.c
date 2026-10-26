/* Benchmark the C implementations. Build & run with:  make bench-c
 * Uses only standard C (clock) so it also builds on Windows/MinGW. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

#define REPS 20 /* repeat each sort and average: clock() is coarse for fast sorts */

static void merge_wrapper(int a[], size_t n) { merge_sort(a, n); }

typedef void (*sort_fn)(int[], size_t);

static double time_ms(sort_fn fn, const int *data, size_t n) {
    int *copy = malloc(n * sizeof(int));
    clock_t total = 0;
    for (int r = 0; r < REPS; r++) {
        memcpy(copy, data, n * sizeof(int)); /* copying is not timed */
        clock_t start = clock();
        fn(copy, n);
        total += clock() - start;
    }
    free(copy);
    return (double)total / CLOCKS_PER_SEC * 1000.0 / REPS;
}

int main(void) {
    const size_t sizes[] = {1000, 2000, 5000, 10000};
    sort_fn fns[] = {bubble_sort, merge_wrapper, quick_sort};

    printf("| n | bubble (ms) | merge (ms) | quick (ms) |\n|---|---|---|---|\n");
    for (size_t s = 0; s < sizeof(sizes) / sizeof(sizes[0]); s++) {
        size_t n = sizes[s];
        int *data = malloc(n * sizeof(int));
        for (size_t i = 0; i < n; i++) data[i] = rand() % 1000001;
        printf("| %zu |", n);
        for (int f = 0; f < 3; f++) printf(" %.3f |", time_ms(fns[f], data, n));
        printf("\n");
        free(data);
    }
    return 0;
}
