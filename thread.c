/*
 *Program for TWO THREADED SORTING
 *Operating Systems lab
 *Akhil Alluri
 *1310110043
 *CopyLeft 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 50

struct parameters
{
	int *array;
int start;
int end;
};

void * sort(struct parameters *par) ;

int * merge(int *array1,int *array2,int m,int n) {
	int i,j,k,*temp;
	temp = (int *)malloc((m+n) * sizeof(int));
	for(i = 0,j = 0,k = 0;i<m+n;) {
		if(j<m && k<n) {
			if(array1[j] < array2[k]) {
				temp[i] = array1[j];
				j++;
			}
			else {
				temp[i] = array2[k];
				k++;
			}
			i++;
		}

		else if(j == m && k < n) {
			while(k < n && i < m+n) {
				temp[i] = array2[k];
				k++;i++;
			}
		}

		else {
			while(j< m && i < m+n) {
				temp[i] = array1[j];
				j++;i++;
			}
		}
	}
	return temp;
}


void printarray(struct parameters *par) {
	int start,end;
	start = par->start;
	end = par->end;
	int i = start;
	while(i<end) {
		printf("%d ",par->array[i]);
		i++;
	}
}

void * thread_merge(struct parameters *par) {
	int *arr,m,n;
	m = (par->end)/2;
	n = par->end - m ;
	arr = (int *)malloc((m+n)*sizeof(int));
	arr = par->array;
	par->array = merge(arr,arr+m,m,n);
	pthread_exit(0);
}

void main() {
	printf("--MULTI THREADED SORTING---\n");
	pthread_t t1,t2,t3;
	int *array,n;
	
	printf("Enter number of elements to be sorted:\n");
	scanf("%d",&n);
	array = (int *)malloc((n)*sizeof(int));

	int i = 0;
	while(i<n) {
		scanf("%d",&array[i]);
		i++;
	}

	struct parameters *p1,*p2,*p;
	p1 = (struct parameters *)malloc(sizeof(struct parameters));
	p2 = (struct parameters *)malloc(sizeof(struct parameters));
	p  = (struct parameters *)malloc(sizeof(struct parameters));

	//Setting up the parameters.
    p1->array = array; // First half
	p1->start = 0;
	p1->end = n/2;
	p2->array = array; //Second Half
	p2->start = n/2;
	p2->end = n;
	p ->array = array; //Whole array
	p ->start = 0;
	p ->end = n;


	printf("Array before Sorting:\n");

	printarray(p);

	pthread_create(&t1,NULL,sort,(struct parameters *)p1);
	
	pthread_create(&t2,NULL,sort,(struct parameters *)p2);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	printf("\nArray after sorting:\n");
	printarray(p);

	//sort(p1); //Testing
	//sort(p2); //Testing
	//thread_merge(p); //Testing
	pthread_create(&t3,NULL,thread_merge,(struct parameters *)p);
	pthread_join(t2,NULL);

	printf("\nArray After Merging:\n");
	printarray(p);
	printf("\n");
	/*printarray(p1);
	printf("\n");
	printarray(p2);
   	printf("\n");*/
}



void * sort(struct parameters *par) {
	int *array = par->array;
	int start,end,i,j,temp;
	start = par -> start;
	end = par -> end;
	for(i=start;i<end;i++) {
        for(j=start;j<end-1;j++) {   
            if(array[j]>array[j+1]) {
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp; 
            }
        }
    }

    pthread_exit(0);
}