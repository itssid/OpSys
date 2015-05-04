#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "bankersAlgo.h"



void customer(int cust_num) {
	int i,j;
	printf("%d started\n",cust_num);
	int request[NUMBER_OF_RESOURCES];
	for(j = 0;j<NUMBER_OF_RESOURCES;j++)
		request[j] = need[cust_num][j];
	
	int done = 1,todo = 0;
	while(1) {
	pthread_mutex_lock(&lock);
	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) 
  		for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
  			if(need[i][j] != maximum[i][j])
  				todo = 1;
  	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) 
  		for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
  			if(maximum[i][j] != 0)
  				done = 0;

  	if(todo)
		if(!request_resources(cust_num,request))
			pthread_cond_wait(&CV[cust_num],&lock);
	else
		if(done) {
			printf("%d /n",cust_num);
			pthread_mutex_unlock(&lock);
			pthread_exit(NULL);
		}
		else {
			release_resources(cust_num);
		}
	}
}


void main(int argc, char **argv) {
	int i;
	pthread_t th[NUMBER_OF_CUSTOMERS];
	pthread_attr_t attr;
	pthread_mutex_init(&lock,NULL);
	pthread_attr_init(&attr);
 	
 	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++)
 		pthread_cond_init(&CV[i],NULL);
 
	init_max();
	init_alloc();
	for(i=0;i<NUMBER_OF_RESOURCES;i++)
		available[i] = (int) argv[i+1];
	
printf("initiate\n");
 	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) {
 		pthread_create(&th[i],NULL,customer, (int) i);
 	}

 	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) pthread_join(th[i],NULL);

}

