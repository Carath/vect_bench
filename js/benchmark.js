"use strict";

if (typeof window === "undefined") { // node.js environment

	var { performance } = require("perf_hooks"); // for old node versions.

	module.exports = {
		runBenchmarks
	}
}
else { window.onload = function() {} } // web browser

class PQnode {
	constructor(key, item) {
		this.key = key;
		this.item = item;
	}
}

function runBenchmarks() {
	// let n = 10;
	let n = 100000000;

	let start = performance.now();

	benchmark(n, (x) => String.fromCharCode(x % 256), (x) => x.codePointAt(0));
	benchmark(n, (x) => x, (x) => x);
	benchmark(n, (x) => new PQnode(x, x), (x) => x.key + x.item); // all 'numbers'

	let end = performance.now();
	console.log("Elasped time:", ((end - start) / 1000.).toFixed(3), "s");
}

function benchmark(n, create_t, hash_t) {
	try {
		console.log("Bench with", n, "samples...");

		let arr = [];

		for (let i = 0; i < n; ++i) {
			arr.push(create_t(i));
		}

		let checksum = 0; // type 'number'
		for (let i = 0; i < arr.length; ++i) {
			checksum += hash_t(arr[i]);
		}
		console.log("checksum:", checksum);

		while (arr.length > 0) {
			arr.pop();
		}

		console.log("Length:", arr.length);
		return checksum;
	}
	catch (error) {
		console.error(error);
		console.log("This benchmark failed.");
		return 0;
	}
}
