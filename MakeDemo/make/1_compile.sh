##########Compilation Script in Multi-File Demo#######################
#	@(#)File:           $CVSfile: Makefile,v $
#	@(#)Version:        $Revision: 0.1 $
#	@(#)Last changed:   $Date: 2015/03/16 23:20:00 $
#	@(#)Purpose:        Demo of Multi-File Code and Make utility
#	@(#)Author:         Narendra Shukla
#	@(#)Copyright:      (C) NS 2015-16
#	@(#)Product:        :CSD 204 Operating Systems Lab
#####################################################################
gcc -g -o ../obj/main.o -Wall -c ../src/main.c -I../include
gcc -g -o ../obj/printstring.o -Wall -c ../src/printstring.c -I../include
gcc -o ../bin/final ../obj/main.o ../obj/printstring.o
#cd ../bin
#./final
