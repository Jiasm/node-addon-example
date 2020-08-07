const { add } = require('bindings')('add.node')

console.log(add(1, 2))     // 3
console.log(add(0.1, 0.2)) // 熟悉的 0.3XXXXX
