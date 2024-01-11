#include "headers/netw.h"
#include "headers/cmdout.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int server_connect(int *socket_fd)
{

  struct sockaddr_in addr = {AF_INET, htons(3001)};
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  int s = socket(AF_INET, SOCK_STREAM, 0);
  *socket_fd = connect(s, &addr, sizeof(addr));

  if (s == -1 || *socket_fd <= 0)
  {
    print_installer("network", "Couldn't reach server. Exiting..", 2);
    return -1;
  } else return 0;
}

int close_connection(int *socket_fd)
{
  print_installer("network", "Cleaning up.", 0);
  close(*socket_fd);
  return 0;
}

int send_message(int *socket_fd, char *type)
{
  char buf[128];
  strncpy(buf, type, sizeof(buf));

  int status = send(*socket_fd, buf, sizeof(buf), 0);
  if (status <= 0)
  {
    print_installer("network", "Couldn't send message to server. Exiting..", 2);
    return -1;
  } else
  {
    char buf_recv[128];
    char buf_com[128];
    
    status = recv(*socket_fd, buf_com, sizeof(buf_com), 0);

    if (status <= 0)
    {
      print_installer("network", "Error receiving response from server. Exiting..", 2);
      return -1;
    }

    snprintf(buf_recv, sizeof(buf_recv), "Message send, received: %s", buf_com);
    print_installer("network", buf_recv, 0);
    return 0;
  }
}

#endif