#include <windows.h>
#include "headers/events.h"
#include "headers/menu.h"

void InitMenu(HWND hParent)
{
  HMENU hMenu = CreateMenu();
  HMENU hProjectMenu = CreateMenu();
  HMENU hFileMenu = CreateMenu();

  AppendMenu(hFileMenu, MF_STRING, MENU_PROJECT_FILE_OPEN, "Open");
  AppendMenu(hProjectMenu, MF_POPUP, hFileMenu, "File");
  AppendMenu(hMenu, MF_POPUP, hProjectMenu, "Project");
  SetMenu(hParent, hMenu);
}