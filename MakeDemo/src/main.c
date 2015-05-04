/***********Main File in Multi-File Demo***********
@(#)File:           $CVSfile: main.c,v $
@(#)Version:        $Revision: 0.1 $
@(#)Last changed:   $Date: 2015/03/16 23:05:00 $
@(#)Purpose:        Demo of Multi-File Code and Make
@(#)Author:         Narendra Shukla
@(#)Copyright:      (C) NS 2015-16
@(#)Product:        :CSD 204 Operating Systems Lab
***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myheader.h"
//#include "../include/myheader.h"

char	*JustOneString = "Welcome to CSD 204 OS";

int main(int argc, char **argv)
{
	char *arg[] = {"echo", "Going back to bash prompt",NULL};
	system("clear");
	printf("\nI am inside main and going to call Print String routine\n");
/** Call PrintJustOneString() - defined in another C source file****/
	PrintJustOneString(ONE_STRING);
/***************Back to Main now************************************/
printf("Back to main from Printing String Job.execvp called to echo !!\n");
	execvp(arg[0],arg);
	return 0;
}
