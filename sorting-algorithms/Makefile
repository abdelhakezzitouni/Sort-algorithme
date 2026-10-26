CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -O2
INCLUDE = -Ialgorithms/bubble-sort -Ialgorithms/merge-sort -Ialgorithms/quick-sort
C_SRCS  = algorithms/bubble-sort/bubble_sort.c algorithms/merge-sort/merge_sort.c algorithms/quick-sort/quick_sort.c
BUILD   = build

.PHONY: test test-py test-js test-c bench bench-py bench-js bench-c clean

test: test-py test-js test-c

test-py:
	python3 tests/test_sorts.py

test-js:
	node tests/test_sorts.js

test-c:
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(INCLUDE) tests/test_sorts.c $(C_SRCS) -o $(BUILD)/test_sorts
	./$(BUILD)/test_sorts

bench: bench-c bench-js bench-py

bench-py:
	python3 benchmarks/benchmark.py

bench-js:
	node benchmarks/benchmark.js

bench-c:
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(INCLUDE) benchmarks/benchmark.c $(C_SRCS) -o $(BUILD)/benchmark
	./$(BUILD)/benchmark

clean:
	rm -rf $(BUILD)
