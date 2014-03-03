#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>


int s = socket(PF_INET, SOCK_STREAM, 0);

struct sockaddr_in si;
memset(&si, 0, sizeof(si));
si.sin_family = PF_INET;
si.sin_addr.s_addr = inet_addr("199.119.126.69");
si.sin_port = htons(80);
connect(s, (struct sockaddr *) &si, sizeof(si));


struct addrinfo *res;
struct addrinfo hints;
memset(&hints, 0, sizeof(hints));
hints.ai_family = PF_UNSPEC;
hints.ai_socktype = SOCK_STREAM;
getaddrinfo("www.infoq.com", "80", &hints, &res);

int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
connect(s, res->ai_addr, res->ai_addrlen);
