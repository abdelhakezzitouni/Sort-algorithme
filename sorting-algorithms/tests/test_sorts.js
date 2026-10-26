// Tests for the JavaScript implementations.  Run:  node tests/test_sorts.js
const assert = require("assert");
const path = require("path");

const dir = (name) => path.join(__dirname, "..", "algorithms", name);
const { bubbleSort } = require(path.join(dir("bubble-sort"), "bubbleSort.js"));
const { mergeSort } = require(path.join(dir("merge-sort"), "mergeSort.js"));
const { quickSort } = require(path.join(dir("quick-sort"), "quickSort.js"));

const algorithms = { bubbleSort, mergeSort, quickSort };

// NOTE: JS's default .sort() compares as strings, so we always pass a comparator.
const reference = (a) => [...a].sort((x, y) => x - y);
const randInt = (lo, hi) => lo + Math.floor(Math.random() * (hi - lo + 1));
const randomArray = (n, lo, hi) => Array.from({ length: n }, () => randInt(lo, hi));

const cases = {
  empty: [],
  single: [42],
  twoSorted: [1, 2],
  twoReversed: [2, 1],
  alreadySorted: Array.from({ length: 50 }, (_, i) => i),
  reversed: Array.from({ length: 50 }, (_, i) => 50 - i),
  allEqual: Array(30).fill(7),
  duplicates: [3, 1, 3, 2, 1, 2, 3, 1, 2],
  negatives: [-5, 3, -1, 0, -10, 8, -5],
  randomSmall: randomArray(200, -100, 100),
  randomLarge: randomArray(2000, -1e6, 1e6),
};

let passed = 0;
for (const [algoName, fn] of Object.entries(algorithms)) {
  for (const [caseName, data] of Object.entries(cases)) {
    assert.deepStrictEqual(fn(data), reference(data), `${algoName} failed on ${caseName}`);
    passed++;
  }
  // the input array must not be modified
  const original = [5, 3, 1, 4, 2];
  fn(original);
  assert.deepStrictEqual(original, [5, 3, 1, 4, 2], `${algoName} modified its input`);
  passed++;
}

// stability: bubble and merge sort must keep equal keys in original order
const items = Array.from({ length: 300 }, (_, tag) => ({ key: randInt(0, 5), tag }));
for (const fn of [bubbleSort, mergeSort]) {
  // wrap objects so that comparison operators work on the key
  const wrapped = items.map((it) => ({ ...it, valueOf: () => it.key }));
  const out = fn(wrapped);
  for (let i = 1; i < out.length; i++) {
    const a = out[i - 1];
    const b = out[i];
    assert.ok(a.key < b.key || (a.key === b.key && a.tag < b.tag), `${fn.name} is not stable`);
  }
  passed++;
}

console.log(`All ${passed} JavaScript checks passed.`);
