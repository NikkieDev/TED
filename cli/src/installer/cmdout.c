#include "headers/cmdout.h"
#include <stdio.h>

void print_installer(char *identifier, char *message, int status)
{
  if (!status) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else if (status == 2) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else printf("[Installer:%s] %s\n", identifier, message);
} 