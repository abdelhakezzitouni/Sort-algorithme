/* Tests for the C implementations. Build & run with:  make test-c */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bubble_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"

typedef void (*sort_fn)(int[], size_t);

/* merge_sort returns int, so wrap it to fit the common signature */
static void merge_sort_wrapper(int a[], size_t n) {
    int rc = merge_sort(a, n);
    assert(rc == 0);
}

static int cmp_int(const void *x, const void *y) {
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);
}

static int checks = 0;

static void check(const char *algo, const char *name, sort_fn fn, const int *data, size_t n) {
    int *got = malloc((n ? n : 1) * sizeof(int));
    int *expected = malloc((n ? n : 1) * sizeof(int));
    if (n) { memcpy(got, data, n * sizeof(int)); memcpy(expected, data, n * sizeof(int)); }

    fn(got, n);
    if (n) qsort(expected, n, sizeof(int), cmp_int);

    if (n && memcmp(got, expected, n * sizeof(int)) != 0) {
        fprintf(stderr, "FAIL: %s on case '%s'\n", algo, name);
        exit(1);
    }
    checks++;
    free(got);
    free(expected);
}

static int *random_array(size_t n, int lo, int hi) {
    int *a = malloc((n ? n : 1) * sizeof(int));
    for (size_t i = 0; i < n; i++) a[i] = lo + rand() % (hi - lo + 1);
    return a;
}

int main(void) {
    struct { const char *name; sort_fn fn; } algos[] = {
        {"bubble_sort", bubble_sort},
        {"merge_sort", merge_sort_wrapper},
        {"quick_sort", quick_sort},
    };

    int sorted_arr[50], reversed_arr[50], equal_arr[30];
    for (int i = 0; i < 50; i++) { sorted_arr[i] = i; reversed_arr[i] = 50 - i; }
    for (int i = 0; i < 30; i++) equal_arr[i] = 7;
    int single[] = {42};
    int two_sorted[] = {1, 2};
    int two_reversed[] = {2, 1};
    int duplicates[] = {3, 1, 3, 2, 1, 2, 3, 1, 2};
    int negatives[] = {-5, 3, -1, 0, -10, 8, -5};
    int *rand_small = random_array(200, -100, 100);
    int *rand_large = random_array(2000, -1000000, 1000000);

    for (size_t k = 0; k < sizeof(algos) / sizeof(algos[0]); k++) {
        const char *a = algos[k].name;
        sort_fn f = algos[k].fn;
        check(a, "empty", f, NULL, 0);
        check(a, "single", f, single, 1);
        check(a, "two_sorted", f, two_sorted, 2);
        check(a, "two_reversed", f, two_reversed, 2);
        check(a, "already_sorted", f, sorted_arr, 50);
        check(a, "reversed", f, reversed_arr, 50);
        check(a, "all_equal", f, equal_arr, 30);
        check(a, "duplicates", f, duplicates, 9);
        check(a, "negatives", f, negatives, 7);
        check(a, "random_small", f, rand_small, 200);
        check(a, "random_large", f, rand_large, 2000);
    }

    free(rand_small);
    free(rand_large);
    printf("All %d C checks passed.\n", checks);
    return 0;
}
