#include "headers/fs.h"
#include "headers/cmdout.h"
#include <stdio.h>

#ifdef linux
#include <dirent.h>

#else

#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include <sys/stat.h>

#endif

void set_dir(char **dir, char *dir_name)
{
  #if defined(WIN32)
  snprintf(dir, 256, "%s%s", getenv("APPDATA"), dir_name);
  #endif
}

void create_win_dump()
{
  #if defined(WIN32)
  struct _stat info;
  
  char cmdout_buf[256+48];
  #define DIR_AMOUNT 4

  const char *roaming_dir = getenv("APPDATA");
  const char *directories[DIR_AMOUNT];

  for (size_t i = 0; i < DIR_AMOUNT; ++i) directories[i] = malloc(256);

  set_dir(directories[0], "\\TED");
  set_dir(directories[1], "\\TED\\dump");
  set_dir(directories[2], "\\TED\\config");
  set_dir(directories[3], "\\TED\\output");

  print_installer("filesystem", "Making directories");
  for (size_t i = 0; i < DIR_AMOUNT; i++) {
    if (stat(directories[i], &info) != 0) {
      const char cmd_buf[256];
      
      snprintf(cmd_buf, sizeof(cmd_buf), "mkdir %s", directories[i]);
      system(cmd_buf);

      memset(cmdout_buf, 0, sizeof(cmdout_buf));
      snprintf(cmdout_buf, sizeof(cmdout_buf), "Created directory %s", directories[i]);
      print_installer("filesystem", cmdout_buf);
    } else {
      memset(cmdout_buf, 0, sizeof(cmdout_buf));
      snprintf(cmdout_buf, sizeof(cmdout_buf), "Directory %s already exists", directories[i]);
      print_installer("filesystem", cmdout_buf);
    }
  }

  for (size_t i = 0; i < DIR_AMOUNT; ++i) free (directories[i]);
  #endif
}

void fetch_win_executable()
{
  
}