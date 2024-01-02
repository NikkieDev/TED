#include <windows.h>
#include "headers/events.h"

void HandleEvent(int wParam, HWND hWindow)
{
  if (wParam == MENU_PROJECT_FILE_OPEN)
  {
    MessageBox(hWindow, "TED says Hi", "Info", MB_OK | MB_ICONINFORMATION);
  }

  return;
}