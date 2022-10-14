This is bm2font, a utility to convert pictures into TeX fonts, in C.


This is the C port of the Pascal program of the same name by
Friedhelm Sowa <tex@tex@dd0rud81.bitnet>

It has been converted to C via p2c, the Pascal-to-C converter written
by  Dave Gillespie, <synaptx!daveg@uunet.UU.NET>
and is  up and running on NeXT, sun sparc (gcc) and rs6000 (gcc).
For these three I provided cc lines in the Makefile

New in the list is Mach I386 whatever this means


Manifest:
========

You should have obtained bm2font.c, p2clib.c, loc.p2clib.c, p2c.h,
and a Makefile.
And the Gnu Public licence.

There is a subdirectory "testpix" now, containing a selection of
pictures, some of them out of Friedhelm's manual, by the author's
permission, some others of my own choice, where you might experiment
the different settings (particularly "carina" is extremely difficult!)
and a selection of grayscales for testing.


Changes against the PC version:
==============================

I took out the preview option (-s) and the pxl file option (-p)
The former has been most PC specific, and would have to be
handled by a bunch of library functions, and for the latter
I don't see a real need today anymore (If you are still hooked,
complain to your dope dealers)
and I removed the interpretation of environment variables, which would
make little sense in a Unix environment.
So everything is handled locally, even if you call
bm2font /pub/gifs/dobie.gif
you will obtain ./dobiea.tfm, ./dobiea.300pk etc.
(and see a fake)
(NeXT and Sony addicts: I left it at 300 by default)


Tiff Users Attention please 
===========================

There seems to be some babel going on around the name "tiff".
I had the opportunity to try out tifflib and SDSClib
on tiffs, and found out that the current scanner software
on PCs, as well as the examples talk a language entirely
uncomprehensible to them and vice versa.

So, if you have tiffs from, say, the Peoples collection, or some
Icon, do convert it to gif before applying bm2font. There is
enough of software ready to do the conversion. Try pbmplus.



Compilation notes:
=================

The p2c stuff is intended to go with bm2font since they are modifications
made while mating bm2font to p2c. Mille gracias to Dave for valuable
suggestions.

Do not put them into your installed p2c-version, nor replace
them by your installed p2c versions.

The sample CC lines that are in the Makefile may fail for you;
the gccs I used may not be the same for you, nor the OS.

The defines mentioned in the Makefile refer to entries in p2c.h,
except one: -DINTEL which refers to order of significance stuff
inside bm2font. Set that for intel machines.
For the other defines, try p2c.h for reference.

In particular, I know nothing about SysV-systems, so, try your luck.


Manual:
======

There is no bm2font.1 yet, I do not speak troff.

Friedhelm's manual applies to this version, except the changes
mentioned above.
I won't bundle it with this package since it is readily available
on all TeX servers.

For printing the manual, you must give to the supplied pks the extension
*.300pk.

Note to NeXT and Sony users: For printing the manual, you must give your
dvi-printer the resolution 300. Sony will print it in smallprint,
NeXT built-in PS interpreter scales it up again (and does a
real good job, at that)


Thanks to:
=========

Friedhelm Sowa, who constantly kept me posted to the latest updates
and things yet to do. He was the one to point out that the INTEL switch
was to be a cpp define switch instead a web switch.

Dave Gillespie, the author of p2c, who suggested a good many changes
to p2c instead of the fixes I did..

Bart Childs and Heinz Werntges who were the first guinea pigs to
test this out


===========================================
Well, erh, there are the copyright notices:

bm2font is (C) 1991, 1992 by Friedhelm Sowa,
p2c.h, p2clib.c, loc.p2clib.c is
   (C) 1989, 1990, 1991  Free Software Foundation, Inc.
and the Unix port is (A) by mahilata (All Rights Destroyed)

..and
#include <stddisclaim.h>
Specifically, I do not guarantee that you will be able to print
the Kascha series out of a.s.p--I did not keep them for testing:-)
(Really, to me the lyaps out of Northern Norway are more exciting stuff,
 but, perhaps I am a pervert)

All complaints please direct to mahilata@vogon.mathi.uni-heidelberg.de
who will most gladly pipe them to /dev/null
