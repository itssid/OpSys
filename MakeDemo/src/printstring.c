/******Module for Print String in Multi-File Demo**
@(#)File:           $CVSfile: printstring.c,v $
@(#)Version:        $Revision: 0.1 $
@(#)Last changed:   $Date: 2015/03/16 23:10:00 $
@(#)Purpose:        Demo of Multi-File Code and Make
@(#)Author:         Narendra Shukla
@(#)Copyright:      (C) NS 2015-16
@(#)Product:        :CSD 204 Operating Systems Lab
***************************************************/
#include<stdio.h> //included to remove printf Warning
extern char	*JustOneString;
void PrintJustOneString(MyString)
char	*MyString;
{
	printf("\n**********Inside Function PrintJustOneString*********\n");
	printf("Function is called with Parameter %s\n", MyString);
	printf("Global Variable defined in main file = %s\n", JustOneString);
	printf("*******Coming out of Function PrintJustOneString*****\n\n");
}
