const {isMainThread, parentPort} = require('worker_threads');
const path = require('path');
const atri = require(path.resolve(__dirname, '../build/Release/atrijs.node'));

atri.registerEvent((event) => {
  if (isMainThread) {
    console.log(event);
  } else {
    parentPort.postMessage(event);
  }
});
