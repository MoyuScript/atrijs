const Atri = require('./src/atri.js');

const atri = new Atri();

atri.on('mousemove', (/**@type {ATRI.EventData} */ event) => {
  console.log(event.cursorX, event.cursorY);
});

