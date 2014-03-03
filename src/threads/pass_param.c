#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void* foo(void *a)
{
  long no = (long)a;
  printf("param is %ld\n", no);
  return (void *)(++no);
}

int main()
{
  pthread_t ts[20];

  long t;
  for(t=0;t<20;t++){
	pthread_create(&ts[t], NULL, foo, (void*)t);
  }

  void* result;
  for(t=0;t<20;t++){
	pthread_join(ts[t], &result);
	printf("thread %i returned %ld\n", t, (long)result);
  }
  return 0;
}
