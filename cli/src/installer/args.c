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
    char *arg_item = argv[(size_t)i];
    printf("Item: %s\n", arg_item);
    
    if (strncmp(arg_item, "-R", sizeof(arg_item)) == 0)
    {
      if (ask_reinstall() == 0) return -1;
      else return 1;
    } else if (strncmp(arg_item, "-U", sizeof(arg_item)) == 0)
    {
      if (ask_uninstall() == 0) return -2;
      else return 1;
    } else if (strncmp(arg_item, "-u", sizeof(arg_item)) == 0)
    {
      print_installer("ted", "Updating..", 0);
      return -3;
    }
  }
}