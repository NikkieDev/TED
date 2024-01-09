#include "headers/cmdout.h"
#include <stdio.h>
#include <ctype.h>

void print_installer(char *identifier, char *message, int status)
{
  if (!status) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else if (status == 2) {
    printf("[Installer:%s] %s\n", identifier, message);
  } else printf("[Installer:%s] %s\n", identifier, message);
}

int ask_reinstall()
{
  char answer;
  int return_val;
  printf("Seems like TED has been installed before. Would you like to reinstall? (Y\\n)\n");
  scanf(" %c", &answer);
  
  answer = tolower(answer);

  switch (answer)
  {
    case 'y':
      return_val = 0;
      break;
    case 'n':
      return_val = 1;
      break;
    default:
      return_val = ask_reinstall();
      break;
  }

  return return_val;
}

int ask_uninstall()
{
  char answ;
  int return_val;

  printf("Are you sure you want to fully uninstall TED & all it's data (including userdata) (Y\\n)\n");
  scanf(" %c", &answ);

  answ = tolower(answ);

  switch (answ)
  {
    case 'y':
      return_val = 0;
      break;
    case 'n':
      return_val = 1;
      break;
    default:
      return_val = ask_uninstall();
      break;
  }

  return return_val;
}