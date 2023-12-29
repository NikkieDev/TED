#include "headers/cmdout.h"
#include <stdio.h>

void print_installer(char *identifier, char *message, int status)
{
  if (!status) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else if (status == 2) {
    printf("\033[0;33m[Installer:%s] %s\033[0m\n", identifier, message);
  } else printf("\033[0;31m[Installer:%s] %s\033[0m\n", identifier, message);
}