#include <windows.h>

#ifndef UI_H
#define UI_H

typedef struct itemSize
{
  int width;
  int height
} itemSize;

void CreateUI();
void InitMenu(HWND *hPtr, void *p);

#endif