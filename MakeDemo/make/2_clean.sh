##########Clean-up Script in Multi-File Demo#########################
#	@(#)File:           $CVSfile: Makefile,v $
#	@(#)Version:        $Revision: 0.1 $
#	@(#)Last changed:   $Date: 2015/03/16 23:20:00 $
#	@(#)Purpose:        Demo of Multi-File Code and Make utility
#	@(#)Author:         Narendra Shukla
#	@(#)Copyright:      (C) NS 2015-16
#	@(#)Product:        :CSD 204 Operating Systems Lab
#####################################################################
rm ../bin/final 2>/dev/null
rm ../obj/*.o 2>/dev/null
rm ../src/*~ ../src/*.o ../src/a.out 2>/dev/null
rm ../include/*~ 2>/dev/null
rm ../doc/*~ 2>/dev/null
rm *~ 2>/dev/null
