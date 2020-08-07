const { curryAdd } = require('bindings')('curry-add');

const fn = curryAdd(1, 2, 3);
const fn2 = fn(4);

console.log(fn.valueOf())
console.log(fn2.valueOf())
console.log(fn2(5).valueOf())