/*References:
1. Text Book SGGv9 Section 5.9.2 and
2. Mutex API Reference, https://www.kernel.org/doc/htmldocs/kernel-locking/apiref-mutex.html

Mutex locks are available in Linux for protecting critical sections within the kernel. Here, a task must invoke the mutex lock() function prior to entering a critical section and the mutex unlock() function after exiting the critical section. If the mutex lock is unavailable, a task calling mutex lock() is put into a sleep state and is awakened when the lock’s owner invokes mutex unlock().[Ref 1]

POSIX API has methods like pthread_mutex_lock and pthread_mutex_unlock. Read man pages to know more about these methods. If man page is not installed, google for man pages OR you may install using the following command:
sudo apt-get install manpages-posix-dev

INSTRUCTIONS: 
1. Understand the following code thoroughly. Compile and Run the code using make file given. What problem do you observe? 
2. Now apply mutex locks at appropriate places. Whether problem in 1 gets solved?
3. Record your observations in a text file for submission. In the submitted code, make sure the lock are applied properly in the appropriate places.

ANSWERS : 
1 > The problem is that the expected final incremented value is not the same as the one computed by the threads. This is because of race condition, where the threads operate upon the wrong counter value. 

2 > Yes , as the locks ensure that no thread increments the counter value out of their turn. 

3 > Observation : Locks ensure proper output, as none of the threads can increment out of their turn. 
 
IMPORTANT NOTE:
We have reproduced atomic_add function here for you to understand how it is implemented internally. In practice, you will need to simply use the default header provided by the compiler. It is called atomic.h and is normally located in asm folder.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define MAX_ITERATION 1000000

pthread_mutex_t my_mutex,wait_mutex;

int my_count;
void *thread_function(void *ptr );

void
my_increment_count_function()
{
		//Apply the lock by completing the following
		//pthread_mutex_lock(&my_mutex);
		my_count ++;
		//pthread_mutex_lock(&wait_mutex);
		sleep(10000);
		//pthread_mutex_unlock(&wait_mutex);
		//Remove the lock by completing the following
		//pthread_mutex_unlock(&my_mutex);
}

int
my_fetch_count_function()
{
		int count;
		//pthread_mutex_lock(&my_mutex);
		count = my_count;
	    	//pthread_mutex_unlock(&my_mutex);
	    	return (count);
	    	
}
 
int main(int argc, char **argv)
{fflush(stdout);
     pthread_t thread1, thread2;//thread3;
     const char *name1 = "Inside Thread 1";
     const char *name2 = "Inside Thread 2";
    // const char *name3 = "Inside Thread 3";
     int  my_ret_1, my_ret_2,my_ret_3;
    /* Create independent threads */
     my_ret_1 = pthread_create(&thread1, NULL, thread_function, (void*) name1);
     if(my_ret_1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",my_ret_1);
         exit(EXIT_FAILURE);
     }
     my_ret_2 = pthread_create( &thread2, NULL, thread_function, (void*) name2);
     if(my_ret_2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",my_ret_2);
         exit(EXIT_FAILURE);
     }
    /* my_ret_3 = pthread_create( &thread3, NULL, thread_function, (void*) name3);
     if(my_ret_3)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",my_ret_3);
         exit(EXIT_FAILURE);
     }
     */
     printf("pthread_create() for thread 1 returns: %d\n",my_ret_1);
     printf("pthread_create() for thread 2 returns: %d\n",my_ret_2);
    
     
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL);
//     pthread_join( thread3, NULL);

   exit(EXIT_SUCCESS);
}

void *thread_function( void *ptr )
{
     char *name;
     int loopvar=0; 
     name = (char *) ptr;
     printf("%s \n", name);
     fflush(stdout);
     for(loopvar=0; loopvar<MAX_ITERATION; loopvar++)
	{
	//my_increment_count_function();
	my_count = my_count+1;
//	printf("Thread %s prints %d\n", name, my_fetch_count_function()); 
printf("Thread %s prints %d\n", name, my_count); 
	//printf("%d\n",my_fetch_count_function());
	}
	return NULL;
}
