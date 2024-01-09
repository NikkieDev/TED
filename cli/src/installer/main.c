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
  if (geteuid() != 0)
  {
    printf("This is an installer. Run with sudo!\n");
    exit(1);
  }

  if (arg_parse(argc, argv) == -1) printf("Reinstalling..\n"); reinstall();
  create_lin_dump();
  fetch_lin_exec();
  #endif

  return 0;
}