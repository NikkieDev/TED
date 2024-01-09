#include "headers/args.h"
#include "headers/cmdout.h"
#include <stdio.h>
#include <string.h>

int arg_parse(int argc, char** argv)
{
  if (argc < 2)
    return 0;
  
  for (int i = 0; i < argc; ++i)
  {
    if (strncmp(argv[(size_t)i], "-R", sizeof(argv[(size_t)i])) == 0)
    {
      if (ask_reinstall() == 0) return -1;
      else return 1;
    } else if (strncmp(argv[(size_t)i], "-U", sizeof(argv[(size_t)i])) == 0)
    {
      if (ask_uninstall() == 0) return -2;
      else return 1;
    }
  }
}