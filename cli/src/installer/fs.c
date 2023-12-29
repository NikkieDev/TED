#include "headers/fs.h"
#include "headers/cmdout.h"
#include "../../libs/curl/curl.h"

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <sys/stat.h>

void set_dir(char **dir, char *dir_name, char *roaming_dir)
{
  snprintf(dir, 256, "%s%s", roaming_dir, dir_name);
}

void create_win_dump()
{
  struct stat info;
  
  char cmdout_buf[384];
  #define DIR_AMOUNT 4

  char *roaming_dir = getenv("APPDATA");
  printf("%s\n", roaming_dir);
  for (int i = 0; i < strlen(roaming_dir); i++)
  {
    if (roaming_dir[i] == '\\') {
      roaming_dir[i] = '/';
    }
  }

  const char *directories[DIR_AMOUNT];

  for (size_t i = 0; i < DIR_AMOUNT; ++i) directories[i] = malloc(384);

  set_dir(directories[0], "/TED", roaming_dir);
  set_dir(directories[1], "/TED/dump", roaming_dir);
  set_dir(directories[2], "/TED/config", roaming_dir);
  set_dir(directories[3], "/TED/output", roaming_dir); // broken

  print_installer("filesystem", "Making directories", 0);
  for (size_t i = 0; i < DIR_AMOUNT; i++) {
    if (stat(directories[i], &info) != 0) {
      const char cmd_buf[384];
      
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
}

int get_serv_status(CURL *hCurl)
{
  char buf[128];
  
  CURLcode curl_response;
  curl_easy_setopt(hCurl, CURLOPT_URL, "http://node.kubyx.nl"); /* TODO: create /TED/status endpoint with PHP */
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
      print_installer("downloader", "Downloading executable files", 0); // TODO: Create /TED/download/exec-files endpoint with PHP & a C function to sort all the files.
      exit(0);
    }
  }
}
