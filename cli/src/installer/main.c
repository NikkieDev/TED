#include <stdio.h>
#include "headers/fs.h"

int main(void)
{
  printf("TED Says Hi!\n");

  #ifdef linux

  #elif defined(WIN32)
  create_windows_dump();

  #endif
}