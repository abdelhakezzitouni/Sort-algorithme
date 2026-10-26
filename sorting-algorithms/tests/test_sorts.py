"""Unit tests for the Python implementations.  Run:  python tests/test_sorts.py"""
import os
import random
import sys
import unittest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for name in ("bubble-sort", "merge-sort", "quick-sort"):
    sys.path.insert(0, os.path.join(ROOT, "algorithms", name))

from bubble_sort import bubble_sort  # noqa: E402
from merge_sort import merge_sort    # noqa: E402
from quick_sort import quick_sort    # noqa: E402

ALGORITHMS = {
    "bubble_sort": bubble_sort,
    "merge_sort": merge_sort,
    "quick_sort": quick_sort,
}

CASES = {
    "empty": [],
    "single": [42],
    "two_sorted": [1, 2],
    "two_reversed": [2, 1],
    "already_sorted": list(range(50)),
    "reversed": list(range(50, 0, -1)),
    "all_equal": [7] * 30,
    "duplicates": [3, 1, 3, 2, 1, 2, 3, 1, 2],
    "negatives": [-5, 3, -1, 0, -10, 8, -5],
    "random_small": [random.randint(-100, 100) for _ in range(200)],
    "random_large": [random.randint(-10**6, 10**6) for _ in range(2000)],
}


class TestSorts(unittest.TestCase):
    def test_correctness(self):
        for algo_name, fn in ALGORITHMS.items():
            for case_name, data in CASES.items():
                with self.subTest(algorithm=algo_name, case=case_name):
                    self.assertEqual(fn(data), sorted(data))

    def test_input_not_modified(self):
        for algo_name, fn in ALGORITHMS.items():
            with self.subTest(algorithm=algo_name):
                data = [5, 3, 1, 4, 2]
                fn(data)
                self.assertEqual(data, [5, 3, 1, 4, 2])

    def test_stability(self):
        """Bubble and merge sort must be stable (quick sort is not)."""
        # sort pairs by key only; equal keys must keep their original order
        class Item:
            def __init__(self, key, tag):
                self.key, self.tag = key, tag

            def __lt__(self, other): return self.key < other.key
            def __le__(self, other): return self.key <= other.key
            def __gt__(self, other): return self.key > other.key
            def __ge__(self, other): return self.key >= other.key

        data = [Item(random.randint(0, 5), i) for i in range(300)]
        for fn in (bubble_sort, merge_sort):
            out = fn(data)
            for a, b in zip(out, out[1:]):
                self.assertTrue(a.key < b.key or (a.key == b.key and a.tag < b.tag))


if __name__ == "__main__":
    unittest.main(verbosity=2)
