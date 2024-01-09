/* TODO:
BG:
1. Create dump

User:
1. Cascadingly read all todos in a given directory.
2. Use config file for exclusions and other configurations
*/

#include <stdio.h>
#include <stdlib.h>
#include "headers/fs.h"

#ifdef __unix__
#include <unistd.h>
#include "headers/args.h"


int main(int argc, char** argv)

#else
int main(void);
#endif
{
  printf("TED Says Hi!\n");
  #if defined(WIN32)
  create_win_dump();
  fetch_win_executable();
  #endif
  #ifdef __unix__
  int installed = 0;

  if (geteuid() != 0)
  {
    printf("This is an installer. Run with sudo!\n");
    exit(1);
  }

  switch (arg_parse(argc, argv))
  {
    case 0:
      installed = 0;
      break;
    case -1:
      reinstall();
      installed = 1;
      break;
    case -2:
      uninstall();
      installed = 1;
      break;
    default:
      printf("No arguments provided. No action taken.\nAvailable arguments:\n\tTED_installer -I (Install)\n\tTED_installer -R (Reinstall)\n\tTED_installer -U (Uninstall)\n\tTED_installer -u (Update)\n");
      break;
  }

  if (installed != 1)
    linux_install();

  #endif

  return 0;
}
