const { bubble } = require('bindings')('bubble.node')

const arr = Array.from(new Array(1e4), () => Math.random() * 1e8 | 0)

console.time('c++')
const a = bubble(arr)
console.timeEnd('c++')

function bubbleJS (arr) {
  for (let i = 0, len = arr.length; i < len; i++) {
    for (let j = i + 1; j < len; j++) {
      if (arr[i] < arr[j]) {
        [arr[i], arr[j]] = [arr[j], arr[i]]
      }
    }
  }

  return arr
}

console.time('js')
bubbleJS(arr)
console.timeEnd('js')
