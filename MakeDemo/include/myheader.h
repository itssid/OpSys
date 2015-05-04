/***********Header File in Multi-File Demo***********
@(#)File:           $CVSfile: myheader.h,v $
@(#)Version:        $Revision: 0.1 $
@(#)Last changed:   $Date: 2015/03/16 23:15:00 $
@(#)Purpose:        Demo of Multi-File Code and Make
@(#)Author:         Narendra Shukla
@(#)Copyright:      (C) NS 2015-16
@(#)Product:        :CSD 204 Operating Systems Lab
***************************************************/

//Start with Protection Against Double Inclusion

#ifndef __MYHEADER_H__
#define __MYHEADER_H__

#define ONE_STRING "Hello World" //Macro Declaration

void PrintJustOneString();	//Function Prototype
extern char *JustOneString;	//External Global Variable

//We may write typedef for some struct here if required by the Designer

#endif
