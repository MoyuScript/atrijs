# ATRI.js

A high-performance keyboard and mouse monitor for Node.js (Windows only)

# Installation

**Environment acquirements:**

+ [Build Tools for Visual Studio 2019](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) With "Desktop development with C++" workload.
+ [Python 3.X](https://www.python.org/)

**You must to install environments above to build this module automatically.**

Install by using npm:

```bash
$ npm install --save atrijs
```

Install by using yarn:

```bash
$ yarn add atrijs
```

# Getting started

```javascript
const Atri = require('atrijs');

const atri = new Atri();

atri.on('keydown', (/**@type {ATRI.EventData} */ event) => {
  console.log(`Key "${event.keyName}" pressed!`)
});

atri.on('keyup', (/**@type {ATRI.EventData} */ event) => {
  console.log(`Key "${event.keyName}" released!`)
});
```

# Available Events

+ `keydown`
+ `keyup`
+ `mousedown`
+ `mouseup`
+ `mousemove`
+ `mousewheel`

# Structure of event callback 

```typescript
interface EventData {
  // Type of current event
  type: string

  // Only set in `keydown`, `keyup`, `mousedown`, `mouseup` events.
  keyCode: number

  // Name of key
  keyName: string

  // Is `Alt` key pressed
  alt: boolean

  // Is `Ctrl` key pressed
  ctrl: boolean

  // Is `Shift` key pressed
  shift: boolean

  // Is `Win` key pressed
  win: boolean

  // Only set in `mousewheel` event
  wheel: number

  // Current position X of cursor
  cursorX: number

  // Current position Y of cursor
  cursorY: number

  // Timestamp of current event
  timestamp: number
}
```

# Reference

[Virtual-Key Codes](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
