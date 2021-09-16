#include <windows.h>
#include "napi.h"
#include <string>
#include <ctime>

using namespace Napi;

Function * callback;
Env * env;

bool isCtrlKeyDown() {
  return (GetKeyState(VK_LCONTROL) >> 7) | (GetKeyState(VK_RCONTROL) >> 7) | (GetKeyState(VK_CONTROL) >> 7);
}

bool isShiftKeyDown() {
  return (GetKeyState(VK_LSHIFT) >> 7) | (GetKeyState(VK_RSHIFT) >> 7) | (GetKeyState(VK_SHIFT) >> 7);
}

bool isWinKeyDown() {
  return (GetKeyState(VK_LWIN) >> 7) | (GetKeyState(VK_RWIN) >> 7);
}

bool isAltKeyDown(KBDLLHOOKSTRUCT * data) {
  return data->flags >> 5 | GetKeyState(VK_MENU) >> 7;
}

bool isAltKeyDown() {
  return GetKeyState(VK_MENU) >> 7;
}

LRESULT CALLBACK hookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
  Object event = Object::New(*env);

  switch(wParam) {
    // Keyboard

    case WM_KEYDOWN: {
      KBDLLHOOKSTRUCT * data = (KBDLLHOOKSTRUCT *) lParam;
      event.Set("type", String::New(*env, "keydown"));
      event.Set("keyCode", Number::New(*env, data->vkCode));
      event.Set("alt", Boolean::New(*env, isAltKeyDown(data)));
      break;
    }

    case WM_KEYUP: {
      KBDLLHOOKSTRUCT * data = (KBDLLHOOKSTRUCT *) lParam;
      event.Set("type", String::New(*env, "keyup"));
      event.Set("keyCode", Number::New(*env, data->vkCode));
      event.Set("alt", Boolean::New(*env, isAltKeyDown(data)));
      break;
    }

    case WM_SYSKEYDOWN: {
      KBDLLHOOKSTRUCT * data = (KBDLLHOOKSTRUCT *) lParam;
      event.Set("type", String::New(*env, "keydown"));
      event.Set("keyCode", Number::New(*env, data->vkCode));
      event.Set("alt", Boolean::New(*env, isAltKeyDown(data)));
      break;
    }

    case WM_SYSKEYUP: {
      KBDLLHOOKSTRUCT * data = (KBDLLHOOKSTRUCT *) lParam;
      event.Set("type", String::New(*env, "keyup"));
      event.Set("keyCode", Number::New(*env, data->vkCode));
      event.Set("alt", Boolean::New(*env, isAltKeyDown(data)));
      break;
    }

    // Mouse

    case WM_LBUTTONDOWN: {
  
      event.Set("type", String::New(*env, "mousedown"));
      event.Set("keyCode", Number::New(*env, VK_LBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_LBUTTONUP: {
      event.Set("type", String::New(*env, "mouseup"));
      event.Set("keyCode", Number::New(*env, VK_LBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_RBUTTONDOWN: {
      event.Set("type", String::New(*env, "mousedown"));
      event.Set("keyCode", Number::New(*env, VK_RBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_RBUTTONUP: {
      event.Set("type", String::New(*env, "mouseup"));
      event.Set("keyCode", Number::New(*env, VK_RBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_MBUTTONDOWN: {
      event.Set("type", String::New(*env, "mousedown"));
      event.Set("keyCode", Number::New(*env, VK_MBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_MBUTTONUP: {
      event.Set("type", String::New(*env, "mouseup"));
      event.Set("keyCode", Number::New(*env, VK_MBUTTON));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_XBUTTONDOWN: {
      event.Set("type", String::New(*env, "mousedown"));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("keyCode", Number::New(*env, VK_XBUTTON1 - 1 + ((data->mouseData) >> 16)));
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      
      break;
    }

    case WM_XBUTTONUP: {
      event.Set("type", String::New(*env, "mouseup"));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("keyCode", Number::New(*env, VK_XBUTTON1 - 1 + ((data->mouseData) >> 16)));
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_MOUSEMOVE: {
      event.Set("type", String::New(*env, "mousemove"));
      event.Set("keyCode", Number::New(*env, -1));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      break;
    }

    case WM_MOUSEWHEEL: {
      event.Set("type", String::New(*env, "mousewheel"));
      event.Set("keyCode", Number::New(*env, -1));
      MSLLHOOKSTRUCT * data = (MSLLHOOKSTRUCT *) lParam;
      event.Set("cursorX", Number::New(*env, data->pt.x));
      event.Set("cursorY", Number::New(*env, data->pt.y));
      event.Set("wheel", Number::New(*env, (short) (data->mouseData >> 16)));
      break;
    }

    default: {
      event.Set("type", String::New(*env, "unknown"));
      break;
    }
  }

  event.Set("ctrl", Boolean::New(*env, isCtrlKeyDown()));
  event.Set("shift", Boolean::New(*env, isShiftKeyDown()));
  event.Set("win", Boolean::New(*env, isWinKeyDown()));

  if (!event.Has("alt")) {
    event.Set("alt", Boolean::New(*env, isAltKeyDown()));
  }

  if (!event.Has("wheel")) {
    event.Set("wheel", Number::New(*env, 0));
  }

  if (!event.Has("cursorX")) {
    LPPOINT cursorPos;
    GetCursorPos(cursorPos);
    event.Set("cursorX", Number::New(*env, cursorPos->x));
    event.Set("cursorY", Number::New(*env, cursorPos->y));
  }

  callback->Call({event});

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void messageLoop() {
  MSG msg;

  while (true) {
    GetMessage(&msg, NULL, 0, 0);

    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

Number registerEvent(const CallbackInfo& info) {
  env = &info.Env();

  if (info.Length() < 1) {
    Error::New(*env, "Unexpected arguments").ThrowAsJavaScriptException();
    return Number::New(*env, 0);
  }
  
  if (!info[0].IsFunction()) {
    Error::New(*env, "First argument is not a function").ThrowAsJavaScriptException();
    return Number::New(*env, 0);
  }

  callback = &info[0].As<Function>();

  HHOOK h1 = SetWindowsHookExW(WH_MOUSE_LL, hookCallback, NULL, 0);
  HHOOK h2 = SetWindowsHookExW(WH_KEYBOARD_LL, hookCallback, NULL, 0);
  
  messageLoop();

  UnhookWindowsHookEx(h1);
  UnhookWindowsHookEx(h2);

  return Number::New(*env, 0);
}


Object init(Env env, Object exports) {
  exports.Set(String::New(env, "registerEvent"), Function::New(env, registerEvent));
  
  return exports;
}

NODE_API_MODULE(atrijs, init)
