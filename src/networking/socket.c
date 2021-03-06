#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>


void errnoexit(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}
void error(char *msg)
{
  errnoexit(msg);
  exit(1);
}

char *advice[] = {
  "Take smaller bites\r\n",
  "Go for the tight jeans. No they do NOT make you look fat.\r\n", 
  "One word: inappropriate\r\n",
  "Just for today, be honest. Tell your boss what you *really* think\r\n", 
  "You might want to rethink that haircut\r\n"
};

int open_listener_socket()
{
  int s = socket(PF_INET, SOCK_STREAM, 0); //0 represents a protocal number, leave it as 0 here.
  if(s == -1)
	error("Can't open a socket");
  return s;
}

void bind_to_port(int socket, int port)
{
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;
  if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int))==-1)
	error("Can't set the reuse option on the socket");

  int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
  if(c == -1)
	error("Can't bind to socket");
}

int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
	errnoexit("Error talking to the client");
  return result;
}

int read_in(int socket, char *buf, int len)
{
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  while ((c > 0) && (s[c-1] != '\n')) {
    s += c; slen -= c;
    c = recv(socket, s, slen, 0);
  }
  if (c < 0) 
    return c;
  else if (c == 0)
    buf[0] = '\0';
  else
    s[c-1]='\0';
  return len - slen;
}

int main()
{

  int listener_d = open_listener_socket();

  bind_to_port(listener_d, 30000);

  if(listen(listener_d, 10) == -1)
	error("Can't listen");
  puts("Waiting for connection");

  struct sockaddr_storage client_addr;
  unsigned int address_size = sizeof(client_addr);
  while(1){
	int connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &address_size);
	if(connect_d == -1)
	  error("Can't open secondary socket");

	char *msg = advice[rand() % 5];
    say(connect_d, msg);

	close(connect_d);
  }

  return 0;
} 
