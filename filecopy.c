#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define READ_END 0
#define WRITE_END 1
#define BUFFER_S 25

int main(int argc,char *argv[]) {
	int fd[2];
	char write_buf,read_buf;
	FILE *read_file,*write_file;
	pid_t pid;

	int ctr;

	if((read_file = fopen(argv[1],"r"))==NULL) {
		perror("No source");
		return 1;
	}

	if((write_file = fopen(argv[2],"w"))==NULL) {
	  perror("No dest");
	  return 1;
	}

	if(pipe(fd)==-1) {
		perror("pipe");
		return 1;
	}

	if((pid = fork())== -1) {
		perror("fork");
		return 1;
	}
	
	//int flag;
	while(!feof(read_file)) {
		if(pid>0) {
			wait(NULL);
			close(fd[WRITE_END]);
			if(read(fd[READ_END],&read_buf,1)>0) {
			    fputc(read_buf,write_file);
			    //printf("%c",read_buf);
		    }
		    else
		    	break;
		}
		else {
			close(fd[READ_END]);
			write_buf=fgetc(read_file);
			if(write_buf == -1)
				break;
			write(fd[WRITE_END],&write_buf,1);
			//printf("parent :%d\n",write_buf);
		}	
	}
	
	fcloseall();
	exit(0);	
}
