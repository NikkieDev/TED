#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  struct sockaddr_in addr = {.sin_family = AF_INET, .sin_addr = INADDR_ANY, .sin_port = htons(3001)};
  int s = socket(AF_INET, SOCK_STREAM, 0);
  int found = 0;

  char message_types[3][14] = {"update", "check_version", "install"};
  char recv_buf[128];
  char send_buf[128];
  
  bind(s, &addr, sizeof(addr));

  listen(s, 5);
  int csock_fd = accept(s, 0, 0);
  printf("Client connected\n");

  recv(csock_fd, recv_buf, sizeof(recv_buf), 0);
  printf("Received: %s\n", recv_buf);

  for (size_t i = 0; i < sizeof(message_types) / sizeof(message_types[0]); ++i)
  {
    if (0 == strncmp(recv_buf, message_types[i], sizeof(recv_buf)))
    {
      snprintf(send_buf, sizeof(send_buf), "Received: %s", message_types[i]);
      send(csock_fd, send_buf, sizeof(send_buf), 0);
      found = 1;
    }
  }

  if (found == 0)
  {
    strncpy(send_buf, "Bad Message", sizeof(send_buf));
    send(csock_fd, send_buf, sizeof(send_buf), 0);
  }

  printf("Client disconnected\n");
  close(csock_fd);
  close(s);
}