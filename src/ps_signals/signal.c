#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// handler for interrupt
void die(int sig)
{
  puts("\ndeal with something, like close file and network connection...");
  exit(1);
}
void coffee(int sig)
{
  puts("\ntime for coffee...\n");
}
//  register a handler.
int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  int res = sigaction(sig, &action, NULL);
  if(res==-1){
	fprintf(stderr, "Can't map the handler");
	exit(2);
  }
  return res;
}

int main()
{
  catch_signal(SIGALRM, coffee);
  catch_signal(SIGINT, die);
  alarm(3);
  char name[30];
  printf("Enter your name: ");
  fgets(name, 30, stdin);
  printf("Hello %s\n", name);
  return 0;
} 
