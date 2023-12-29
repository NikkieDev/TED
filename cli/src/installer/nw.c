#include "headers/nw.h"
#include "headers/cmdout.h"
#include "../../libs/curl/curl.h"

#if defined(WIN32)
void download_win(CURL hCurl) {
}
#endif

int get_serv_status(CURL hCurl)
{
  CURLcode curl_response;
  curl_easy_setopt(hCurl, CURLOPT_URL, "http://node.kubyx.nl/TED/status"); /* TODO: create /TED/status endpoint with Laravel */
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