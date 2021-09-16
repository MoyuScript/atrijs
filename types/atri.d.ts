declare namespace ATRI {
  declare interface EventData {
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
}