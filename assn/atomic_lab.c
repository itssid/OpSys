/*Reference: https://www.kernel.org/doc/Documentation/atomic_ops.txt
Atomic operation interfaces typically implemented with the help of assembly code
	void atomic_add(int i, atomic_t *v);
	void atomic_sub(int i, atomic_t *v);
	void atomic_inc(atomic_t *v);
	void atomic_dec(atomic_t *v);

These four routines add and subtract integral values to/from the given
atomic_t value.  The first two routines pass explicit integers by
which to make the adjustment, whereas the latter two use an implicit
adjustment value of "1".

One very important aspect of these two routines is that they DO NOT
require any explicit memory barriers.  They need only perform the
atomic_t counter update in an SMP safe manner.

Next, we have:

	int atomic_inc_return(atomic_t *v);
	int atomic_dec_return(atomic_t *v);

These routines add 1 and subtract 1, respectively, from the given
atomic_t and return the new counter value after the operation is
performed.

Unlike the above routines, it is required that explicit memory
barriers are performed before and after the operation.  It must be
done such that all memory operations before and after the atomic
operation calls are strongly ordered with respect to the atomic
operation itself.

For example, it should behave as if a smp_mb() call existed both
before and after the atomic operation.

If the atomic instructions used in an implementation provide explicit
memory barrier semantics which satisfy the above requirements, that is
fine as well.

Let's move on:

	int atomic_add_return(int i, atomic_t *v);
	int atomic_sub_return(int i, atomic_t *v);

These behave just like atomic_{inc,dec}_return() except that an
explicit counter adjustment is given instead of the implicit "1".
This means that like atomic_{inc,dec}_return(), the memory barrier
semantics are required.

Next:

	int atomic_inc_and_test(atomic_t *v);
	int atomic_dec_and_test(atomic_t *v);

These two routines increment and decrement by 1, respectively, the
given atomic counter.  They return a boolean indicating whether the
resulting counter value was zero or not.

It requires explicit memory barrier semantics around the operation as
above.

	int atomic_sub_and_test(int i, atomic_t *v);

This is identical to atomic_dec_and_test() except that an explicit
decrement is given instead of the implicit "1".  It requires explicit
memory barrier semantics around the operation.
*/

/******************************************************************************************************************/

/*
INSTRUCTIONS: Understand the following code thoroughly. Then invoke atomic and non-atomic add functions as an argument of pthread_create separately. Record your observations in a text file for submission. In the submitted code, make sure that atomic version of add is called.

IMPORTANT NOTE:
We have reproduced atomic_add function here for you to understand how it is implemented internally. In practice, you will need to simply use the default header provided by the compiler. It is called atomic.h and is normally located in asm folder.
*/

//The observation is that the output is not the expected output in case of non_atomic_add. In case of atomic_add it is the expected output. 

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define NUM 100000
#define NUM_THREADS 5

int global_int = 0;

void *atomic_add(void *arg)
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		__sync_fetch_and_add( &global_int, 1 ); //Atomic Addition function
	}

	return NULL;
}


void *my_non_atomic_add( void *arg )
{
	int i;
	for (i = 0; i < NUM; i++)
	{
		global_int++;  //non-atomic addition
	}
	return NULL;
}

int main(int argc, char **argv)
{
	int i;
	pthread_t *thrs;

	thrs = malloc( sizeof( pthread_t ) * NUM_THREADS );
	if (thrs == NULL)
	{
		perror( "malloc" );
		return -1;
	}

	printf( "Starting %d threads !!\n", NUM_THREADS );

	for (i = 0; i < NUM_THREADS; i++)
	{
		//Complete the following line
		if (pthread_create( &thrs[i], NULL, atomic_add,
			(void *)(long )i))
		{
			perror( "pthread_create" );
			break;
		}
	}

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join( thrs[i], NULL );

	free( thrs );

	printf( "Actual global_int value is: %d\n",
		global_int );
	printf( "Expected ideal global_int value is: %d\n", NUM * NUM_THREADS );

	return 0;
}
