# bm2font compiling hints:
# for Next set -DNO_LACK
# for rs6000 set -DHAS_UCHAR
# for sun set -DNOSTDDEF
# any intel machine set -DINTEL
# Compiling everything:
 
CC=gcc -O2 -traditional -DINTEL -DBSD -DHAS_STDLIB # Linux

#CC=cc -O -DNO_LACK -Wall # NeXT

#CC=gcc -O2 -DNO_LACK -DHAS_UCHAR -Wall -Wtraditional # RS6000 gcc, touchy

#CC=gcc -O -DNOSTDDEF  -Wall # sparc gcc
 
#CC=/usr/local/bin/gcc -O2 -traditional -I/usr/local/lib/gcc-include -DBSD -DHAS_STDLIB # Convex

#CC=gcc -O -Dmemmove=my_memmove -DNO_LACK -Wall # Mips thanks to Tim Murphy

#CC=cc +O1 -DBSD=1  -DHAS_STDLIB # HP-UX

#CC=cc -O1 -ansi # Silicon Graphics

bm2font: bm2font.o p2clib.o loc.p2clib.o
	$(CC) -o bm2font bm2font.o p2clib.o loc.p2clib.o -lm 

bm2font.o: bm2font.c p2c.h
	$(CC) -c bm2font.c

p2clib.o: p2clib.c p2c.h
	$(CC) -c p2clib.c

loc.p2clib.o: loc.p2clib.c p2c.h
	$(CC) -c loc.p2clib.c

clean:
	rm -f *.o bm2font *.tfm *pk *.dvi *.log
