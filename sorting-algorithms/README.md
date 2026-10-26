# Sorting Algorithms in Python, JavaScript & C

![CI](https://github.com/YOUR_USERNAME/sorting-algorithms/actions/workflows/ci.yml/badge.svg)
![License](https://img.shields.io/badge/license-MIT-blue)

A learning project and personal reference: classic sorting algorithms implemented
**from scratch in three languages**, each with a written explanation, a correctness
proof, a complexity analysis, automated tests and benchmarks.

> Replace `YOUR_USERNAME` in the badge URL above with your GitHub username.

## Algorithms

| Algorithm | Best | Average | Worst | Extra space | Stable | In place |
|-----------|------|---------|-------|-------------|:------:|:--------:|
| [Bubble Sort](algorithms/bubble-sort/README.md) | O(n) | O(n²) | O(n²) | O(1) | Yes | Yes |
| [Merge Sort](algorithms/merge-sort/README.md)   | O(n log n) | O(n log n) | O(n log n) | O(n) | Yes | No |
| [Quick Sort](algorithms/quick-sort/README.md)   | O(n log n) | O(n log n) | O(n²) | O(log n) | No | Yes |

Each algorithm folder contains `README.md` (idea, pseudocode, proof, complexity)
plus the implementations:

```
algorithms/<name>/
├── README.md        explanation + proof
├── merge_sort.py    Python        (snake_case)
├── mergeSort.js     JavaScript    (camelCase, Node.js)
└── merge_sort.c/.h  C             (shown here for merge-sort)
```

## Project structure

```
sorting-algorithms/
├── algorithms/      the implementations + explanations
├── tests/           test_sorts.py · test_sorts.js · test_sorts.c
├── benchmarks/      benchmark.py · benchmark.js · benchmark.c
├── .github/workflows/ci.yml   runs all tests on every push
├── Makefile
└── README.md
```

## Requirements

- Python 3.8+
- Node.js 16+
- A C compiler (`gcc` or `clang`; on Windows use MinGW-w64 or WSL)
- `make` (optional, only a shortcut for the commands below)

## Run an algorithm

```bash
python algorithms/merge-sort/merge_sort.py
node   algorithms/merge-sort/mergeSort.js
```

## Run the tests

With `make`:

```bash
make test        # everything
make test-py     # Python only
make test-js     # JavaScript only
make test-c      # C only
```

Without `make`:

```bash
python tests/test_sorts.py
node tests/test_sorts.js
gcc -std=c11 -Wall -Wextra -O2 -Ialgorithms/bubble-sort -Ialgorithms/merge-sort -Ialgorithms/quick-sort \
    tests/test_sorts.c algorithms/bubble-sort/bubble_sort.c algorithms/merge-sort/merge_sort.c \
    algorithms/quick-sort/quick_sort.c -o test_sorts && ./test_sorts
```

Every algorithm is checked against the language's built-in sort on: empty input,
a single element, sorted, reversed, all-equal, duplicates, negative numbers and
random arrays. Stability and "input is not modified" are tested too.

## Run the benchmarks

```bash
make bench       # or: bench-py / bench-js / bench-c
```

Each script prints a Markdown table (time in milliseconds for random arrays of
1 000 to 10 000 elements). Paste **your own machine's results** below, together
with your CPU and language versions, and compare the three languages:

<!-- TODO: paste your benchmark tables here -->

Things to notice when you look at your results:

- Bubble Sort grows quadratically: doubling `n` roughly quadruples the time.
- Merge and Quick Sort grow almost linearly on this range (O(n log n)).
- The same algorithm is dramatically faster in C than in Python.

## Design decisions

- **Python / JavaScript** functions return a **new** sorted list and never modify
  their input. **C** functions sort the array **in place** (the idiomatic C way).
- Quick Sort uses a **random pivot** and a **3-way partition**, which avoids the
  classic O(n²) behaviour on sorted input and on arrays with many duplicates.
- Merge Sort's merge step uses `<=` so that equal elements keep their order (stability).

## Roadmap

- [ ] Insertion, Selection, Heap, Shell sort
- [ ] Counting, Radix, Bucket sort (non-comparison sorts)
- [ ] Tim Sort walkthrough (the algorithm behind Python's `sorted`)
- [ ] Interactive React visualizer deployed on GitHub Pages
- [ ] Benchmark charts

## Contributing / License

Released under the [MIT License](LICENSE).
