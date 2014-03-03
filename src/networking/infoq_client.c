#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void errnoexit(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}
void error(char *msg)
{
  errnoexit(msg);
  exit(1);
}

int open_socket(char *host, char *port)
{
  struct addrinfo *res;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if(getaddrinfo("www.infoq.com", "80", &hints, &res)==-1)
	error("Can't resolve the address");

  int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (d_sock == -1)
	error("Can't open socket");
  int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
  if (c == -1)
	error("Can't connect to socket");
  return d_sock;
}

int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
	errnoexit("Error talking to the server");
  return result;
}

int main(int argc, char *argv[])
{
  int d_sock;
  d_sock = open_socket("www.infoq.com", "80");
  char buf[255];
  sprintf(buf, "GET / HTTP/1.1\r\n", argv[1]);
  say(d_sock, buf);

  say(d_sock, "Host: www.infoq.com\r\n\r\n");
  char rec[256];
  int bytesRcvd = recv(d_sock, rec, 255, 0);
  while(bytesRcvd){

	if(bytesRcvd == -1)
	  error("Can't read from server");
	rec[bytesRcvd] = '\0';
	printf("%s", rec);
	bytesRcvd = recv(d_sock, rec, 255, 0);
  }
  close(d_sock);
  return 0;
}


