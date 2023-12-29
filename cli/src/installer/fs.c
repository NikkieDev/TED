#include "headers/fs.h"
#include "headers/cmdout.h"
#include "../../libs/curl/curl.h"

#include <stdio.h>

#ifdef linux
#include <dirent.h>

#else
#include <windows.h>
#include <tchar.h>
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
  struct stat info;
  
  char cmdout_buf[256+48];
  #define DIR_AMOUNT 4

  const char *roaming_dir = getenv("APPDATA");
  const char *directories[DIR_AMOUNT];

  for (size_t i = 0; i < DIR_AMOUNT; ++i) directories[i] = malloc(256);

  set_dir(directories[0], "\\TED");
  set_dir(directories[1], "\\TED\\dump");
  set_dir(directories[2], "\\TED\\config");
  set_dir(directories[3], "\\TED\\output");

  print_installer("filesystem", "Making directories", 0);
  for (size_t i = 0; i < DIR_AMOUNT; i++) {
    if (stat(directories[i], &info) != 0) {
      const char cmd_buf[256];
      
      snprintf(cmd_buf, sizeof(cmd_buf), "mkdir %s", directories[i]);
      system(cmd_buf);

      memset(cmdout_buf, 0, sizeof(cmdout_buf));
      snprintf(cmdout_buf, sizeof(cmdout_buf), "Created directory %s", directories[i]);
      print_installer("filesystem", cmdout_buf, 0);
    } else {
      memset(cmdout_buf, 0, sizeof(cmdout_buf));
      snprintf(cmdout_buf, sizeof(cmdout_buf), "Directory %s already exists", directories[i]);
      print_installer("filesystem", cmdout_buf, 0);
    }
  }

  for (size_t i = 0; i < DIR_AMOUNT; ++i) free (directories[i]);
  #endif
}

int get_serv_status(CURL *hCurl)
{
  char buf[128];
  
  CURLcode curl_response;
  curl_easy_setopt(hCurl, CURLOPT_URL, "http://node.kubyx.nl"); /* TODO: create /TED/status endpoint with Laravel */
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

  #if defined(WIN32)
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
      print_installer("downloader", "Downloading executable files", 0);
      exit(0);
    }
  }
  #endif
}