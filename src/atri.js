/// <reference path="../types/atri.d.ts" />

const {Worker} = require('worker_threads');
const events = require('events');
const path = require('path');

const KEYCODE = {
  MOUSE_LBUTTON: 0x01,
  MOUSE_RBUTTON: 0x02,
  CANCEL: 0x03,
  MOUSE_MBUTTON: 0x04,
  MOUSE_XBUTTON1: 0x05,
  MOUSE_XBUTTON2: 0x06,
  BACK: 0x08, 
  TAB: 0x09,
  CLEAR: 0x0C,
  // RETURN
  ENTER: 0x0D,
  SHIFT: 0x10,
  CONTROL: 0x11,
  // MENU
  ALT: 0x12,
  PAUSE: 0x13,
  CAPITAL: 0x14,

  ESCAPE: 0x1B,

  SPACE: 0x20,
  // PRIOR
  PAGE_UP: 0x21,
  // NEXT
  PAGE_DOWN: 0x22,
  END: 0x23,
  HOME: 0x24,
  LEFT: 0x25,
  UP: 0x26,
  RIGHT: 0x27,
  DOWN: 0x28,

  // SNAPSHOT
  PRINT_SCREEN: 0x2C,
  INSERT: 0x2D,
  DELETE: 0x2E,

  K_0: 0x30,
  K_1: 0x31,
  K_2: 0x32,
  K_3: 0x33,
  K_4: 0x34,
  K_5: 0x35,
  K_6: 0x36,
  K_7: 0x37,
  K_8: 0x38,
  K_9: 0x39,

  K_A: 0x41,
  K_B: 0x42,
  K_C: 0x43,
  K_D: 0x44,
  K_E: 0x45,
  K_F: 0x46,
  K_G: 0x47,
  K_H: 0x48,
  K_I: 0x49,
  K_J: 0x4A,
  K_K: 0x4B,
  K_L: 0x4C,
  K_M: 0x4D,
  K_N: 0x4E,
  K_O: 0x4F,
  K_P: 0x50,
  K_Q: 0x51,
  K_R: 0x52,
  K_S: 0x53,
  K_T: 0x54,
  K_U: 0x55,
  K_V: 0x56,
  K_W: 0x57,
  K_X: 0x58,
  K_Y: 0x59,
  K_Z: 0x5A,

  SEMICOLON: 0xBA,
  EQUAL: 0xBB,
  COMMA: 0xBC,
  MINUS: 0xBD,
  PERIOD: 0xBE,
  SLASH: 0xBF,
  BACKQUOTE: 0xC0,
  BRACKETLEFT: 0xDB,
  BACKSLASH: 0xDC,
  BRACKETRIGHT: 0xDD,
  QUOTE: 0xDE,

  LWIN: 0x5B,
  RWIN: 0x5C,

  NUMPAD_0: 0x60,
  NUMPAD_1: 0x61,
  NUMPAD_2: 0x62,
  NUMPAD_3: 0x63,
  NUMPAD_4: 0x64,
  NUMPAD_5: 0x65,
  NUMPAD_6: 0x66,
  NUMPAD_7: 0x67,
  NUMPAD_8: 0x68,
  NUMPAD_9: 0x69,

  NUMPAD_MULTIPLY: 0x6A,
  NUMPAD_ADD: 0x6B,
  NUMPAD_SEPARATOR: 0x6C,
  NUMPAD_SUBTRACT: 0x6D,
  NUMPAD_DECIMAL: 0x6E,
  NUMPAD_DIVIDE: 0x6F,

  F1: 0x70,
  F2: 0x71,
  F3: 0x72,
  F4: 0x73,
  F5: 0x74,
  F6: 0x75,
  F7: 0x76,
  F8: 0x77,
  F9: 0x78,
  F10: 0x79,
  F11: 0x7A,
  F12: 0x7B,

  NUMLOCK: 0x90,
  SCROLL: 0x91,
  LSHIFT: 0xA0,
  RSHIFT: 0xA1,
  LCONTROL: 0xA2,
  RCONTROL: 0xA3,
  LALT: 0xA4,
  RALT: 0xA5
};

// Reverse key-value pair
const REVERSED_KEYCODE = {};

for (const [k, v] of Object.entries(KEYCODE)) {
  REVERSED_KEYCODE[v] = k;
}

let atriInstance;

class Atri extends events.EventEmitter {
  static KEYCODE = KEYCODE;
  static REVERSED_KEYCODE = REVERSED_KEYCODE;

  constructor() {
    if (atriInstance) {
      return atriInstance;
    }

    super();

    this._worker;
    this._initializeWorker();
    

    atriInstance = this;
  }

  _initializeWorker() {
    this._worker = new Worker(path.resolve(__dirname, './worker.js'));
    this._worker.on("message", (/**@type {ATRI.EventData} */ event) => {
      // Additional data of timestamp
      event.timestamp = Date.now();

      // Additional data of name of key
      event.keyName = REVERSED_KEYCODE[event.keyCode] || 'UNKNOWN';

      this.emit(event.type, event);
    });

    this._worker.on("error", (err) => {
      setImmediate(this._initializeWorker.bind(this));
    });
  }
}

module.exports = Atri;

module.exports.default = Atri;
