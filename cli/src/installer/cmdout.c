#include "headers/cmdout.h"
#include <stdio.h>

void print_installer(char *identifier, char *message)
{
  printf("[Installer:%s] %s\n", identifier, message);
}