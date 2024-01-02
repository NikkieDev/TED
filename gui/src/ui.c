#include "headers/ui.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>

void CreateLabel(const char *title, int pos[2], itemSize size, HWND hwnd)
{
  HWND newLabel = CreateWindowEx(0,"STATIC",title,
    WS_VISIBLE | WS_CHILD,
    pos[0], pos[1], size.width, size.height,
    hwnd, NULL, NULL, NULL
  );

  if (newLabel == NULL)
    MessageBox(NULL, "ERROR", "Couldn't create STATIC (label)", MB_OK | MB_ICONERROR);
}

void GetParentSize(HWND parentHandle, itemSize *size)
{
  RECT rect;
  GetClientRect(parentHandle, &rect);
  
  size->width = rect.right - rect.left;
  size->height = rect.bottom - rect.top;
}

void CreateUI(HWND hwnd)
{
  itemSize parentSize;
  char parentName[128];
  
  GetParentSize(hwnd, &parentSize);
  GetWindowText(hwnd, parentName, sizeof(parentName));

  if (strncmp(parentName, "TED", sizeof(parentName)) == 0)
  {
    CreateLabel("Select file to begin", (int[2]){0,0}, parentSize, hwnd);
  }
}