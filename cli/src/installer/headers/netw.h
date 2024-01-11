#ifndef NETW_H
#define NETW_H

#ifdef __unix__
  int server_connect(int *sd);
  int close_connection(int *sd);
  int send_message(int *sd, char *t);
#endif

#endif