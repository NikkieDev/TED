#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  struct sockaddr_in addr = {.sin_family = AF_INET, .sin_addr = INADDR_ANY, .sin_port = htons(3002)};
  int s = socket(AF_INET, SOCK_STREAM, 0);
  int found = 2;

  char message_types[3][14] = {"update", "check_version", "install"};
  char recv_buf[128];
  char send_buf[128];
  
  bind(s, &addr, sizeof(addr));

  listen(s, 5);
  int csock_fd = accept(s, 0, 0);

}