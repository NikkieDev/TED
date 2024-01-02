#include <windows.h>
#include "headers/ui.h"
#include "headers/menu.h"

LRESULT CALLBACK WindowProc(HWND mainWindow, UINT uMsg, WPARAM wParam, LPARAM lParam); // hoisted method

int WINAPI WinMain(HINSTANCE handleInstance, HINSTANCE handlePreviousInstance, LPSTR lpCmdLine, int nCmdShow)
{
  wchar_t *CLASS_NAME = "WindowClass";
  wchar_t *WINDOW_NAME = "TED";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = handleInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);

  RegisterClass(&wc);
  HWND mainWindow = CreateWindowEx( // Handle Window
    0, CLASS_NAME, WINDOW_NAME,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
    NULL, NULL, handleInstance, NULL
  );

  if (mainWindow == NULL)
  {
    MessageBox(NULL, "Couldn't create window", "Error", MB_ICONERROR);
    return 0;
  }

  InitMenu(mainWindow);
  CreateUI(mainWindow);
  ShowWindow(mainWindow, 1);
  UpdateWindow(mainWindow);
  
  MSG msg = {}; while (GetMessage(&msg, NULL, 0,0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND mainWindow, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_CREATE:
    {
      return 0;
    }
    case WM_COMMAND:
      HandleEvent(LOWORD(wParam), mainWindow);
  };

  return DefWindowProc(mainWindow, uMsg, wParam, lParam);
}