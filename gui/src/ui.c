#include "headers/ui.h"
#include <windows.h>

void InitSubMenu(HWND *parentHandle, void *param) // sort into init.c
{

}

void InitMenu(HWND *parentHandle, void *param) // sort into init.c
{
  HMENU hMenu = CreateMenu();
  HMENU hProjectMenu = CreateMenu();

  AppendMenu(hProjectMenu, MF_STRING, 1, "Open");
  AppendMenu(hMenu, MF_POPUP, hProjectMenu, "Project");
  SetMenu(*parentHandle, hMenu);
}

void CreateLabel(const char *title, int pos[2], itemSize size, HWND *hwnd, void *param)
{
  HWND newLabel = CreateWindowEx(0,"STATIC",title,
    WS_VISIBLE | WS_CHILD,
    pos[0], pos[1], size.width, size.height,
    *hwnd, NULL, NULL, NULL
  );

  if (newLabel == NULL)
    MessageBox(NULL, "ERROR", "Couldn't create STATIC (label)", MB_OK | MB_ICONERROR);
}

void GetParentSize(HWND *parentHandle, itemSize *size)
{
  RECT rect;
  GetClientRect(*parentHandle, &rect);
  
  size->width = rect.right - rect.left;
  size->height = rect.bottom - rect.top;
}

void CreateUI(HWND *hwnd)
{
  itemSize parentSize;
  GetParentSize(hwnd, &parentSize);

  CreateLabel("TED", (int[2]){0,0}, (itemSize){parentSize.width, 20}, hwnd, NULL);
}