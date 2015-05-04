#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4
/* the available amount of each resource */
int available[NUMBER_OF_RESOURCES];
/*the maximum demand of each customer */
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the amount currently allocated to each customer */
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
/* the remaining need of each customer */
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
pthread_cond_t CV[NUMBER_OF_CUSTOMERS];
pthread_mutex_t lock; 
int request_resources(int customer_num, int request[]) {
	int i,j,flag = 1;
	
		for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
			if(!(request[j] <= need[customer_num][j]))
				flag = 0;
	if(!flag)
		return 0;
	else {
		flag = 1;
		
			for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
				if(!(request[j] <= need[customer_num][j]))
					flag = 0;
		if(flag) {
			
				for(j = 0;j<NUMBER_OF_RESOURCES;j++) {
					available[j] = available[j] - request[j];
					allocation[customer_num][j] += request[j];
					need[customer_num][j] -= request[j];
				}

			if(!safety_check()) {
				for(i = 0;i<NUMBER_OF_CUSTOMERS;i++)
					for(j = 0;j<NUMBER_OF_RESOURCES;j++) {
						need[i][j] += request[j];
						allocation[i][j] -= request[j];
						available[j] += request[j];
					}
				return 0;
			}
			else
				return 1;

		}
	}
}

int release_resources(int customer_num) {
	int i,j;
	for(j = 0;j<NUMBER_OF_RESOURCES;j++) {
		available[j] += allocation[customer_num][j];
		allocation[customer_num][j] = 0;
		need[customer_num][j] = 0;
		maximum[customer_num][j] = 0; 
	}

	for(i = 0;i<NUMBER_OF_CUSTOMERS;i++)
		pthread_cond_signal(&CV[i]);
}

int safety_check() {
 int work[NUMBER_OF_RESOURCES],finish[NUMBER_OF_CUSTOMERS];
 int i,j;
  
 for(j = 0;j<NUMBER_OF_RESOURCES;j++)
  work[j] = available[j];
  
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++)
  finish[i] = 0;
  
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) {
  for(j = 0;j<NUMBER_OF_RESOURCES;j++) {
   if(finish[i] == 0 && need[i][j] <= work[j]) {
    work[j] = work[j] + allocation[i][j];
    finish[i] = 1;
   }
  }
 }
 
 int flag = 1;
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++)
  if(finish[i] != 1)
   flag = 0;
  
 if(flag)
 	return 1;  
 else
 	return 0;
}

void init_max() {
 int i,j;
 printf("Max matrix :\n");
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) {
  printf("\nEnter resource for P%d :",i);
  for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
   scanf("%d",&maximum[i][j]);
 }
}

void init_alloc() {
 int i,j;
 printf("Allocation matrix :\n");
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) {
  printf("\nEnter resource for P%d :",i);
  for(j = 0;j<NUMBER_OF_RESOURCES;j++) 
   scanf("%d",&allocation[i][j]);
 }
}



void init() {
 int i,j;
 for(i = 0;i<NUMBER_OF_CUSTOMERS;i++) {
  for(j = 0;j<NUMBER_OF_RESOURCES;j++) {
   available[j] = available[j] - allocation[i][j];
   need[i][j] = maximum[i][j] - allocation[i][j];
  }
 }
}

