const {isMainThread, parentPort} = require('worker_threads');
const atri = require('bindings')('atrijs');

atri.registerEvent((event) => {
  if (isMainThread) {
    console.log(event);
  } else {
    parentPort.postMessage(event);
  }
});
