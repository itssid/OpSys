/*
 *  Akhil Alluri
 *  Copyleft - TechAlien
 *
 *  Shell simulation Part 1
*/ 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX_LINE 80

int main(void) {
 char *args[MAX_LINE/2 + 1],*token,command[MAX_LINE/2];
 int ctr = 0;
 pid_t pid;

 while(1) {
 	
 	printf("TechAlien>");       //Change to whatever name you want your shell prompt to show.   
 	fflush(stdout);            //refer "man fflush"
 	while(ctr< MAX_LINE/2 + 1) {
 		args[ctr] = NULL;
 		ctr++;
 	}
 	
 	ctr = 0;

    scanf("%[^\n]%*c",command);
    if(strlen(command)==0)         //Handle zero entry. 
    	continue;

    if(strcmp(command,"exit")==0)  //To simulate the exit command in shell. 
    	exit(0);
    
    //To split the user entry into the command and its arguements.
    //Using the strtok function to tokenise the string based on the " " delimiter.

 	args[0] = strtok(command," ");     
 	ctr = 1;
 	token = strtok(NULL," ");
 	while(token!=NULL) {
 		args[ctr] = token;
 		token = strtok(NULL," ");
 		ctr++;
 	}

 	//Forking the process. Child gets pid = 0. 

 	pid = fork();
 	 
 	if(pid==0) {
 		fflush(stdout);
 		execvp(args[0],args);
 		perror(args[0]);
 	}

 	else if(pid < 0)
 		printf("fork failed\n");
 	else
 		waitpid(-1, NULL, 0);  //puts parent on wait until child terminates. 
 }
 return 1;
}
