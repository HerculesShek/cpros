#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;
int beers = 2000000;


void* drink()
{
  int i;
  for(i=0;i<100000;i++){
	pthread_mutex_lock(&a_lock);
	beers = beers - 1;
	pthread_mutex_unlock(&a_lock);
  }
  return NULL;
}

int main()
{
  pthread_t ts[20];

  int t;
  printf("%i bottles of beer on the wall\n", beers);
  
  for(t=0;t<20;t++){
	pthread_create(&ts[t], NULL, drink, NULL);
  }

  void* result;
  for(t=0;t<20;t++){
	pthread_join(ts[t], &result);
  }
  printf("There are now %i bottles of beer on the wall\n", beers);
  return 0;
}

 
