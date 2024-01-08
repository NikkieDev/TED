#include "headers/fs.h"
#include "headers/cmdout.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined(WIN32)
#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include "../../libs/curl/curl.h"
#endif

void set_dir(char *dir, char *child, char *parent)
{
  #if defined(WIN32)
  snprintf(dir, 256, "%s\\%s", parent, child);
  #else
  snprintf(dir, 256, "%s/%s", parent, child);
  #endif
}

#if defined(WIN32)
void create_win_dump()
{
  struct stat info;
  
  char cmdout_buf[384];
  const int DIR_AMOUNT = 4;

  char *roaming_dir = getenv("APPDATA");

  char *directories[DIR_AMOUNT];

  for (size_t i = 0; i < DIR_AMOUNT; ++i) directories[i] = malloc(384);

  set_dir(directories[0], "TED", roaming_dir);
  set_dir(directories[1], "TED\\dump", roaming_dir);
  set_dir(directories[2], "TED\\config", roaming_dir);
  set_dir(directories[3], "TED\\output", roaming_dir);

  print_installer("filesystem", "Making directories", 0);
  for (size_t i = 0; i < DIR_AMOUNT; i++) {
    if (stat(directories[i], &info) != 0) {      
      if (CreateDirectory(directories[i], NULL)) {
        memset(cmdout_buf, 0, sizeof(cmdout_buf));
        snprintf(cmdout_buf, sizeof(cmdout_buf), "Created directory %s", directories[i]);
        print_installer("filesystem", cmdout_buf, 0);
      } else {
        memset(cmdout_buf, 0, sizeof(cmdout_buf));
        snprintf(cmdout_buf, sizeof(cmdout_buf), "Error creating dir %s", directories[i]);
        print_installer("filesystem", cmdout_buf, 1);

        DWORD error = GetLastError();
        if (error == ERROR_PATH_NOT_FOUND)
          printf("Path not found!\n");
        else if (error == ERROR_ACCESS_DENIED)
          printf("Access to path denied!\n");
        else
          printf("Error code: %lu\n", error);
      }

    } else {
      memset(cmdout_buf, 0, sizeof(cmdout_buf));
      snprintf(cmdout_buf, sizeof(cmdout_buf), "Directory %s already exists", directories[i]);
      print_installer("filesystem", cmdout_buf, 0);
    }
  }

  for (size_t i = 0; i < DIR_AMOUNT; ++i) free (directories[i]);
}

int get_serv_status(CURL *hCurl)
{
  char buf[128];
  
  CURLcode curl_response;
  curl_easy_setopt(hCurl, CURLOPT_URL, "http://node.kubyx.nl"); /* TODO: create /TED/status endpoint with PHP to check if socket server is running */
  curl_easy_setopt(hCurl, CURLOPT_NOBODY, (long)1);

  curl_response = curl_easy_perform(hCurl);
  int http_code;
  curl_easy_getinfo(hCurl, CURLINFO_RESPONSE_CODE, &http_code);

  if (curl_response != CURLE_OK) {
    int status = 0;
    if (http_code != 0) {
      snprintf(buf, sizeof(buf), "Couldn't reach file server! HTTP: %d", http_code);
      status = 1;
    }
    else {
      snprintf(buf, sizeof(buf), "Couldn't reach file server! Server not available.");
      status = 2;
    }

    print_installer("network", buf, status);
    return -1;
  } else {
    snprintf(buf, sizeof(buf), "Server reached with code: %d\n", http_code);
    print_installer("network", buf, 0);

    return 0;
  }
}

void fetch_win_executable()
{
  int reach_tries = 0;

  print_installer("network", "Checking server status", 0);
  CURL *hCurl;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  hCurl = curl_easy_init();
  if (hCurl)
  {
    char buf[64];
    int fileserv_status = get_serv_status(hCurl);

    if (fileserv_status != 0) {
      print_installer("downloader", "Couldn't download files", 2);
      exit(-1);
    } else {
      print_installer("downloader", "Downloading executable files", 0); // TODO: Create socket file server & a C function to download & sort all the files.
      exit(0);
    }
  }
}
#endif

#ifdef __unix__
int create_lin_dump()
{
  const int DIR_AMOUNT = 3;

  struct stat dir_info;
  char buf[128];

  char *dirs[DIR_AMOUNT];

  for (size_t i = 0; i < DIR_AMOUNT; ++i) dirs[i] = malloc(128);
  set_dir(dirs[0], "TED", "/var/log");
  set_dir(dirs[1], "TED", "/opt");
  set_dir(dirs[2], "TED", "/etc");

  for (size_t i = 0; i < DIR_AMOUNT; ++i)
  {
    if (stat(dirs[i], &dir_info) != 0)
    {
      if (mkdir(dirs[i], S_IRWXG | S_IRWXO | S_IRWXU) == -1)
      {
        snprintf(buf, sizeof(buf), "Cant create directory '%s'\n", dirs[i]);
        print_installer("filesystem", buf, 1);
        return 1;
      } else
      {
        snprintf(buf, sizeof(buf), "Created directory %s", dirs[i]);
        print_installer("filesystem", buf, 0);
      }
    } else
    {
      snprintf(buf, sizeof(buf), "Directory %s already exists", dirs[i]);
      print_installer("filesystem", buf, 0);
      ask_reinstall();
    }
  }

  for (size_t i = 0; i < DIR_AMOUNT; ++i) free(dirs[i]);
  return 0;
}

void fetch_lin_exec()
{

}
#endif
