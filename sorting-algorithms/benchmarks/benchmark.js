// Benchmark the JavaScript implementations.  Run:  node benchmarks/benchmark.js
const path = require("path");
const dir = (name) => path.join(__dirname, "..", "algorithms", name);
const { bubbleSort } = require(path.join(dir("bubble-sort"), "bubbleSort.js"));
const { mergeSort } = require(path.join(dir("merge-sort"), "mergeSort.js"));
const { quickSort } = require(path.join(dir("quick-sort"), "quickSort.js"));

const SIZES = [1000, 2000, 5000, 10000];
const algorithms = [
  ["bubble", bubbleSort],
  ["merge", mergeSort],
  ["quick", quickSort],
];

console.log(`| n | ${algorithms.map(([n]) => `${n} (ms)`).join(" | ")} |`);
console.log(`|---|${"---|".repeat(algorithms.length)}`);
for (const size of SIZES) {
  const data = Array.from({ length: size }, () => Math.floor(Math.random() * 1e6));
  const row = algorithms.map(([, fn]) => {
    const start = process.hrtime.bigint();
    fn(data);
    return (Number(process.hrtime.bigint() - start) / 1e6).toFixed(2);
  });
  console.log(`| ${size} | ${row.join(" | ")} |`);
}
