"""Benchmark the Python implementations.  Run:  python benchmarks/benchmark.py"""
import os
import random
import sys
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for name in ("bubble-sort", "merge-sort", "quick-sort"):
    sys.path.insert(0, os.path.join(ROOT, "algorithms", name))

from bubble_sort import bubble_sort  # noqa: E402
from merge_sort import merge_sort    # noqa: E402
from quick_sort import quick_sort    # noqa: E402

SIZES = [1000, 2000, 5000, 10000]
ALGORITHMS = [("bubble", bubble_sort), ("merge", merge_sort), ("quick", quick_sort)]

print("| n | " + " | ".join(f"{n} (ms)" for n, _ in ALGORITHMS) + " |")
print("|---|" + "---|" * len(ALGORITHMS))
for size in SIZES:
    data = [random.randint(0, 10**6) for _ in range(size)]
    row = []
    for _, fn in ALGORITHMS:
        start = time.perf_counter()
        fn(data)
        row.append(f"{(time.perf_counter() - start) * 1000:.2f}")
    print(f"| {size} | " + " | ".join(row) + " |")
