#include "headers/cmdout.h"
#include <stdio.h>

void print_installer(char *identifier, char *message, int is_error)
{
  if (!is_error) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else printf("\033[0;31m[Installer:%s] %s\033[0m\n", identifier, message);
}