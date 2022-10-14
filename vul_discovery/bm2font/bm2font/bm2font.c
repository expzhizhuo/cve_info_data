/* Output from p2c, the Pascal-to-C translator */
/* From input file "bm2font.pas" */


/*1:*/

#include "p2c.h"
/* p2c: bm2font.pas, line 1: 
 * Note: Unexpected name "texfile" in program header [262] */
/* p2c: bm2font.pas, line 1: 
 * Note: Unexpected name "tfmfile" in program header [262] */
/* p2c: bm2font.pas, line 1: 
 * Note: Unexpected name "pxlfile" in program header [262] */
/* p2c: bm2font.pas, line 1: 
 * Note: Unexpected name "bitmap" in program header [262] */
/* p2c: bm2font.pas, line 1: 
 * Note: Unexpected name "tmpfil" in program header [262] */


/*logfile,*/


typedef uchar ebts;

typedef short halfk;

typedef long dynlong[52][129];
typedef unsigned short dynword[52][129];
typedef short korbyte[511];
typedef short spreadbyte[256];
/*55:*/
typedef unsigned short pxlstr;

typedef ebts pxla[65522L];
/*:55*/
/*59:*/
typedef short pxlba[32761];
/*:59*/
/*91:*/
typedef uchar dmatrix[7][7];

/*:91*/


#define maxmemsize      32760


/*92:*/

Static dmatrix ditherm = {
  { 1, 3, 6, 10, 18, 26, 38 },
  { 2, 4, 8, 12, 20, 28, 40 },
  { 5, 7, 9, 14, 22, 30, 42 },
  { 11, 13, 15, 16, 24, 32, 44 },
  { 17, 19, 21, 23, 25, 34, 46 },
  { 27, 29, 31, 33, 35, 36, 48 },
  { 37, 39, 41, 43, 45, 47, 49 }
};

/*:92*/
/*:1*/
/*2:*/
Static ebts hrep, vrep, xrep, yrep, patswitch, usecol, pminval, pmaxval,
	    bufsh, nextbuf, tmpcolor, invbyte, invbit, xratio, yratio;
Static unsigned short tpal[256];
Static long bitspsam, rowspstrip;
Static unsigned short photoinf;
Static short colpos;
Static ebts pxllook[256];
Static ebts lutone[256];
Static ebts lutvga[256];
Static ebts lutsl[256];
Static double spreadcol, patref, greyunit;
Static short greykor;
Static short *gkorh, *gkordivp;
Static short *spreadvals;
Static short hktab[256];
Static boolean cspread;
Static unsigned short bhell[256];
Static boolean cmyk, cyan, magenta, yellow, black, saveblack;
Static short colcyan, colblack, colmagenta, colyellow;
Static dmatrix colmatrix;
Static unsigned short pxlcolor;
Static boolean greypxl, egastretch, ledprinter, distribute, giftemp, pcxtemp;
Static short maxcol;
Static long usepxl, vusepxl, brightness;
Static short greypix;
Static ebts pattern[4][197][7];
Static ebts ipattern[4][197][7];
Static unsigned short tab[64][3];
Static uchar ccol;
Static Char cref[77];
Static ebts b1[3000];
Static ebts b2[3000];
Static ebts b3[3000];
Static ebts b4[3000];
Static long linepos_, posbit;
Static halfk dbuf;
Static boolean clipon, zeroline, zerorow, nameok, fok;
Static Char cmd[256];
Static Char bmname[256];
Static Char font[256];
Static Char tmpname[256];
Static Char fontpre[256];
Static Char fontupc[256];
Static ebts curpat[2];
Static short gbufp, gbufpp;
Static halfk pxlinlen, zeropads;
Static short mapwidth, mapheight, maplines, freelines;
Static long mapinlen, newwidth, newheight;
Static short a, b, f, nf, g, ng, ly, lx, minx, maxx, i, nj, j, v, k, pk, pkn;
Static uchar pm, pn;
Static unsigned short pl, pb;
Static uchar c, cb;
Static long fh, sh, fw, sw;
Static unsigned short lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np;
Static union {
  uchar b[4];
  long i;
} cx;
Static long checksum, dsize;
Static long tabdsize[52];
Static long (*width)[129], (*height)[129];
Static unsigned short (*yoffset)[129], (*pwidth)[129], (*pheight)[129];
Static long dirpoint[129];
Static pxlstr pkpoint[129];
Static long hres, vres;
Static double truehres, truevres;
Static long noffonts, nofchars, mincharpf;
Static uchar charpf[53];
/*logfile,*/
Static FILE *texfile;
Static FILE *bitmap, *pxlfile, *tmpfil;
Static short filestat;
Static unsigned short gi;
Static boolean invert;
Static unsigned short cv, dv, lv;
Static Char comment[256];
Static Char aliasname[256];
Static boolean aliasused;
Static double mapdiv;
Static long pkwidth, pkheight;
Static boolean nowhite, halfinch;
Static pxlstr nextmemfree;
/*25:*/
Static ebts cutrep, outputbyte;
Static halfk cutlen;
Static boolean cutgrey;   /*:25*/
/*53:*/
Static Char tfmstr[256];
Static uchar tfmb;
Static FILE *tfmfile;
/*:53*/
/*56:*/
Static uchar *pxlbm;
Static pxlstr pxlbmi;
/*:56*/
/*58:*/
Static uchar *pkbm;
Static short *repbm;
Static pxlstr pkloc;
/*:58*/
/*62:*/
Static short bitweight;
/*:62*/
/*64:*/
Static ebts car;
/*:64*/
/*69:*/
Static short cxoff, cyoff;
/*:69*/
/*73:*/
Static short power[9];   /*:73*/
/*93:*/
Static double valinc, redval, grx, grxzero;
Static long gradint;
Static uchar *greymem;
Static long pgreymem;
Static boolean randomst, newrandom;
Static Char texfile_NAME[_FNSIZE];
Static Char bitmap_NAME[_FNSIZE];
Static Char pxlfile_NAME[_FNSIZE];
Static Char tmpfil_NAME[_FNSIZE];
Static Char tfmfile_NAME[_FNSIZE];


/*:93*/
/*:2*/
/*6:*/
Static uchar korrlastb(i, j)
uchar i;
short j;
{
  ebts k;

  k = 8 - j;
  if (k > 0) {
    i >>= k;
    i <<= k;
  }
  return i;
}


/*:6*/
/*7:*/
Static uchar pxladd(i, j, k)
uchar i, j;
short k;
{
  i = (i << k) & 255;
  j >>= k;
  return (i | j);
}


/*:7*/
/*8:*/
Static unsigned short getcolor()
{
  halfk j, k;
  unsigned short a, o;
  ebts savcol, lcol, rcol, l, r;

  if (cutgrey) {
    if ((cutrep & 127) == 0) {
      if (cutrep == 128)
	colpos++;
      cutrep = b1[(halfk)colpos];
      colpos++;
    }
    savcol = b1[(halfk)colpos];
    if (cutrep < 128)
      colpos++;
    cutrep--;
    return savcol;
  }
  a = colpos;
  colpos += bitspsam;
  o = a + bitspsam - 1;
  l = a & 7;
  r = (o + 1) & 7;
  k = o >> 3;
  j = a >> 3;
  lcol = b1[j];
  rcol = b1[k];
  if (k != j) {
    savcol = lcol << l;
    savcol = (savcol >> (l - r)) ^ (rcol >> (8 - r));
    return savcol;
  }
  savcol = lcol << l;
  savcol >>= l;
  if (r > 0)
    savcol >>= 8 - r;
  return savcol;
}


/*:8*/
/*10:*/
Static Void sepcols(cr, cg, cb)
uchar cr, cg, cb;
{
  colcyan = 255 - cr;
  colmagenta = 255 - cg;
  colyellow = 255 - cb;
  if (colcyan != colmagenta || colcyan != colyellow || colmagenta != colyellow) {
    colcyan -= colmagenta / 3;
    if (colcyan < 0)
      colcyan = 0;
    colmagenta -= colyellow / 3;
    if (colmagenta < 0)
      colmagenta = 0;
  }
  colblack = colcyan;
  if (colblack > colmagenta)
    colblack = colmagenta;
  if (colblack > colyellow)
    colblack = colyellow;
}


/*:10*/
/*11:*/
Static Char *numtostr(Result, i)
Char *Result;
long i;
{
  Char nstr[256];

  sprintf(nstr, "%ld", i);
  return strcpy(Result, nstr);
}


/*:9*/
/*10:*/
Static Void korrfont()
{
  uchar i, j;

  i = strpos2(font, "/", 1);
  while (i > 0) {
    strdelete((Anyptr)font, 1, i);
    i = strpos2(font, "/", 1);
  }
  j = strlen(font);
  i = strpos2(font, ".", 1);
  if (i != 0)
    strdelete((Anyptr)font, i, j - i + 1);
  if (strlen(font) > 7)
    font[7] = '\0';
}


/*:10*/
/*11:*/
Static Void whatistrue()
{
  hres = (long)floor(truehres + 0.5);
  vres = (long)floor(truevres + 0.5);
  if (halfinch) {
    hres /= 2;
    vres /= 2;
  }
  hres -= hres & 7;
  if (hres * vres <= 262136L)
    return;
  if (truehres > truevres) {
    hres = (long)sqrt(262136.0) - 31;
    vres = (long)(hres * truevres / truehres);
    return;
  }
  if (truevres > truehres) {
    vres = (long)sqrt(262136.0) - 31;
    hres = (long)(vres * truehres / truevres);
  } else {
    hres = (long)sqrt(262136.0) - 31;
    vres = hres;
  }
}  /*:11*/


/*12:*/
Static Void outfix(k)
long k;
{
  short a;
  long f;
  char j;
  long delta;
  union {
    ebts b[4];
    long i;
  } ax;
  char dig[12];

  ax.i = k;
#ifdef INTEL
  a = (long)ax.b[3] * 16 + ax.b[2] / 16;
  f = ((ax.b[2] & 15) * 256 + ax.b[1]) * 256 + ax.b[0];
#else
  a = (long)ax.b[0] * 16 + ax.b[1] / 16;
  f = ((ax.b[1] & 15) * 256 + ax.b[2]) * 256 + ax.b[3];
#endif
  if (a > 2047) {
    putc('-', texfile);
    a = 4096 - a;
    if (f > 0) {
      f = 1048576L - f;
      a--;
    }
  }
  j = 0;
  do {
    dig[j] = a % 10;
    a /= 10;
    j++;
  } while (a != 0);
  do {
    j--;
    fprintf(texfile, "%d", dig[j]);
  } while (j != 0);
  putc('.', texfile);
  f = f * 10 + 5;
  delta = 10;
  do {
    if (delta > 1048576L)
      f += 524288L - delta / 2;
    fprintf(texfile, "%ld", f / 1048576L);
    f = f % 1048576L * 10;
/* p2c: bm2font.pas, line 102:
 * Note: Using % for possibly-negative arguments [317] */
    delta *= 10;
  } while (f > delta);
}


/*:12*/
/*13:*/
Static Void fileproblem()
{
  printf("file-error %d : ", filestat);
  switch (filestat) {

  case 2:
    printf("file not found");
    break;

  case 3:
    printf("path not found");
    break;

  case 4:
    printf("too many files open");
    break;

  case 5:
    printf("file access denied");
    break;

  case 6:
    printf("invalid file handle");
    break;

  case 12:
    printf("invalid file access mode");
    break;

  case 15:
    printf("invalid drive number");
    break;

  case 101:
    printf("disk full");
    break;

  default:
    printf("ask a tpc guru");
    break;
  }
  printf("!\n");
  if (pcxtemp)
/* p2c: bm2font.pas, line 112: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "pcxtemp.tmp");
#else
    Exec("rm", "pcxtemp.tmp");
#endif
  if (giftemp)
/* p2c: bm2font.pas, line 112: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "giftemp.tmp");
#else
    Exec("rm", "giftemp.tmp");
#endif
  if (greypxl)
/* p2c: bm2font.pas, line 112: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", tmpname);
#else
    Exec("rm", tmpname);
#endif
}


/*:13*/
/*14:*/
Static Void opentempfile()
{
  strcpy(tmpname, "pcxtemp.tmp");
  strcpy(tmpfil_NAME, "pcxtemp.tmp");
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {
    printf("tempfile pcxtemp.tmp not accessable, abort\n");
    fileproblem();
    _Escape(0);
  }
  if (tmpfil != NULL)
    tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
  else
    tmpfil = fopen(tmpfil_NAME, "w+b");
  _SETIO(tmpfil != NULL, FileNotFound);
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (!fok)
    return;
  printf("Unable to create pcxtmp.tmp, abort\n");
  fileproblem();
  _Escape(0);
}


/*:14*/
/*15:*/
Static Void picstretch()
{
  short FORLIM;

  printf("Stretching the picture because of odd aspect ratio\n");
  posbit = 0;
  giftemp = true;
  strcpy(tmpname, "giftemp.tmp");
  strcpy(tmpfil_NAME, "giftemp.tmp");
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {
    printf("tempfile giftemp.tmp not accessable, abort\n");
    fileproblem();
    _Escape(0);
  }
  if (tmpfil != NULL)
    tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
  else
    tmpfil = fopen(tmpfil_NAME, "w+b");
  if (tmpfil == NULL)
    _EscIO(FileNotFound);
  while (!P_eof(bitmap)) {
    fread(b1, mapinlen, 1, bitmap);
    if (posbit == xratio) {
      if (bitspsam == 8) {
	FORLIM = mapinlen;
	for (gbufp = 0; gbufp < FORLIM; gbufp++)
	  b3[gbufp] = ((unsigned)(b3[gbufp] + b1[gbufp])) >> 1;
      } else if (bitspsam == 4) {
	FORLIM = mapinlen;
	for (gbufp = 0; gbufp < FORLIM; gbufp++) {
	  b = ((unsigned)((b3[gbufp] >> 4) + (b1[gbufp] >> 4))) >> 1;
	  c = ((unsigned)((b3[gbufp] & 15) + (b1[gbufp] & 15))) >> 1;
	  b3[gbufp] = (b << 4) + c;
	}
      }
/* p2c: bm2font.pas, line 131:
 * Note: Can't interpret size in BLOCKWRITE [174] */
      _SETIO(fwrite(b3, mapinlen, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
      posbit = 0;
    }
    posbit++;
    if (posbit == xratio) {
      FORLIM = mapinlen;
      for (gbufp = 0; gbufp < FORLIM; gbufp++)
	b3[gbufp] = b1[gbufp];
    }
/* p2c: bm2font.pas, line 135:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    _SETIO(fwrite(b1, mapinlen, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
  }
/* p2c: bm2font.pas, line 126:
 * Note: Can't interpret size in BLOCKREAD [174] */
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  strcpy(bitmap_NAME, "giftemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "r+b", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "r+b");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  posbit = 0;
  cutgrey = false;
  if (pcxtemp) {
/* p2c: bm2font.pas, line 140: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "pcxtemp.tmp");
#else
    Exec("rm", "pcxtemp.tmp");
#endif
    pcxtemp = false;
  }
}


/*:15*/
/*16:*/
Static Void scaling()
{  /*17:*/
  long newh, newv, counth, countv;
  double scaleh, scalev, ledfac, repfac;
  boolean grver, grhor, remlast;
  short FORLIM;

  if (ledprinter)
    ledfac = 0.5;
  else
    ledfac = 0.0;
  if (hrep != 1)
    repfac = 2.0;
  else
    repfac = 1.0;
  if (!greypxl) {
    usepxl = 1;
    vusepxl = 1;
    bitspsam = 1;
  }
  if (newwidth != 0)
    newwidth = (long)floor(
	  newwidth * truehres / 25.4 / (repfac * (usepxl + ledfac)) + 0.5);
  if (newheight != 0)
    newheight = (long)floor(
	  newheight * truevres / 25.4 / (repfac * (vusepxl + ledfac)) + 0.5);
  if (newheight == 0)
    newheight = (long)floor((double)mapheight / mapwidth * newwidth + 0.5);
  if (newwidth == 0)
    newwidth = (long)floor((double)mapwidth / mapheight * newheight + 0.5);
  printf("Scaling the picture from %dx%d", mapwidth, mapheight);
  printf(" to %ldx%ld pixels\n", newwidth, newheight);
  grver = (newheight > mapheight);
  grhor = (newwidth > mapwidth);
  if (grhor)
    scaleh = newwidth / (newwidth - mapwidth + 1.0);
  else
    scaleh = mapwidth / (mapwidth - newwidth + 1.0);
  if (grver)   /*:17*/
    scalev = newheight / (newheight - mapheight + 1.0);
  else
    scalev = mapheight / (mapheight - newheight + 1.0);
  /*18:*/
  if (giftemp)
    strcpy(tmpname, "pcxtemp.tmp");
  else
    strcpy(tmpname, "giftemp.tmp");
  strcpy(tmpfil_NAME, tmpname);
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {
    printf("tempfile %s not accessable, abort\n", tmpname);
    fileproblem();
    _Escape(0);
  }
  if (tmpfil != NULL)
    tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
  else
    tmpfil = fopen(tmpfil_NAME, "w+b");
  if (tmpfil == NULL)
    _EscIO(FileNotFound);
  /*:18*/
  pxlinlen = (halfk)(((unsigned long)(mapwidth * bitspsam + 7)) >> 3);
  greypix = mapwidth;
  if (cutgrey) {
    checksum = mapheight;
    pxlinlen = cutlen;
  } else
    checksum = mapheight;
  pl = 0;
  fseek(bitmap, posbit, 0);
  for (pk = 0; pk <= 255; pk++)
    lutsl[pk] = pk << (8 - bitspsam);
  newv = 1;
  countv = 0;
  remlast = false;
  do {
    pxlinlen = fread(b1, 1, pxlinlen, bitmap);
    colpos = 0;
    cutrep = 0;
    gbufpp = (newwidth * bitspsam + 7) / 8;
    memset((Anyptr)b4, invbyte, sizeof(uchar) * 1500L);
    FORLIM = greypix;
    for (pk = 0; pk < FORLIM; pk++)
      b4[pk] = getcolor();
    if (remlast) {
      FORLIM = greypix;
      for (pk = 0; pk < FORLIM; pk++)
	b4[pk] = (b2[pk] * 2 + b4[pk]) / 3;
      remlast = false;
    }
    gbufp = 0;
    cb = 0;
/* p2c: bm2font.pas, line 172:
 * Note: Can't interpret size in FILLCHAR [174] */
    memset((Anyptr)b3, invbyte, (long)gbufpp);
    newh = 1;
    counth = 0;
    pk = 0;
    while (pk < greypix) {   /*19:*/
      cb = lutsl[b4[pk]];
      dbuf = ((unsigned)gbufp) >> 3;
      bufsh = gbufp & 7;
      nextbuf = bufsh + bitspsam;
      switch (bufsh) {

      case 0:
	b3[dbuf] = cb;
	break;

      default:
	b3[dbuf] ^= cb >> bufsh;
	if (nextbuf > 8)
	  b3[dbuf + 1] = cb << (8 - bufsh);
	break;
      }
      gbufp += bitspsam;
      pk++;
      counth++;
      if (counth != (long)floor(newh * scaleh + 0.5))
	continue;
      if (grhor) {
	while (counth >= (long)floor(newh * scaleh + 0.5)) {
	  if (pk == greypix)
	    cb = lutsl[(b4[pk - 1] * 2 + b4[pk - 2]) / 3];
	  else
	    cb = lutsl[(b4[pk] * 2 + b4[pk - 1]) / 3];
	  dbuf = ((unsigned)gbufp) >> 3;
	  bufsh = gbufp & 7;
	  nextbuf = bufsh + bitspsam;
	  switch (bufsh) {

	  case 0:
	    b3[dbuf] = cb;
	    break;

	  default:
	    b3[dbuf] ^= cb >> bufsh;
	    if (nextbuf > 8)
	      b3[dbuf + 1] = cb << (8 - bufsh);
	    break;
	  }
	  gbufp += bitspsam;
	  counth++;
	  newh++;
	}
	continue;
      }
      while (counth == (long)floor(newh * scaleh + 0.5)) {
	b4[pk + 1] = (b4[pk + 1] * 2 + b4[pk]) / 3;
	pk++;
	newh++;
	counth++;
      }
    }  /*:19*/
    if (bitspsam == 1) {
      dbuf = ((unsigned)gbufp) >> 3;
      bufsh = gbufp & 7;
      if (dbuf < gbufpp) {
	cb = invbyte;
	b3[dbuf] ^= cb >> bufsh;
      }
    }
/* p2c: bm2font.pas, line 191:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    fwrite(b3, gbufpp, 1, tmpfil);
    checksum--;   /*20:*/
    countv++;
    if (cutgrey)
      pxlinlen = (halfk)(b1[pxlinlen - 1] * 256 + b1[pxlinlen - 2] + 2);
    if (countv == (long)floor(newv * scalev + 0.5)) {   /*:20*/
      if (grver) {
	while (countv >= (long)floor(newv * scalev + 0.5)) {
	  fwrite(b3, gbufpp, 1, tmpfil);
	  countv++;
	  newv++;
	}
/* p2c: bm2font.pas, line 194:
 * Note: Can't interpret size in BLOCKWRITE [174] */
      } else {
	while (countv == (long)floor(newv * scalev + 0.5)) {
	  pxlinlen = fread(b1, 1, pxlinlen, bitmap);
	  colpos = 0;
	  cutrep = 0;
	  FORLIM = greypix;
	  for (pk = 0; pk < FORLIM; pk++)
	    b2[pk] = getcolor();
	  remlast = true;
	  if (checksum > 0)
	    checksum--;
	  if (cutgrey)
	    pxlinlen = (halfk)(b1[pxlinlen - 1] * 256 + b1[pxlinlen - 2] + 2);
	  newv++;
	  countv++;
	}
/* p2c: bm2font.pas, line 196:
 * Note: Can't interpret size in BLOCKREAD [174] */
      }
    }
  } while (checksum != 0);
/* p2c: bm2font.pas, line 168:
 * Note: Can't interpret size in BLOCKREAD [174] */
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;   /*21:*/
  if (giftemp) {   /*:21*/
/* p2c: bm2font.pas, line 206: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "giftemp.tmp");
#else
    Exec("rm", "giftemp.tmp");
#endif
    giftemp = false;
    pcxtemp = true;
  } else {
/* p2c: bm2font.pas, line 206: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "pcxtemp.tmp");
#else
    Exec("rm", "pcxtemp.tmp");
#endif
    giftemp = true;
    pcxtemp = false;
  }
  strcpy(bitmap_NAME, tmpname);
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "r+b", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "r+b");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  posbit = 0;
  cutgrey = false;
  mapheight = newheight;
  mapwidth = newwidth;
  if (bitspsam == 1)
    pxlinlen = (mapwidth + 7) / 8;
  mapheight = (P_maxpos(bitmap)) / ((mapwidth * bitspsam + 7) / 8);
}  /*:16*/


/* Local variables for tifint: */
struct LOC_tifint {
  boolean le;
  uchar tb[3000];
} ;

/*:22*/
/*23:*/
Local unsigned short tifword(ba, LINK)
unsigned short ba;
struct LOC_tifint *LINK;
{
  if (LINK->le)
    return ((unsigned short)LINK->tb[ba] + (unsigned short)LINK->tb[ba + 1] * 256);
  else
    return ((unsigned short)(LINK->tb[ba] * 256) +
	    (unsigned short)LINK->tb[ba + 1]);
}

Local long tiflong(ba, LINK)
unsigned short ba;
struct LOC_tifint *LINK;
{
  if (LINK->le)
    return ((long)tifword(ba, LINK) + (long)tifword(ba + 2, LINK) * 65536L);
  else
    return (LINK->tb[ba] * 16777216 + LINK->tb[ba + 1] * 65536 +
	    LINK->tb[ba + 2] * 256 + (long)LINK->tb[ba + 3]);
}

Local unsigned short tiftwobyte(ba, LINK)
unsigned short ba;
struct LOC_tifint *LINK;
{
  if (LINK->le)
    return ((unsigned short)LINK->tb[ba] + (unsigned short)LINK->tb[ba + 1] * 256);
  else
    return ((unsigned short)(LINK->tb[ba] * 256) +
	    (unsigned short)LINK->tb[ba + 1]);
}


/*22:*/
Static Void tifint()
{   /*:23*/
  struct LOC_tifint V;
  unsigned short i, j, l, m, tl;
  long ll;
  uchar tp;
  boolean strips, tiffrgb;
  unsigned short ttype;
  long tiftemp;
  ebts tiffbuf[3];
  unsigned short FORLIM;
  uchar FORLIM1;
  unsigned short FORLIM2;

  /*24:*/
  strips = false;
  tl = fread(V.tb, 1, sizeof(uchar) * 1199, bitmap);
  V.le = (V.tb[1] == 'I');
  ll = tiflong(4, &V);
  if (ll > 900) {
    printf("I can't digest this\n");
    _Escape(0);
  }
  l = ll;
  m = tiftwobyte(l, &V);
  l += 2;
  for (i = 1; i <= m; i++) {
    j = tiftwobyte(l, &V);
    ttype = tiftwobyte(l + 2, &V);
    if (ttype == 3)
      tiftemp = tifword(l + 8, &V);
    else
      tiftemp = tiflong(l + 8, &V);
    switch (j) {

    case 256:
      mapwidth = tiftemp;
      break;

    case 257:
      mapheight = tiftemp;
      break;

    case 258:
      if (tiftemp > 1) {
	greypxl = true;
	bitspsam = tiftemp;
	if (bitspsam > 8) {
	  printf("Assuming 8 greyshades\n");
	  bitspsam = 8;
	}
	mapdiv = 1.0;
	FORLIM1 = bitspsam;
	for (tp = 1; tp <= FORLIM1; tp++)
	  mapdiv *= 2;
	mapdiv /= 16;
      }
      break;

    case 259:
      if (tiftemp > 1) {
	printf("No compression supported\n");
	_Escape(0);
      }
      break;

    case 262:
      photoinf = tiftemp;
      if (photoinf > 1)
	tiffrgb = true;
      else
	tiffrgb = false;
      if (photoinf == 0)
	invert = !invert;
      if (invert) {
	invbit = 0;
	invbyte = 0;
      } else {
	invbit = 1;
	invbyte = 255;
      }
      photoinf = 15;
      break;

    case 273:
      if (tiflong(l + 4, &V) != 1)
	strips = true;
      posbit = tiftemp;
      break;

    case 277:
      if (tiftemp == 3)
	tiffrgb = true;
      else
	tiffrgb = false;
      break;

    case 278:
      rowspstrip = tiftemp;
      break;

    case 290:
      greyunit = 1.0;
      FORLIM1 = tifword(l + 4, &V);
      for (tp = 1; tp <= FORLIM1; tp++)
	greyunit /= 10;
      break;

    case 291:
      FORLIM1 = tiflong(l + 4, &V);
      for (tp = 0; tp < FORLIM1; tp++)
	tpal[tp] = V.tb[l + tp + 8];
      break;
    }
    l += 12;
    if (l >= tl) {
      tl = fread(V.tb, 1, sizeof(uchar) * 1199, bitmap);
      l = 0;
    }
  }
  if (strips) {
    fseek(bitmap, posbit, 0);
    l = fread(V.tb, 1, sizeof(uchar) * 2, bitmap);
    posbit = tiflong(0, &V);
  }
  if (!tiffrgb)
    return;
  opentempfile();
  fseek(bitmap, posbit, 0);
  FORLIM = mapheight;
  for (j = 1; j <= FORLIM; j++) {
    FORLIM2 = mapwidth;
    for (i = 0; i < FORLIM2; i++) {
      l = fread(tiffbuf, 1, 3, bitmap);
      if (cmyk) {
	sepcols(tiffbuf[0], tiffbuf[1], tiffbuf[2]);
	if (cyan)
	  b3[i] = 255 - colcyan;
	if (magenta)
	  b3[i] = 255 - colmagenta;
	if (yellow)
	  b3[i] = 255 - colyellow;
	if (black)
	  b3[i] = 255 - colblack;
      } else
	b3[i] = (long)floor(tiffbuf[0] * 0.287 + tiffbuf[1] * 0.589 +
			    tiffbuf[2] * 0.114 + 0.5);
    }
/* p2c: bm2font.pas, line 244:
 * Note: Can't interpret size in BLOCKREAD [174] */
/* p2c: bm2font.pas, line 257:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    fwrite(b3, mapwidth, 1, tmpfil);
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "r+b", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "r+b");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  posbit = 0;
  pcxtemp = true;
  mapinlen = mapwidth;
}


/*:24*/
/*26:*/
Static Void cutint()
{
  long FORLIM;
  short FORLIM1;

  pxlinlen = 8;
/* p2c: bm2font.pas, line 241:
 * Note: Can't interpret size in BLOCKREAD [174] */
  pxlinlen = fread(b1, 1, pxlinlen, bitmap);
  if (pxlinlen != 8) {
    printf("CUT file too small!\n");
    _Escape(0);
  }
  mapheight = b1[3] * 256 + b1[2];
  mapwidth = b1[1] * 256 + b1[0];
  photoinf = 15;
  mapdiv = 16.0;
  posbit = 8;
  cutlen = b1[7] * 256 + b1[6] + 2;
  bitspsam = 8;
  cutgrey = true;
  greypxl = true;
  if (!egastretch)
    return;
  mapinlen = mapwidth;
  printf("Shrinking the CUT picture because of odd aspect ratio\n");
  giftemp = true;
  strcpy(tmpname, "giftemp.tmp");
  strcpy(tmpfil_NAME, "giftemp.tmp");
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {
    printf("tempfile giftemp.tmp not accessable, abort\n");
    fileproblem();
    _Escape(0);
  }
  if (tmpfil != NULL)
    tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
  else
    tmpfil = fopen(tmpfil_NAME, "w+b");
  if (tmpfil == NULL)
    _EscIO(FileNotFound);
  xratio = 2;
  posbit = 0;
  pxlinlen = cutlen;
  FORLIM = mapheight;
  for (checksum = 1; checksum <= FORLIM; checksum++) {
    pxlinlen = fread(b1, 1, pxlinlen, bitmap);
    colpos = 0;
    cutrep = 0;
    FORLIM1 = mapinlen;
    for (pk = 0; pk < FORLIM1; pk++)
      b2[pk] = getcolor();
    posbit++;
    FORLIM1 = mapinlen;
    for (gbufp = 0; gbufp < FORLIM1; gbufp++)
      b3[gbufp] = b2[gbufp];
    if (posbit < xratio) {
      _SETIO(fwrite(b2, mapinlen, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
    }
/* p2c: bm2font.pas, line 256:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    if (posbit > xratio) {
      FORLIM1 = mapinlen;
      for (gbufp = 0; gbufp < FORLIM1; gbufp++)
	b3[gbufp] = ((unsigned)(b3[gbufp] + b2[gbufp])) >> 1;
/* p2c: bm2font.pas, line 261:
 * Note: Can't interpret size in BLOCKWRITE [174] */
      _SETIO(fwrite(b3, mapinlen, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
      posbit = 0;
      if (xratio == 2)
	xratio = 3;
      else
	xratio = 2;
    }
    pxlinlen = (halfk)(b1[pxlinlen - 1] * 256 + b1[pxlinlen - 2] + 2);
  }
/* p2c: bm2font.pas, line 253:
 * Note: Can't interpret size in BLOCKREAD [174] */
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  strcpy(bitmap_NAME, "giftemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "r+b", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "r+b");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  cutgrey = false;
  posbit = 0;
}


typedef unsigned short tabcode[4097];
typedef uchar bytecod[4097];
typedef uchar ilaced[4];
typedef uchar ebts_;


typedef long gifmask[13];


/* Local variables for gifint: */
struct LOC_gifint {
  ilaced ioff, ijump;
  long lvr, linepos;
  ebts_ logvr, codesample, modus, gifshift, nextbuf, bufsh;
  unsigned short maxcode, hh;
  short ec, ki;
  unsigned short hell[256];
  ebts_ gifbuf[3000];
  unsigned short codepos, gifinlen, gotinlen;
  long codesav;
  unsigned short dbuf, linebytes;
} ;

/*:27*/
/*28:*/
Local uchar getgif(LINK)
struct LOC_gifint *LINK;
{
/* p2c: bm2font.pas, line 279:
 * Note: Can't interpret size in BLOCKREAD [174] */
  fread(b1, 1, 1, bitmap);
  return (b1[0]);
}

Local Void gifout(b, LINK)
unsigned short b;
struct LOC_gifint *LINK;
{
  short i, FORLIM;
  ebts_ ibits;

  if (gbufpp < 3000)
    b2[gbufpp] = LINK->hell[b];
  gbufpp++;
  if (gbufpp != LINK->hh)
    return;
  LINK->codepos = 0;
/* p2c: bm2font.pas, line 282:
 * Note: Can't interpret size in FILLCHAR [174] */
  memset((Anyptr)LINK->gifbuf, invbyte, 3000L);
  FORLIM = LINK->hh;
  for (i = 0; i < FORLIM; i++) {
    LINK->dbuf = LINK->codepos / 8;
    LINK->bufsh = LINK->codepos & 7;
    LINK->nextbuf = LINK->bufsh + bitspsam;
    cb = lutsl[b2[i]];
    if (LINK->bufsh == 0)
      LINK->gifbuf[LINK->dbuf] = cb;
    else {
      LINK->gifbuf[LINK->dbuf] |= cb >> LINK->bufsh;
      if (LINK->nextbuf > 8)
	LINK->gifbuf[LINK->dbuf + 1] = cb << (8 - LINK->bufsh);
    }
    LINK->codepos += bitspsam;
  }
  if (LINK->modus == 1)
    fseek(tmpfil, LINK->linepos, 0);
  if (bitspsam == 1) {
    i = 8 - (LINK->hh & 7);
    if (i != 8) {
      cb = LINK->gifbuf[LINK->dbuf] >> i;
      cb <<= i;
      LINK->gifbuf[LINK->dbuf] = cb;
      cb = invbit;
      for (ibits = 1; ibits <= i; ibits++) {
	LINK->gifbuf[LINK->dbuf] ^= cb;
	cb <<= 1;
      }
    }
  }
/* p2c: bm2font.pas, line 291:
 * Note: Can't interpret size in BLOCKWRITE [174] */
  _SETIO(fwrite(LINK->gifbuf, LINK->linebytes, 1, tmpfil) == 1,
	 FileWriteError);
  filestat = P_ioresult;
  if (filestat != 0) {
    _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	   FileWriteError);
    fileproblem();
    _Escape(0);
  }
  LINK->lvr++;
  gbufpp = 0;
  LINK->linepos += LINK->linebytes * LINK->ijump[LINK->logvr];
  if (LINK->linepos >= P_maxpos(tmpfil)-1) {
    LINK->logvr++;
    LINK->linepos = LINK->ioff[LINK->logvr] * LINK->linebytes;
  }
}

Local unsigned short gifcode(LINK)
struct LOC_gifint *LINK;
{
  unsigned short Result;

  static gifmask codemask = {
    0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095
  };

  long codebyte;

  while (LINK->gifshift < LINK->codesample) {
    codebyte = b1[gbufp];
    gbufp++;
    if (gbufp == LINK->gifinlen) {
      LINK->gifinlen = getgif(LINK);
/* p2c: bm2font.pas, line 303:
 * Note: Can't interpret size in BLOCKREAD [174] */
      LINK->gotinlen = fread(b1, 1, LINK->gifinlen, bitmap);
      gbufp = 0;
      if (LINK->gifinlen == 0)
	printf("Code zero, proceeding\n");
      if (LINK->gotinlen != LINK->gifinlen) {
	b1[LINK->gotinlen] = LINK->ec;
	LINK->gifinlen = LINK->gotinlen + 1;
      }
    }
    LINK->codesav |= codebyte << LINK->gifshift;
    LINK->gifshift += 8;
  }
  Result = LINK->codesav & codemask[LINK->codesample];
  LINK->codesav = ((unsigned long)LINK->codesav) >> LINK->codesample;
  LINK->gifshift -= LINK->codesample;
  LINK->ki++;
  if (LINK->ki > LINK->maxcode && LINK->codesample < 12) {
    LINK->codesample++;
    LINK->maxcode = 1 << LINK->codesample;
  }
  return Result;
}


/*:26*/
/*27:*/
Static Void gifint()
{   /*:28*/
  struct LOC_gifint V;

  static ilaced ioff = {
    0, 4, 2, 1
  };

  static ilaced ijump = {
    8, 8, 4, 2
  };

  unsigned short a, g, hi, vi, vh, hr, vr;
  short merk, ic, codegif, i;
  ebts_ colmap, b, col, bpp;
  ebts_ gpal[256][3];
  unsigned short *codtab;
  unsigned short folge, minhell, maxhell;
  uchar *anf;
  Char hexbyte[7];
  short FORLIM;

  /*29:*/
  memcpy(V.ioff, ioff, sizeof(ilaced));
  memcpy(V.ijump, ijump, sizeof(ilaced));
  printf("Decoding GIF file\n");
  V.logvr = 0;
  V.codesav = 0;
  V.lvr = 0;
  minhell = 9999;
  maxhell = 0;
  codtab = (unsigned short *)Malloc(sizeof(tabcode));
  anf = (uchar *)Malloc(sizeof(bytecod));
  opentempfile();
  *hexbyte = '\0';
  for (i = 1; i <= 3; i++) {
    sprintf(hexbyte + strlen(hexbyte), "%c", getgif(&V));
/* p2c: bm2font.pas, line 313:
 * Note: Possible string truncation in assignment [145] */
  }
  if (strcmp(hexbyte, "GIF")) {
    printf("This file is NOT a gif file!\n");
    _Escape(0);
  }
  for (i = 1; i <= 3; i++) {
    sprintf(hexbyte + strlen(hexbyte), "%c", getgif(&V));
/* p2c: bm2font.pas, line 315:
 * Note: Possible string truncation in assignment [145] */
  }
  if (strcmp(hexbyte, "GIF87a") && strcmp(hexbyte, "GIF89a")) {
    printf("The program only supports version 87a and 89a!\n");
    _Escape(0);
  }
  b = getgif(&V);
  hr = b;
  b = getgif(&V);
  hr += b * 256;
  b = getgif(&V);
  vr = b;
  b = getgif(&V);
  vr += b * 256;
  if (hr == 640 && vr == 350) {
    xratio = 3;
    yratio = 4;
  }
  b = getgif(&V);
  colmap = b & 128;
  colmap >>= 7;
  col = b & 112;
  col >>= 4;
  col++;
  bitspsam = b & 7;
  bitspsam++;
  b = getgif(&V);
  b = getgif(&V);
  if (colmap == 1) {   /*30:*/
    g = 1;
    FORLIM = bitspsam;
    for (i = 1; i <= FORLIM; i++)
      g *= 2;
    for (i = 0; i < g; i++) {
      for (j = 0; j <= 2; j++)
	gpal[i][j] = getgif(&V);
      if (cmyk) {
	sepcols(gpal[i][0], gpal[i][1], gpal[i][2]);
	if (cyan)
	  V.hell[i] = 255 - colcyan;
	if (magenta)
	  V.hell[i] = 255 - colmagenta;
	if (yellow)
	  V.hell[i] = 255 - colyellow;
	if (black)
	  V.hell[i] = 255 - colblack;
	bhell[V.hell[i]] = 255 - colblack;
      } else
	V.hell[i] = (long)floor(gpal[i][0] * 0.287 + gpal[i][1] * 0.589 + gpal[i]
				  [2] * 0.114 + 0.5);
      if (V.hell[i] > maxhell)
	maxhell = V.hell[i];
    }
    if (bitspsam > 1) {
      for (i = 0; i < g; i++)
	V.hell[i] = (long)floor((double)V.hell[i] / maxhell * (g - 1) + 0.5);
      for (i = 0; i < g; i++)
	bhell[i] = (long)floor((double)bhell[i] / maxhell * (g - 1) + 0.5);
    } else {
      V.hell[0] = 0;
      V.hell[1] = 1;
      bhell[0] = 0;
      bhell[1] = 1;
    }
  }
  b = getgif(&V);
  if (b != 44) {   /*31:*/
    while (b != 44) {   /*:31*/
      b = getgif(&V);
      switch (b) {

      case 249:
	a = getgif(&V);
	for (g = 0; g <= a; g++)
	  b = getgif(&V);
	break;

      case 254:
	a = getgif(&V);
	while (a != 0) {
	  for (g = 0; g <= a; g++)
	    b = getgif(&V);
	  a = b;
	  if (P_eof(bitmap)) {
	    printf("file ended while looking for image\n");
	    _Escape(0);
	  }
	}
	break;

      case 1:
      case 255:
	a = getgif(&V);
	for (g = 1; g <= a; g++)
	  b = getgif(&V);
	a = getgif(&V);
	while (a != 0) {
	  for (g = 0; g <= a; g++)
	    b = getgif(&V);
	  a = b;
	  if (P_eof(bitmap)) {
	    printf("file ended while looking for image\n");
	    _Escape(0);
	  }
	}
	break;
      }
      b = getgif(&V);
      if (P_eof(bitmap)) {
	printf("file ended while looking for image\n");
	_Escape(0);
      }
    }
  }
  b = getgif(&V);
  hi = b;
  b = getgif(&V);
  hi += b * 256;
  b = getgif(&V);
  vi = b;
  b = getgif(&V);
  vi += b * 256;
  b = getgif(&V);
  V.hh = b;
  b = getgif(&V);
  V.hh += b * 256;
  b = getgif(&V);
  vh = b;
  b = getgif(&V);
  vh += b * 256;
  if (V.hh != hr || vh != vr)
    printf("No fragments supported!\n");
  V.linebytes = (V.hh * bitspsam + (bitspsam - 1)+7) / 8;
  if (V.linebytes > 3000) {
    V.linebytes = 3000;
    printf("Sorry, had to cut picture to a width of 3000 bytes\n");
  }
  b = getgif(&V);
  col = b & 128;
  col >>= 7;
  if (col != 0) {
    bitspsam = b & 7;
    bitspsam++;   /*30:*/
    g = 1;
    FORLIM = bitspsam;
    for (i = 1; i <= FORLIM; i++)
      g *= 2;
    for (i = 0; i < g; i++) {
      for (j = 0; j <= 2; j++)
	gpal[i][j] = getgif(&V);
      if (cmyk) {
	sepcols(gpal[i][0], gpal[i][1], gpal[i][2]);
	if (cyan)
	  V.hell[i] = 255 - colcyan;
	if (magenta)
	  V.hell[i] = 255 - colmagenta;
	if (yellow)
	  V.hell[i] = 255 - colyellow;
	if (black)
	  V.hell[i] = 255 - colblack;
	bhell[V.hell[i]] = 255 - colblack;
      } else
	V.hell[i] = (long)floor(gpal[i][0] * 0.287 + gpal[i][1] * 0.589 + gpal[i]
				  [2] * 0.114 + 0.5);
      if (V.hell[i] > maxhell)
	maxhell = V.hell[i];
    }
    for (i = 0; i < g; i++)
      V.hell[i] = (long)floor((double)V.hell[i] / maxhell * (g - 1) + 0.5);
    for (i = 0; i < g; i++)   /*:30*/
      bhell[i] = (long)floor((double)bhell[i] / maxhell * (g - 1) + 0.5);
  }
  for (pk = 0; pk <= 255; pk++)
    lutsl[pk] = pk << (8 - bitspsam);
  V.modus = b << 1;
  V.modus >>= 7;
  if (V.modus == 0)
    printf("Image is loaded sequentially.\n");
  else
    printf("Interlaced mode, loading the image will take more time.\n");
  if (V.modus != 0) {
    memset((Anyptr)V.gifbuf, invbyte, 3000L);
    for (i = 1; i <= vh; i++) {
      _SETIO(fwrite(V.gifbuf, V.linebytes, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
    }
/* p2c: bm2font.pas, line 379:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    V.linepos = 0;
    V.logvr = 0;
    fseek(tmpfil, 0L, 0);
  }
/* p2c: bm2font.pas, line 378:
 * Note: Can't interpret size in FILLCHAR [174] */
  bpp = b << 5;
  bpp >>= 5;
  bpp++;
  bpp = getgif(&V);
  g = 1 << bpp;
  ic = 1 << bpp;
  V.ec = ic + 1;
  V.codesample = bpp + 1;
  V.maxcode = 1 << V.codesample;
  for (i = 0; i <= 4095; i++)
    codtab[i] = 4098;
  V.ki = V.ec + 1;
  a = 4098;
  gbufpp = 0;
  V.gifshift = 0;
  V.gifinlen = getgif(&V);
/* p2c: bm2font.pas, line 387:
 * Note: Can't interpret size in BLOCKREAD [174] */
  fread(b1, V.gifinlen, 1, bitmap);
  gbufp = 0;
  if (V.gifinlen == 0)
    _Escape(0);
  merk = 0;   /*32:*/
  while (V.lvr < vh) {   /*:32*/
    codegif = gifcode(&V);
    if (codegif == V.ec) {
      printf("End of code before gif image completed!\n");
      V.lvr = vh;
      continue;
    }
    if (codegif == ic) {
      for (i = 0; i <= 4095; i++)
	codtab[i] = 4098;
      V.ki = V.ec + 1;
      V.codesample = bpp + 1;
      V.maxcode = 1 << V.codesample;
      a = 4098;
      continue;
    }
    if (codegif < ic)
      gifout(codegif, &V);
    else {
      if (codtab[codegif] == 4098) {
	if (codegif != V.ki - 2) {
	  printf("Bytes are mangled!\n");
	  _Escape(0);
	}
	folge = a;
	merk++;
	while (folge > ic)
	  folge = codtab[folge];
	b3[merk] = folge;
	anf[V.ki - 2] = folge;
	folge = a;
      } else
	folge = codegif;
      while (folge > ic && folge <= 4095) {
	merk++;
	b3[merk] = anf[folge];
	folge = codtab[folge];
      }
      merk++;
      b3[merk] = folge;
      while (merk > 0) {
	gifout(b3[merk], &V);
	merk--;
      }
    }
    if (a != 4098) {
      codtab[V.ki - 2] = a;
      if (codegif == V.ki - 2) {
	folge = a;
	while (folge > ic)
	  folge = codtab[folge];
	anf[V.ki - 2] = folge;
      } else {
	folge = codegif;
	while (folge > ic)
	  folge = codtab[folge];
	anf[V.ki - 2] = folge;
      }
    }
    a = codegif;
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  if (bitspsam > 1)
    greypxl = true;
  mapinlen = V.linebytes;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "r+b", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "r+b");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  pcxtemp = true;
  if (egastretch) {
    if (xratio + 1 == yratio)
      picstretch();
  }
  posbit = 0;
  mapdiv = 1.0;
  FORLIM = bitspsam;
  for (i = 1; i <= FORLIM; i++)
    mapdiv *= 2;
  mapdiv /= 16;
}


/*:29*/
/*33:*/
Static uchar getpcx()
{
  uchar Result;

  if (gbufp == pxlinlen) {
    gbufp = 0;
    pxlinlen = fread(b1, 1, sizeof(uchar) * 320, bitmap);
  }
  Result = b1[gbufp];
  gbufp++;
  return Result;
}


/*:33*/
/*34:*/
Static long longpcx()
{
  long bl;
  ebts pb;

  pb = getpcx();
  bl = pb;
  pb = getpcx();
  bl += pb * 256;
  pb = getpcx();
  bl += pb * 65536;
  pb = getpcx();
  bl += pb * 16777216;
  return bl;
}


/*:34*/
/*35:*/
Static unsigned short wordpcx()
{
  unsigned short bl;
  ebts pb;

  pb = getpcx();
  bl = pb;
  pb = getpcx();
  bl += pb * 256;
  return bl;
}  /*:35*/


/*36:*/
Static Void pcxint()
{
  unsigned short i, ki, k, hi, hh, vi, vh, hr, vr, bzf;
  ebts xb, j, b, a, col, bps, ibits, pcxver, pcxcomp;
  ebts gpal[256][3];
  unsigned short hell[256];
  unsigned short FORLIM;
  short FORLIM1;

  printf("Analysing PCX file %s\n", bmname);
  gbufp = 640;
  pxlinlen = 640;
  b = getpcx();
  if (b != 10 && b != 205) {
    printf("What a bad joke!\n");
    printf("This is NOT a PCX file!\n");
    _Escape(0);
  }
  if (b == 205)
    printf("First byte 205, file seems to be captured!\n");
  /*37:*/
  pcxver = getpcx();
  pcxcomp = getpcx();
  bps = getpcx();
  hi = getpcx();
  b = getpcx();
  hi += b * 256;
  vi = getpcx();
  b = getpcx();
  vi += b * 256;
  hh = getpcx();
  b = getpcx();
  hh += b * 256;
  vh = getpcx();
  b = getpcx();
  vh += b * 256;
  hr = getpcx();
  b = getpcx();
  hr += b * 256;
  vr = getpcx();
  b = getpcx();
  vr += b * 256;
  if (hr == 640 && vr == 350) {
    xratio = 3;
    yratio = 4;
  }
  if (hr == 320 && vr == 200) {
    xratio = 5;
    yratio = 6;
  }
  hh -= hi;
  vh -= vi;
  mapwidth = hh;
  for (i = 0; i <= 15; i++) {
    for (j = 0; j <= 2; j++)
      gpal[i][j] = getpcx();
  }
  b = getpcx();
  col = getpcx();
  bzf = getpcx();
  b = getpcx();
  bzf += b * 256;
  hh = bzf;
  b = getpcx();
  b = getpcx();
  for (i = 70; i <= 127; i++)
    b = getpcx();
  bitspsam = bps;
  if (col == 4) {
    bitspsam = 4;
    greypxl = true;
  } else if (bps > 1) {
    bitspsam = bps;
    greypxl = true;
  }
  mapinlen = ((unsigned long)(mapwidth * bitspsam + 7)) >> 3;   /*:37*/
  /*38:*/
  for (i = 0; i <= 15; i++) {
    if (cmyk) {
      sepcols(gpal[i][0], gpal[i][1], gpal[i][2]);
      if (cyan)
	hell[i] = 255 - colcyan;
      if (magenta)
	hell[i] = 255 - colmagenta;
      if (yellow)
	hell[i] = 255 - colyellow;
      if (black)
	hell[i] = 255 - colblack;
      hell[i] /= 16;
      if (hell[i] > 15)
	hell[i] = 15;
      bhell[hell[i]] = 0;
    } else
      hell[i] = (long)(gpal[i][0] / 16.0 * 0.287 + gpal[i][1] / 16.0 * 0.589 +
		       gpal[i][2] / 16.0 * 0.114);
  }
  for (i = 0; i <= 15; i++) {
    if (hell[i] > 15)
      hell[i] = 15;
  }
  for (i = 0; i <= 15; i++) {
    if (bhell[i] > 15)
      bhell[i] = 15;
  }
  opentempfile();   /*:38*/
  if (pcxver == 5 && bitspsam > 4) {   /*39:*/
    gbufp = 640;
    pxlinlen = 640;
    posbit = P_maxpos(bitmap);
    posbit -= 769;
    fseek(bitmap, posbit, 0);
    b = getpcx();
    if (b != 12) {
      printf("No valid information in 256 colors palette\n");
      printf("Using standard 16 colors palette\n");
    } else {
      for (i = 0; i <= 255; i++) {
	for (j = 0; j <= 2; j++)
	  gpal[i][j] = getpcx();
	if (cmyk) {
	  sepcols(gpal[i][0], gpal[i][1], gpal[i][2]);
	  if (cyan)
	    hell[i] = 255 - colcyan;
	  if (magenta)
	    hell[i] = 255 - colmagenta;
	  if (yellow)
	    hell[i] = 255 - colyellow;
	  if (black)
	    hell[i] = 255 - colblack;
	  bhell[hell[i]] = 255 - colblack;
	} else
	  hell[i] = (long)floor(gpal[i][0] * 0.287 + gpal[i][1] * 0.589 + gpal[i]
				  [2] * 0.114 + 0.5);
      }
    }
    fseek(bitmap, 128L, 0);
    gbufp = 640;
    pxlinlen = 640;
  }
  /*:39*/
  /*40:*/
  a = 0;
  for (i = 0; i <= vh; i++) {   /*:40*/
    FORLIM1 = mapinlen;
    for (gbufpp = 0; gbufpp < FORLIM1; gbufpp++)
      b3[gbufpp] = 0;
    for (j = 0; j < col; j++) {
      gbufpp = 0;
      for (k = 1; k <= hh; k++) {
	if (a == 0) {
	  b = getpcx();
	  if ((b & 0xc0) == 0xc0) {
	    a = (b & 0x3f) - 1;
	    b = getpcx();
	  }
	} else
	  a--;
	if (col == 4) {
	  for (ibits = 0; ibits <= 7; ibits++) {
	    ki = gbufpp * 4 + (ibits >> 1);
	    xb = b << ibits;
	    xb >>= 7;
	    xb <<= j;
	    xb <<= (1 - (ibits & 1)) << 2;
	    b3[ki] ^= xb;
	  }
	} else {
	  b3[gbufpp] = b;
	  if (gbufpp == mapinlen - 1 && bitspsam == 1) {
	    ki = 8 - (mapwidth & 7);
	    if (ki != 8) {
	      xb = b3[gbufpp] >> ki;
	      xb <<= ki;
	      b3[gbufpp] = xb;
	      xb = invbit;
	      for (ibits = 1; ibits <= ki; ibits++) {
		b3[gbufpp] ^= xb;
		xb <<= 1;
	      }
	    }
	  }
	}
	gbufpp++;
      }
    }
    if (col == 4) {
      gbufpp = 0;
      hi = (hh - 1) * 4 + 3;
      for (k = 0; k <= hi; k++) {
	b3[gbufpp] = (hell[b3[k] >> 4] << 4) + hell[b3[k] & 15];
	gbufpp++;
      }
    } else if (bps == 8 && pcxver == 5) {
      hi = hh - 1;
      for (k = 0; k <= hi; k++)
	b3[k] = hell[b3[k]];
      gbufpp = hh;
    }
/* p2c: bm2font.pas, line 489:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    _SETIO(fwrite(b3, mapinlen, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
    if (hr == 640 && vr == 200) {
      _SETIO(fwrite(b3, mapinlen, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
    }
/* p2c: bm2font.pas, line 492:
 * Note: Can't interpret size in BLOCKWRITE [174] */
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  pcxtemp = true;
  if (egastretch) {
    if (xratio + 1 == yratio)
      picstretch();
  }
  posbit = 0;
  mapdiv = 1.0;
  FORLIM = bitspsam;
  for (i = 1; i <= FORLIM; i++)
    mapdiv *= 2;
  mapdiv /= 16;
}


/* Local variables for iffint: */
struct LOC_iffint {
  unsigned short hi, hh, vi, vh, compr;
  uchar a, b, col, bps;
  uchar gpal[256][3];
  unsigned short hell[256];
  Char bmstr[256];
  long bmsize, bmoff, bl;
} ;

/*:41*/
/*42:*/
Local long ifflong(LINK)
struct LOC_iffint *LINK;
{
  ebts k;

  fread(b1, 4, 1, bitmap);
  LINK->bl = b1[0];
  for (k = 1; k <= 3; k++)
    LINK->bl = LINK->bl * 256 + b1[k];
  return LINK->bl;
}

/*:42*/
/*43:*/
Local unsigned short iffword(LINK)
struct LOC_iffint *LINK;
{
  fread(b1, 2, 1, bitmap);
  return (b1[0] * 256 + b1[1]);
}

/*:43*/
/*44:*/
Local Void junkchunk(LINK)
struct LOC_iffint *LINK;
{
  if (LINK->bmsize > P_maxpos(bitmap)) {
    printf("File endend while reading junk\n");
    _Escape(0);
  }
  while (LINK->bmsize > 0) {
    fread(&LINK->b, 1, 1, bitmap);
    LINK->bmsize--;
  }
/* p2c: bm2font.pas, line 509:
 * Note: Can't interpret size in BLOCKREAD [174] */
}  /*:44*/

/*45:*/
Local Void checkchunk(LINK)
struct LOC_iffint *LINK;
{
  short i, j, FORLIM;

  if (!strcmp(LINK->bmstr, "BMHD")) {
    LINK->bmsize = ifflong(LINK);
    if (LINK->bmsize & 1)
      LINK->bmsize++;
    LINK->hh = iffword(LINK);
    LINK->vh = iffword(LINK);
    LINK->hi = iffword(LINK);
    LINK->vi = iffword(LINK);
/* p2c: bm2font.pas, line 513:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&LINK->bps, 1, 1, bitmap);
/* p2c: bm2font.pas, line 513:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&LINK->b, 1, 1, bitmap);
/* p2c: bm2font.pas, line 514:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&LINK->b, 1, 1, bitmap);
    LINK->compr = LINK->b;
    for (i = 1; i <= 4; i++)
      fread(&xratio, 1, 1, bitmap);
/* p2c: bm2font.pas, line 515:
 * Note: Can't interpret size in BLOCKREAD [174] */
/* p2c: bm2font.pas, line 515:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&yratio, 1, 1, bitmap);
    LINK->bmsize -= 16;
    junkchunk(LINK);
    if (LINK->bps == 1) {
      LINK->col = 1;
      return;
    }
    if (LINK->bps == 4)
      LINK->col = 15;
    else
      LINK->col = 255;
    return;
  }
  if (!strcmp(LINK->bmstr, "CMAP")) {
    LINK->bmsize = ifflong(LINK);
    LINK->col = LINK->bmsize / 3 - 1;
    FORLIM = LINK->col;
    for (i = 0; i <= FORLIM; i++) {
      for (j = 0; j <= 2; j++) {
	fread(&LINK->b, 1, 1, bitmap);
	LINK->gpal[i][j] = LINK->b;
      }
/* p2c: bm2font.pas, line 519:
 * Note: Can't interpret size in BLOCKREAD [174] */
      if (cmyk) {
	colcyan = 255 - LINK->gpal[i][0];
	colmagenta = 255 - LINK->gpal[i][1];
	colyellow = 255 - LINK->gpal[i][2];
	if (colcyan != colmagenta || colcyan != colyellow ||
	    colmagenta != colyellow) {
	  colcyan -= colmagenta / 3;
	  if (colcyan < 0)
	    colcyan = 0;
	  colmagenta -= colyellow / 3;
	  if (colmagenta < 0)
	    colmagenta = 0;
	}
	colblack = colcyan;
	if (colblack > colmagenta)
	  colblack = colmagenta;
	if (colblack > colyellow)
	  colblack = colyellow;
	if (cyan)
	  LINK->hell[i] = 255 - colcyan;
	if (magenta)
	  LINK->hell[i] = 255 - colmagenta;
	if (yellow)
	  LINK->hell[i] = 255 - colyellow;
	if (black)
	  LINK->hell[i] = 255 - colblack;
      } else
	LINK->hell[i] = (long)floor(LINK->gpal[i][0] * 0.287 + LINK->gpal[i]
			      [1] * 0.589 + LINK->gpal[i][2] * 0.114 + 0.5);
      LINK->hell[i] = (long)(LINK->hell[i] / (256.0 / (LINK->col + 1)));
      bhell[LINK->hell[i]] = (long)(255 - colblack / (256.0 / (LINK->col + 1)));
    }
    if (LINK->bmsize & 1)
      fread(&LINK->b, 1, 1, bitmap);
/* p2c: bm2font.pas, line 534:
 * Note: Can't interpret size in BLOCKREAD [174] */
    return;
  }
  if (!strcmp(LINK->bmstr, "CRNG")) {
    LINK->bmsize = ifflong(LINK);
    LINK->bmoff = iffword(LINK);
    LINK->bmoff = iffword(LINK);
    LINK->bmoff = iffword(LINK);
/* p2c: bm2font.pas, line 536:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&LINK->b, 1, 1, bitmap);
/* p2c: bm2font.pas, line 537:
 * Note: Can't interpret size in BLOCKREAD [174] */
    fread(&LINK->a, 1, 1, bitmap);
    if (LINK->bmsize & 1)
      fread(&LINK->b, 1, 1, bitmap);
/* p2c: bm2font.pas, line 537:
 * Note: Can't interpret size in BLOCKREAD [174] */
    return;
  }
  LINK->bmsize = ifflong(LINK);
  if (LINK->bmsize & 1)
    LINK->bmsize++;
  junkchunk(LINK);
}


/*:36*/
/*41:*/
Static Void iffint()
{   /*:45*/
  struct LOC_iffint V;
  unsigned short ohh;
  uchar cb;
  short FORLIM, FORLIM1;

  /*46:*/
  printf("Analysing IFF file %s\n", bmname);
  opentempfile();
  fread(V.bmstr, 4, 1, bitmap);
  V.bmstr[4] = '\0';
  if (strcmp(V.bmstr, "FORM")) {
    printf("Graphic file not stored as Interchange File Format\n");
    _Escape(0);
  }
  V.bmsize = ifflong(&V) + 8;
  if (V.bmsize != P_maxpos(bitmap)) {
    printf("File is incomplete, should contain %ld\n", V.bmsize);
    _Escape(0);
  }
  fread(V.bmstr, 4, 1, bitmap);
  V.bmstr[4] = '\0';
  if (strcmp(V.bmstr, "ILBM"))
    printf("Type of file is %s, should be ILBM\n", V.bmstr);
  fread(V.bmstr, 4, 1, bitmap);
  V.bmstr[4] = '\0';
  while (strcmp(V.bmstr, "BODY")) {
    if (P_eof(bitmap)) {
      printf("No graphics information available\n");
      _Escape(0);
    }
    checkchunk(&V);
    fread(V.bmstr, 4, 1, bitmap);
    V.bmstr[4] = '\0';
  }
  V.bmsize = ifflong(&V);
  V.hh = (V.hh * V.bps + 7) / 8;
  ohh = V.hh;
  if (ohh & 1)
    ohh++;
  FORLIM = V.vh;
  for (i = 1; i <= FORLIM; i++) {
    if (P_eof(bitmap)) {
      printf("ende\n");
      _Escape(0);
    }
    if (V.compr == 0)
      fread(b3, ohh, 1, bitmap);
    else {   /*47:*/
      gbufp = 0;
      while (gbufp < ohh) {
	fread(&V.b, 1, 1, bitmap);
	V.bmoff++;
	if (V.b < 128) {
	  V.b++;
/* p2c: bm2font.pas, line 555:
 * Note: Can't interpret size in BLOCKREAD [174] */
	  fread(&b3[gbufp], V.b, 1, bitmap);
	  gbufp += V.b;
	  continue;
	}
	if (V.b <= 128)
	  continue;
/* p2c: bm2font.pas, line 556:
 * Note: Can't interpret size in BLOCKREAD [174] */
	fread(&V.a, 1, 1, bitmap);
	V.b = 257 - V.b;
	while (V.b > 0) {
	  b3[gbufp] = V.a;
	  gbufp++;
	  V.b--;
	}
      }
/* p2c: bm2font.pas, line 554:
 * Note: Can't interpret size in BLOCKREAD [174] */
    }  /*:47*/
/* p2c: bm2font.pas, line 553:
 * Note: Can't interpret size in BLOCKREAD [174] */
    if (V.bps == 4) {   /*48:*/
      gi = 0;
      FORLIM1 = V.hh;
      for (gbufpp = 0; gbufpp < FORLIM1; gbufpp++)
	b2[gbufpp] = 0;
      V.a = 0;
      FORLIM1 = V.hh;
      for (gbufpp = 0; gbufpp < FORLIM1; gbufpp++) {
	V.b = b3[gbufpp];
	for (j = 0; j <= 3; j++) {
	  cb = V.b & 128;
	  cb >>= 3 - V.a;
	  b2[gi] ^= cb;
	  V.b <<= 1;
	  cb = V.b & 128;
	  cb >>= 7 - V.a;
	  b2[gi] ^= cb;
	  V.b <<= 1;
	  gi++;
	}
	if (gi >= V.hh) {
	  gi = 0;
	  V.a++;
	}
      }
      FORLIM1 = V.hh;
      for (gbufpp = 0; gbufpp < FORLIM1; gbufpp++)
	b3[gbufpp] = b2[gbufpp];
      gi = 0;
      FORLIM1 = V.hh;
      for (gbufpp = 0; gbufpp < FORLIM1; gbufpp++) {
	b2[gi] = (V.hell[b3[gbufpp] >> 4] << 4) + V.hell[b3[gbufpp] & 15];
	gi++;
      }  /*:48*/
    } else if (V.bps == 8) {
      FORLIM1 = V.hh;
      for (gbufp = 0; gbufp < FORLIM1; gbufp++)
	b2[gbufp] = V.hell[b3[gbufp]];
    } else {
      FORLIM1 = V.hh;
      for (gbufp = 0; gbufp < FORLIM1; gbufp++)
	b2[gbufp] = b3[gbufp];
    }
/* p2c: bm2font.pas, line 568:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    _SETIO(fwrite(b2, V.hh, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  mapinlen = V.hh;
  bitspsam = V.bps;
  posbit = 0;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  pcxtemp = true;
  if (egastretch) {
    if (xratio + 1 == yratio)
      picstretch();
  }
  posbit = 0;
  if (bitspsam > 1)
    greypxl = true;
  mapdiv = 1.0;
  FORLIM = bitspsam;
  for (i = 1; i <= FORLIM; i++)
    mapdiv *= 2;
  mapdiv /= 16;
}  /*:46*/


/*49:*/
Static Void bmpint()
{
  unsigned short i, k, hi, hh, hhl, vi, vh, compr, lcol;
  uchar j, b, a, col, bps;
  uchar gpal[256][4];
  unsigned short hell[256];
  Char bmstr[256];
  long bmsize, bmoff;
  unsigned short FORLIM;

  printf("Analysing BMP file %s\n", bmname);
  opentempfile();
  fread(bmstr, 2, 1, bitmap);
  bmstr[2] = '\0';
  if (strcmp(bmstr, "BM")) {
    printf("No windows bitmap %s\n", bmstr);
    _Escape(0);
  }
  gbufp = 640;
  pxlinlen = 640;
  bmsize = longpcx();
  for (i = 1; i <= 4; i++)
    b = getpcx();
  bmoff = longpcx();
  bmsize = longpcx();
  bmoff -= bmsize;
  if (bmsize > 12) {
    hi = longpcx();
    vi = longpcx();
    b = getpcx();
    b = getpcx();
    bps = wordpcx();
    if (bps > 8) {
      printf("only up to 256 colors supported\n");
      _Escape(0);
    }
    hh = hi;
    vh = vi;
    compr = longpcx();
    for (i = 1; i <= 4; i++)
      b = getpcx();
    xratio = longpcx();
    yratio = longpcx();
    lcol = longpcx();
    lcol--;
    if (col == 0) {
      if (bps == 1)
	col = 1;
      else if (bps == 4)
	col = 15;
      else
	col = 255;
    }
    col = longpcx();
    col--;
  } else {
    hi = wordpcx();
    vi = wordpcx();
    b = getpcx();
    b = getpcx();
    bps = wordpcx();
    if (bps > 8) {
      printf("only up to 256 colors supported\n");
      _Escape(0);
    }
    hh = hi;
    vh = vi;
    compr = 0;
    xratio = 1;
    yratio = 1;
    col = 0;
  }
  if (lcol == 0) {
    if (bps == 1)
      col = 1;
    else if (bps == 4)
      col = 15;
    else
      col = 255;
  }
  if (bps == 1)
    col = 1;
  else if (bps == 4)
    col = 15;
  else
    col = 255;
  for (i = 0; i <= col; i++) {
    if (bmsize > 12) {
      for (j = 0; j <= 3; j++)
	gpal[i][j] = getpcx();
    } else {
      for (j = 0; j <= 2; j++)
	gpal[i][j] = getpcx();
    }
    if (cmyk) {
      colcyan = 255 - gpal[i][2];
      colmagenta = 255 - gpal[i][1];
      colyellow = 255 - gpal[i][0];
      if (colcyan != colmagenta || colcyan != colyellow ||
	  colmagenta != colyellow) {
	colcyan -= colmagenta / 3;
	if (colcyan < 0)
	  colcyan = 0;
	colmagenta -= colyellow / 3;
	if (colmagenta < 0)
	  colmagenta = 0;
      }
      colblack = colcyan;
      if (colblack > colmagenta)
	colblack = colmagenta;
      if (colblack > colyellow)
	colblack = colyellow;
      if (cyan)
	hell[i] = 255 - colcyan;
      if (magenta)
	hell[i] = 255 - colmagenta;
      if (yellow)
	hell[i] = 255 - colyellow;
      if (black)
	hell[i] = 255 - colblack;
      hell[i] = (long)(hell[i] / (256.0 / (col + 1)));
      bhell[hell[i]] = (long)((255 - colblack) / (256.0 / (col + 1)));
    } else
      hell[i] = (long)((gpal[i][2] * 0.287 + gpal[i][1] * 0.589 + gpal[i]
			  [0] * 0.114) / (256.0 / (col + 1)));
  }
  if (bmsize > 12)
    bmoff -= (col + 1) * 4;
  else
    bmoff -= (col + 1) * 3;
  if (compr != 0) {
    printf("compression not supported yet\n");
    _Escape(0);
  }
  hh = (hh * bps + 7) / 8;
  hhl = (hh + 3) / 4 * 4 - 1;
  a = 8 - ((hi * bps) & 7);
/* p2c: bm2font.pas, line 616:
 * Note: Suspicious mixture of sizes in FILLCHAR [173] */
  memset((Anyptr)b3, 0, hhl + 1L);
  for (i = 1; i <= vh; i++) {  /*$I-*/
    _SETIO(fwrite(b3, hh, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
  }
/* p2c: bm2font.pas, line 617:
 * Note: Can't interpret size in BLOCKWRITE [174] */
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  if (tmpfil != NULL)
    tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
  else
    tmpfil = fopen(tmpfil_NAME, "w+b");
  if (tmpfil == NULL)
    _EscIO(FileNotFound);
  bmoff = (vh - 1) * (long)hh;
  for (i = 0; i < vh; i++) {
    for (k = 0; k <= hhl; k++)
      b3[k] = getpcx();
    if (bps == 4) {
      gi = 0;
      for (k = 0; k < hh; k++) {
	b2[gi] = (hell[b3[k] >> 4] << 4) + hell[b3[k] & 15];
	gi++;
      }
    } else if (bps == 8) {
      for (k = 0; k < hh; k++)
	b2[k] = hell[b3[k]];
    } else {
      for (k = 0; k < hh; k++)
	b2[k] = b3[k];
    }
    if (a < 8) {
      for (k = 0; k < a; k++)
	b2[hh - 1] ^= invbit >> k;
    }
    fseek(tmpfil, bmoff, 0);
    bmoff = bmoff - (long)hh;
/* p2c: bm2font.pas, line 629:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    _SETIO(fwrite(b2, hh, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  mapinlen = hh;
  posbit = 0;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  pcxtemp = true;
  bitspsam = bps;
  if (bitspsam > 1)
    greypxl = true;
  mapdiv = 1.0;
  FORLIM = bitspsam;
  for (i = 1; i <= FORLIM; i++)
    mapdiv *= 2;
  mapdiv /= 16;
}


/*50:*/
Static Void imgint()
{
  unsigned short i, ki, hi, hh, bzf, imgpat;
  short vh;
  uchar mi, cb, j, b, a, col, bps;
  unsigned short hell[16];
  uchar linerep;
  unsigned short FORLIM;

  printf("Analysing IMG file %s\n", bmname);
  invert = !invert;
  if (invert) {   /*51:*/
    invbit = 0;
    invbyte = 0;
  } else {
    invbit = 1;
    invbyte = 255;
  }
  hell[0] = 0;
  hell[1] = 1;
  hell[2] = 6;
  hell[3] = 8;
  hell[4] = 3;
  hell[5] = 2;
  hell[6] = 7;
  hell[7] = 11;
  hell[8] = 4;
  hell[9] = 5;
  hell[10] = 12;
  hell[11] = 13;
  hell[12] = 10;
  hell[13] = 9;
  hell[14] = 14;
  hell[15] = 15;
  opentempfile();   /*:51*/
  gbufp = 640;
  pxlinlen = 640;
  a = getpcx();
  b = getpcx();
  if (a * 256 + b != 1) {   /*52:*/
    printf("File does not contain GEM Image File Format\n");
    _Escape(0);
  }
  b = getpcx();
  bzf = b * 256;
  b = getpcx();
  bzf += b;
  b = getpcx();
  bps = b * 256;
  b = getpcx();
  bps += b;
  b = getpcx();
  imgpat = b * 256;
  b = getpcx();
  imgpat += b;
  b = getpcx();
  xratio = b * 256;
  b = getpcx();
  xratio += b;
  b = getpcx();
  yratio = b * 256;
  b = getpcx();
  yratio += b;
  if (xratio != yratio) {
    mapdiv = (double)yratio / xratio;
    xratio = 0;
    yratio = 0;
    while (xratio == yratio) {
      xratio++;
      yratio = (long)floor(xratio * mapdiv + 0.5);
    }
  }
  b = getpcx();
  hi = b * 256;
  b = getpcx();
  hi += b;
  b = getpcx();
  vh = b * 256;
  b = getpcx();
  vh += b;   /*:52*/
  hh = (hi * bps + 7) / 8;
  if (bzf > 8) {
    for (i = 1; i <= (bzf - 8) * 2; i++)
      b = getpcx();
  }
  linerep = 0;
  gi = 0;
  while (vh > 0) {
    for (gi = 0; gi <= hh; gi++)
      b3[gi] = 0;
    gi = 0;
    while (gi < hh) {
      b = getpcx();
      if (b != 0 && b != 128) {
	a = b & 127;
	cb = ((unsigned)(b - a)) >> 7;
	if (cb == 1)
	  cb = 255;
	for (ki = 1; ki <= a; ki++) {
	  b3[gi] = cb;
	  gi++;
	}
	continue;
      }
      if (b == 128) {
	a = getpcx();
	for (ki = 1; ki <= a; ki++) {
	  b3[gi] = getpcx();
	  gi++;
	}
	continue;
      }
      a = getpcx();
      if (a <= 0) {
	b = getpcx();
	linerep = getpcx();
	continue;
      }
      for (ki = 1; ki <= imgpat; ki++)
	b2[ki] = getpcx();
      for (ki = 1; ki <= a; ki++) {
	for (mi = 1; mi <= imgpat; mi++) {
	  b = b2[mi];
	  b3[gi] = b;
	  gi++;
	}
      }
    }
    if (bps == 4) {   /*48:*/
      gi = 0;
      for (gbufpp = 0; gbufpp < hh; gbufpp++)
	b2[gbufpp] = 0;
      a = 0;
      for (gbufpp = 0; gbufpp < hh; gbufpp++) {
	b = b3[gbufpp];
	for (j = 0; j <= 3; j++) {
	  cb = b & 128;
	  cb >>= 3 - a;
	  b2[gi] ^= cb;
	  b <<= 1;
	  cb = b & 128;
	  cb >>= 7 - a;
	  b2[gi] ^= cb;
	  b <<= 1;
	  gi++;
	}
	if (gi >= hh) {
	  gi = 0;
	  a++;
	}
      }
      for (gbufpp = 0; gbufpp < hh; gbufpp++)
	b3[gbufpp] = b2[gbufpp];
      gi = 0;
      for (gbufpp = 0; gbufpp < hh; gbufpp++) {
	b2[gi] = (hell[b3[gbufpp] >> 4] << 4) + hell[b3[gbufpp] & 15];
	gi++;
      }  /*:48*/
    } else {
      for (ki = 0; ki < hh; ki++)
	b2[ki] = b3[ki];
    }
/* p2c: bm2font.pas, line 674:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    _SETIO(fwrite(b2, hh, 1, tmpfil) == 1, FileWriteError);
    filestat = P_ioresult;
    if (filestat != 0) {
      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	     FileWriteError);
      fileproblem();
      _Escape(0);
    }
    vh--;
    if (linerep <= 0)
      continue;
    for (i = 1; i <= linerep; i++) {  /*$I-*/
      _SETIO(fwrite(b2, hh, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
    }
/* p2c: bm2font.pas, line 678:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    vh += 1 - linerep;
    linerep = 0;
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (tmpfil != NULL)
    fclose(tmpfil);
  tmpfil = NULL;
  if (col == 4) {
    bitspsam = 4;
    greypxl = true;
  } else if (bps > 1) {
    bitspsam = bps;
    greypxl = true;
  }
  mapinlen = hh;
  posbit = 0;
  strcpy(bitmap_NAME, "pcxtemp.tmp");
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  if (egastretch) {
    if (xratio + 1 == yratio)
      picstretch();
  }
  posbit = 0;
  pcxtemp = true;
  mapdiv = 1.0;
  FORLIM = bitspsam;
  for (i = 1; i <= FORLIM; i++)
    mapdiv *= 2;
  mapdiv /= 16;
}


/*54:*/
Static Void tfmhword(hword)
long hword;
{
  union {
    uchar b[4];
    long i;
  } ax;
  short i;

  ax.i = hword;
#ifdef INTEL
  for (i = 1; i >= 0; i--)
    fwrite(&ax.b[i], sizeof(uchar), 1, tfmfile);
#else
  for (i = 2; i <= 3; i++)
    fwrite(&ax.b[i], sizeof(uchar), 1, tfmfile);
#endif
}


Static Void tfmword(lword)
long lword;
{
  union {
    uchar b[4];
    long i;
  } ax;
  short i;

  ax.i = lword;
#ifdef INTEL
  for (i = 3; i >= 0; i--)
    fwrite(&ax.b[i], sizeof(uchar), 1, tfmfile);
#else
  for (i = 0; i <= 3; i++)
    fwrite(&ax.b[i], sizeof(uchar), 1, tfmfile);
#endif
}


/*:54*/
/*57:*/
Static Void pxlmap(lword)
long lword;
{
  union {
    ebts b[4];
    long i;
  } ax;
  uchar i;

  ax.i = lword;
  for (i = 0; i <= 3; i++) {
    pxlbm[pxlbmi] = ax.b[i];
    pxlbmi++;
  }
}  /*:57*/


/*61:*/
Static Void pkbyte(b)
uchar b;
{
  pkbm[pkloc] = b;
  pkloc++;
}


Static Void pkhalfword(a)
short a;
{
  union {
    ebts b[2];
    short w;
  } ax;

  ax.w = a;
#ifdef INTEL
  pkbyte(ax.b[1]);
  pkbyte(ax.b[0]);
#else
  pkbyte(ax.b[0]);
  pkbyte(ax.b[1]);
#endif
}


Static Void pkthreebytes(a)
long a;
{
  union {
    ebts b[4];
    long i;
  } ax;

  ax.i = a;
#ifdef INTEL
  pkbyte(ax.b[2]);
  pkbyte(ax.b[1]);
  pkbyte(ax.b[0]);
#else
  pkbyte(ax.b[1]);
  pkbyte(ax.b[2]);
  pkbyte(ax.b[3]);
#endif
}


Static Void pkword(a)
long a;
{
  union {
    ebts b[4];
    long i;
  } ax;

  ax.i = a;
#ifdef INTEL
  pkbyte(ax.b[3]);
  pkbyte(ax.b[2]);
  pkbyte(ax.b[1]);
  pkbyte(ax.b[0]);
#else
  pkbyte(ax.b[0]);
  pkbyte(ax.b[1]);
  pkbyte(ax.b[2]);
  pkbyte(ax.b[3]);
#endif
}


Static Void pknyb(a)
uchar a;
{
  if (bitweight == 16) {
    outputbyte = a << 4;
    bitweight = 1;
  } else {
    pkbyte(outputbyte + a);
    bitweight = 16;
  }
}


/*:61*/
/*63:*/
Static Void writepreambl()
{
  short i;
  Char nstr[256];

  sprintf(nstr, "%ld", (long)floor(truehres + 0.5));
#ifdef MSDOS
  sprintf(cmd, "%s%c.pk", font, fontpre[nf]);
#else
  sprintf(cmd, "%s%c.%spk", font, fontpre[nf], nstr);
#endif
  strcpy(pxlfile_NAME, cmd);
  if (pxlfile != NULL)
    pxlfile = freopen(pxlfile_NAME, "w+b", pxlfile);
  else
    pxlfile = fopen(pxlfile_NAME, "w+b");
  _SETIO(pxlfile != NULL, FileNotFound);
  filestat = P_ioresult;
  if (filestat == 3 || filestat == 5) {
    strcpy(cmd, bmname);
    sprintf(cmd + strlen(cmd), "%c.pk", fontupc[nf]);
    strcpy(pxlfile_NAME, cmd);
    if (pxlfile != NULL)
      pxlfile = freopen(pxlfile_NAME, "w+b", pxlfile);
    else
      pxlfile = fopen(pxlfile_NAME, "w+b");
    _SETIO(pxlfile != NULL, FileNotFound);
    filestat = P_ioresult;
  }
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {
    printf("error occurred when ");
    printf("allocating pkfile ");
    puts(cmd);
    fileproblem();
    _Escape(0);
  }
  pkloc = 0;
  pkbyte(247);
  pkbyte(89);
  pkbyte(14);
  strcpy(comment, "BM2FONT output");
  for (i = 0; i <= 13; i++)
    pkbyte(comment[i]);
  pkword(tabdsize[nf]);
  pkword(checksum);
  pkword(floor(truehres * 65536L / 72.27 + 0.5));
  pkword(floor(truevres * 65536L / 72.27 + 0.5));
  nextmemfree = 0;
  printf("Packing font %s\n", cmd);
}


/*:63*/
/*65:*/
Static Void writepostamb()
{
  pkbyte(245);
  while ((pkloc & 3) != 0)
    pkbyte(246);
/* p2c: bm2font.pas, line 781:
 * Note: Can't interpret size in BLOCKWRITE [174] */
  _SETIO(fwrite(pkbm, pkloc, 1, pxlfile) == 1, FileWriteError);
  filestat = P_ioresult;
  if (filestat != 0) {
    _SETIO(printf("Error occured when writing font %s!\n", cmd) >= 0,
	   FileWriteError);
    fileproblem();
    _Escape(0);
  }
  if (pxlfile != NULL)
    fclose(pxlfile);
  pxlfile = NULL;
  printf(" \n");
  printf("Font %s at %ld dots per inch written\n",
	 cmd, (long)floor(truehres + 0.5));
  nf++;
  if (nf > 25) {
    printf("More then 26 fonts! Giving up\n");
    _Escape(0);
  }
  charpf[nf] = ng;
  ng = 0;
  pkloc = 0;
}


/*:65*/
/*67:*/
Static boolean equal(row1, row2)
pxlstr row1, row2;
{
  short i;
  boolean temp;

  i = pkwidth;
  temp = true;
  while (i > 0 && temp) {
    if (pxlbm[row1] != pxlbm[row2])
      temp = false;
    row1++;
    row2++;
    i -= 8;
  }
  return temp;
}


/*:67*/
/*68:*/
Static boolean equalzo(row1, row2)
pxlstr row1;
short row2;
{
  short i;
  boolean temp;

  i = pkwidth;
  temp = true;
  while (i > 0 && temp) {
    if (pxlbm[row1] != (repbm[row2] & 255))
      temp = false;
    row1++;
    row2++;
    i -= 8;
  }
  return temp;
}


/*:68*/
/*70:*/
Static Void shipcharacte()
{   /*:87*/
  pxlstr crst;
  short wwid;
  long compsize;
  long horesc;
  /*72:*/
  short l;
  long i, j, k;
  short rowzero, onesrow, repptr, bitcounts;
  ebts fillbytes, longind, mixbyte, restbyte, pkshift, dshift;
  long longtab[20];
  /*:72*/
  /*77:*/
  long count;
  short test, curptr, bit, repflag;
  schar pkkword; 
  short bitptr, bitmod32, currepeat;
  pxlstr endraster;   /*:77*/
  /*80:*/
  short dynf;
  long deriv[13];
  long bcompsize;
  boolean firston;
  short flagbyte;
  /*:80*/
  /*87:*/
  unsigned short max2;
  pxlstr predpkloc;
  short bytelength;

  horesc = pwidth[f][car];
  pkwidth = pwidth[f][car];
  pkheight = pheight[f][car];
  pkheight -= yoffset[f][car];
  cxoff = 0;
  cyoff = pkheight;
  crst = pkpoint[car];
  wwid = (pkwidth + 31) / 32 * 4;
  fillbytes = wwid - (pkwidth + 7) / 8;   /*71:*/
  rowzero = nextmemfree;
  onesrow = nextmemfree + wwid;
  repptr = onesrow + wwid;
  bitcounts = repptr + pkheight + 1;
  for (i = rowzero; i < onesrow; i++)
    repbm[i] = 0;
  for (i = onesrow; i <= repptr - 2; i++)
    repbm[i] = -1;
  j = onesrow + (((unsigned long)(pkwidth + 7)) >> 3);
  repbm[j - 1] = power[8] - power[7 - ((pkwidth + 7) & 7)];
  for (i = j; i < repptr; i++)
    repbm[i] = 0;
  i = 0;
  j = pkheight;
  while (i < j) {
    if (equalzo((i * wwid + crst), rowzero))
      repbm[repptr + i] = 0;
    else if (equalzo((i * wwid + crst), onesrow))
      repbm[repptr + i] = 0;
    else if (i + 1 == j)
      repbm[repptr + i] = 0;
    else if (equal((i * wwid + crst), (int)((i + 1) * wwid + crst)))
      repbm[repptr + i] = 1;
    else
      repbm[repptr + i] = 0;
    i++;
  }
  i = 0;
  while (i < j) {
    k = i;
    while (repbm[repptr + k] == 1)
      k++;
    repbm[repptr + i] = k - i;
    i = k + 1;
  }
  repbm[repptr + i] = 0;   /*:71*/
  /*75:*/
  repflag = 0;
  bitptr = pkwidth - 1;
  currepeat = repptr;
  endraster = crst + pkheight * wwid;
  curptr = bitcounts;
  count = 0;
  longind = 0;
  test = 0;
  do {   /*76:*/
    bitptr++;
    if (bitptr == pkwidth) {
      bitmod32 = 0;
      bitptr = 0;
      if (currepeat > repptr)
	crst += fillbytes;
      if (repbm[currepeat] > 0) {
	repflag = repbm[currepeat];
	currepeat += repflag;
	crst += wwid * repflag;
      }
      currepeat++;
    }
    bitmod32--;
    if (bitmod32 == -1) {
      bitmod32 = 7;
      pkkword = pxlbm[crst];
      crst++;
    }
    if (crst > endraster)
      bit = 2;
    else if (pkkword < 0)
      bit = 1;
    else
      bit = 0;
    pkkword <<= 1;   /*:76*/
    if (bit == test)
      count++;
    else {
      if (count > 32767) {
	longind++;
	longtab[longind - 1] = count;
	count = -longind - 10000;
      }
      repbm[curptr] = count;
      curptr++;
      if (curptr + 1 > maxmemsize)
	test = 3;
      else {
	count = 1;
	test = bit;
	if (repflag > 0) {
	  repbm[curptr] = -repflag;
	  repflag = 0;
	  curptr++;
	}
      }
    }
  } while (test < 2);
  repbm[curptr] = 0;
  repbm[curptr + 1] = 0;   /*:75*/
  /*78:*/
  if (test < 3) {
    for (i = 0; i <= 12; i++)
      deriv[i] = 0;
    firston = (repbm[bitcounts] == 0);
    if (firston)
      bitcounts++;
    i = bitcounts;
    compsize = 0;
    while (repbm[i] != 0) {   /*79:*/
      j = repbm[i];
      if (j < -10000)
	j = longtab[-j - 10001];
      if (j == -1)
	compsize++;
      else {
	if (j < 0) {
	  compsize++;
	  j = -j;
	}
	if (j < 209)
	  compsize += 2;
	else {
	  k = j - 193;
	  while (k >= 16) {
	    k = ((unsigned long)k) >> 4;
	    compsize += 2;
	  }
	  compsize++;
	}
	if (j < 14)
	  deriv[j - 1]--;
	else if (j < 209)
	  deriv[(223 - j) / 15 - 1]++;
	else {
	  k = 16;
	  while (k <= ((unsigned long)(j + 2)) >> 4) {
	    k <<= 4;
	    if (k == 0) {
	      k = 32767;
	      j += 32767;
	    }
	  }
	  if (j - k <= 192)
	    deriv[(k - j + 207) / 15 - 1] += 2;
	}
      }
      i++;
    }
    /*:79*/
    bcompsize = compsize;
    dynf = 0;
    for (i = 1; i <= 13; i++) {
      compsize += deriv[i - 1];
      if (compsize <= bcompsize) {
	bcompsize = compsize;
	dynf = i;
      }
    }
    compsize = (bcompsize + 1) / 2;
    if (compsize > (pkheight * pkwidth + 7) / 8 || pkheight * pkwidth == 0) {
      compsize = (pkheight * pkwidth + 7) / 8;
      dynf = 14;
    }
  } else {
    dynf = 14;
    firston = (repbm[bitcounts] == 0);
    compsize = (pkheight * pkwidth + 7) / 8;
  }
  if (pkloc + compsize > 65487L || ng > 127) {   /*81:*/
    writepostamb();
    if (nf > 26) {
      printf("Sorry, more than 26 fonts necessary, reduce bitmap\n");
      _Escape(0);
    }
    writepreambl();
  }
  flagbyte = dynf * 16;
  if (firston)
    flagbyte += 8;
  if (width[f][car] > 16777215L || width[f][car] < 0 || horesc < 0 ||
      compsize > 196594L || pkwidth > 65535L || pkheight > 65535L ||
      cxoff > 32767 || cyoff > 32767 || cxoff < -32768L || cyoff < -32768L)
  {   /*82:*/
    flagbyte += 7;
    pkbyte(flagbyte);
    compsize += 28;
    pkword(compsize);
    pkword(ng);
    predpkloc = pkloc + compsize;
    pkword(width[f][car]);
    pkword(horesc);
    pkword(0);
    pkword(pkwidth);
    pkword(pkheight);
    pkword(cxoff);
    pkword(cyoff);
  }  /*:82*/
  else if (horesc > 255 || pkwidth > 255 || pkheight > 255 || cxoff > 127 ||
	   cyoff > 127 || cxoff < -128 || cyoff < -128 || compsize > 1015) {
    compsize += 13;
    flagbyte += compsize / 65536L + 4;
    pkbyte(flagbyte);
/* p2c: bm2font.pas, line 874:
 * Note: Using % for possibly-negative arguments [317] */
    pkhalfword((compsize % 65536L));
    pkbyte(ng);
    predpkloc = pkloc + compsize;
    pkthreebytes(width[f][car]);
    pkhalfword(horesc);
    pkhalfword(pkwidth);
    pkhalfword(pkheight);
    pkhalfword(cxoff);
    pkhalfword(cyoff);
  } else {
    compsize += 8;
    flagbyte += compsize / 256;
    pkbyte(flagbyte);
    pkbyte((compsize & 255));
    pkbyte(ng);
    predpkloc = pkloc + compsize;
    pkthreebytes(width[f][car]);
    pkbyte(horesc & 255);
    pkbyte(pkwidth);
    pkbyte(pkheight);
    pkbyte(cxoff);
    pkbyte(cyoff);
  }
  if (dynf != 14) {   /*85:*/
    bitweight = 16;
    max2 = 208 - dynf * 15;
    i = bitcounts;
    while (repbm[i] != 0) {
      j = repbm[i];
      if (j < -10000)
	j = longtab[-j - 10001];
      if (j == -1)
	pknyb(15);
      else {
	if (j < 0) {
	  pknyb(14);
	  j = -j;
	}
	if (j <= dynf)
	  pknyb(j);
	else if (j <= max2) {
	  j += -dynf - 1;
	  pknyb(((j) >> 4) + dynf + 1);
	  pknyb((j & 15));
	} else {
	  j += 15 - max2;
	  k = 1;
	  while (k <= ((unsigned long)j) >> 4) {
	    k <<= 4;
	    pknyb(0);
	  }
	  while (k > 0) {
	    pknyb((j / k));
	    j %= k;
/* p2c: bm2font.pas, line 889:
 * Note: Using % for possibly-negative arguments [317] */
	    k = ((unsigned long)k) >> 4;
	  }
	}
      }
      i++;
    }
    if (bitweight != 16)
      pkbyte(outputbyte);
  } else  /*86:*/
  {   /*:86*/
    crst = pkpoint[car];
    bytelength = (((unsigned long)(pkwidth + 7)) >> 3) - 1;
    if ((pkwidth & 7) == 0) {
      while (crst < endraster) {
	for (i = 0; i <= bytelength; i++)
	  pkbyte(pxlbm[crst + i]);
	crst += wwid;
      }
    } else {
      pkshift = 0;
      dshift = pkwidth & 7;
      while (crst < endraster) {
	if (pkshift == 0) {
	  for (i = 0; i < bytelength; i++)
	    pkbyte(pxlbm[crst + i]);
	  mixbyte = pxlbm[crst + bytelength];
	} else {
	  i = crst;
	  l = pkwidth + pkshift;
	  while (l >= 8) {
	    l -= 8;
	    restbyte = pxlbm[i];
	    i++;
	    pkbyte(mixbyte + (restbyte >> pkshift));
	    mixbyte = restbyte << (8 - pkshift);
	  }
	  if (pkshift < ((pkshift + dshift) & 7))
	    mixbyte += pxlbm[i] >> pkshift;
	}
	crst += wwid;
	pkshift = (pkshift + dshift) & 7;
      }
      if (pkshift > 0)
	pkbyte(mixbyte);
    }
  }
  /*:85*/
  if (predpkloc != pkloc) {
    printf("Bad predicted character length: character %d\n", car);
    printf("pred: %uloc: %u\n", predpkloc, pkloc);
    _Escape(0);
  }
  pkpoint[car] = 0;   /*:78*/
  putchar('.');
  if (car == 79)
    putchar('\n');
  pwidth[nf][ng] = pwidth[f][car];
  pheight[nf][ng] = pheight[f][car];
  width[nf][ng] = width[f][car];
  height[nf][ng] = height[f][car];
  yoffset[nf][ng] = yoffset[f][car];
  ng++;

  /*84:*/
  /*:84*/
  /*83:*/
  /*:83*/
  /*:81*/
}


/*:70*/
/*88:*/
Static Void fonteject()
{
  short lx, FORLIM, FORLIM1, FORLIM2;

  nf = 0;
  ng = 0;
  writepreambl();
  while (maplines > 0) {
    FORLIM = maxx;
    for (k = 1; k <= FORLIM; k++) {
      i = k - 1;
      dirpoint[g] = pxlbmi / 4;
      pkpoint[g] = pxlbmi;
      linepos_ = posbit + i * hres / 8;
      pxlinlen = (pwidth[f][g] + 7) / 8;
      zeroline = true;
      gi = 0;
      FORLIM1 = pheight[f][g];
      for (v = 1; v <= FORLIM1; v++) {
	fseek(bitmap, linepos_, 0);
/* p2c: bm2font.pas, line 916:
 * Note: Can't interpret size in BLOCKREAD [174] */
	j = fread(b1, 1, pxlinlen, bitmap);
	FORLIM2 = pxlinlen;
	for (lx = 0; lx < FORLIM2; lx++)
	  b2[lx] = b1[lx];
	if (invert) {
	  FORLIM2 = pxlinlen;
	  for (lx = 0; lx < FORLIM2; lx++)
	    b2[lx] = 255 - b1[lx];
	}
	gi += dv;
	if (gi >= lv)
	  gi -= cv;
	if (invbyte == 255) {
	  FORLIM2 = pxlinlen;
	  for (lx = 0; lx < FORLIM2; lx++)
	    b1[lx] = invbyte - b1[lx];
	}
	lx = 0;
	zerorow = true;
	FORLIM2 = pxlinlen;
	for (j = 0; j < FORLIM2; j++) {
	  if (b1[j] != 0) {
	    zerorow = false;
	    zeroline = false;
	  }
	}
	if (zeroline) {
	  yoffset[f][g]++;
	  if (yoffset[f][g] == pheight[f][g]) {
	    yoffset[f][g]--;
	    zerorow = false;
	    zeroline = false;
	  }
	}
	cx.i = 0;
	if (!zeroline) {
	  FORLIM2 = pxlinlen;
	  for (j = 0; j < FORLIM2; j++) {
	    if (lx > 3) {
	      lx = 0;
	      pxlmap(cx.i);
	      cx.i = 0;
	    }
	    cx.b[lx] = b1[j];
	    lx++;
	  }
	  pxlmap(cx.i);
	}
	linepos_ += (mapwidth + 7) / 8 + zeropads;
      }
      i += maxx;
      g++;
      if (g == mincharpf) {   /*89:*/
	for (car = 0; car <= 127; car++) {
	  if (pkpoint[car] != 0)
	    shipcharacte();
	}
	f++;
	g = 0;
	pxlbmi = 4;
      }
      /*:89*/
    }
    maplines -= vres;
    posbit += vres * ((mapwidth + 7) / 8 + zeropads);
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;   /*90:*/
  for (car = 0; car <= 127; car++) {
    if (pkpoint[car] != 0)
      shipcharacte();
  }
  writepostamb();
  noffonts = nf;   /*:90*/
}


/*:88*/
/*103:*/
Static Void userhelp()
{
  short FORLIM, FORLIM1;

  sprintf(cmd, "%s.tex", font);
  strcpy(texfile_NAME, cmd);
  if (texfile != NULL)
    texfile = freopen(texfile_NAME, "w", texfile);
  else
    texfile = fopen(texfile_NAME, "w");
  _SETIO(texfile != NULL, FileNotFound);
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (filestat == 5) {
    *cmd = '\0';
    sprintf(cmd + strlen(cmd), "%s.tex", font);
    strcpy(texfile_NAME, cmd);
    if (texfile != NULL)
      texfile = freopen(texfile_NAME, "w", texfile);
    else
      texfile = fopen(texfile_NAME, "w");
    _SETIO(texfile != NULL, FileNotFound);
    filestat = P_ioresult;
    if (filestat == 0)
      fok = false;
    else
      fok = true;
  }
  if (fok) {   /*104:*/
    printf("%s error occured when allocating TeXfile %s\n", cmd, cmd);
    fileproblem();
    _Escape(0);
  }
  fprintf(texfile, "\\newbox\\%sbox\n", font);
  fprintf(texfile, "\\newdimen\\%swd\n", font);
  FORLIM = noffonts;
  for (a = 1; a <= FORLIM; a++) {
    fprintf(texfile, "\\font\\%s%c=%s%c at ",
	    font, fontpre[a - 1], font, fontpre[a - 1]);
    outfix(tabdsize[a - 1]);
    fprintf(texfile, "truept\n");
  }
  fprintf(texfile, "\\setbox\\%sbox=\\vbox{\\hbox{%%\n", font);
  a = 0;
  k = 1;
  c = 0;
  i = (mapwidth + hres - 1) / hres;
  FORLIM = i;
  for (b = 1; b <= FORLIM; b++) {
    if (a != k) {
      fprintf(texfile, "\\%s%c", font, fontpre[k - 1]);
      a = k;
    }
    fprintf(texfile, "\\char%d", c);
    if ((b & 7) == 0 && b != i)
      fprintf(texfile, "%%\n");
    c++;
    if (c == charpf[k]) {
      k++;
      c = 0;
    }
  }
  fprintf(texfile, "}}\n");
  /*:104*/
  /*105:*/
  fprintf(texfile, "\\%swd=\\wd\\%sbox\n", font, font);
  fprintf(texfile, "\\setbox\\%sbox=\\hbox{\\vbox{\\hsize=\\%swd\n",
	  font, font);
  fprintf(texfile, "\\parskip=0pt\\offinterlineskip\\parindent0pt\n");
  v = 1;
  k = 1;
  c = 0;
  FORLIM = nj;
  for (a = 0; a < FORLIM; a++) {
    fprintf(texfile, "\\hbox{\\%s%c", font, fontpre[k - 1]);
    v = k;
    FORLIM1 = i;
    for (b = 0; b < FORLIM1; b++) {
      if (v != k) {
	fprintf(texfile, "\\%s%c", font, fontpre[k - 1]);
	v = k;
      }
      fprintf(texfile, "\\char%d", c);
      if (((b + 1) & 7) == 0 && b + 1 != i)
	fprintf(texfile, "%%\n");
      c++;
      if (c == charpf[k]) {
	k++;
	c = 0;
      }
    }
    if (a < nj - 1)
      fprintf(texfile, "}\n");
  }
  fprintf(texfile, "}}}\n");
  fprintf(texfile, "\\ifx\\parbox\\undefined\n");
  fprintf(texfile, "    \\def\\set%s{\\box\\%sbox}\n", font, font);
  fprintf(texfile, "\\else\n");
  fprintf(texfile, "    \\def\\set%s{\\parbox{\\wd\\%sbox}", font, font);
  fprintf(texfile, "{\\box\\%sbox}}\n", font);
  fprintf(texfile, "\\fi\n");
  if (texfile != NULL)
    fclose(texfile);
  texfile = NULL;
  printf("File %s written\n", cmd);   /*:105*/
}


/*:103*/
/*106:*/
main(argc, argv)
int argc;
Char *argv[];
{
  short FORLIM;
  Char STR2[256];
  uchar FORLIM1;
  short FORLIM2, FORLIM3;
  uchar FORLIM4;

  PASCAL_MAIN(argc, argv);
  tfmfile = NULL;
  tmpfil = NULL;
  pxlfile = NULL;
  bitmap = NULL;
  texfile = NULL;
  power[0] = 1;
  for (i = 1; i <= 8; i++)
    power[i] = power[i - 1] * 2;
  pxlbm = (uchar *)Malloc(sizeof(pxla));
  pkbm = (uchar *)Malloc(sizeof(pxla));
  repbm = (short *)Malloc(sizeof(pxlba));
  gkorh = (short *)Malloc(sizeof(korbyte));
  gkordivp = (short *)Malloc(sizeof(korbyte));
  spreadvals = (short *)Malloc(sizeof(spreadbyte));
  width = (long(*)[129])Malloc(sizeof(dynlong));
  height = (long(*)[129])Malloc(sizeof(dynlong));
  yoffset = (unsigned short(*)[129])Malloc(sizeof(dynword));
  pwidth = (unsigned short(*)[129])Malloc(sizeof(dynword));
  pheight = (unsigned short(*)[129])Malloc(sizeof(dynword));
  greymem = (uchar *)Malloc(sizeof(pxla));   /*107:*/
  strcpy(cref, "!()+,-./0123456789:;<=>?");
  strcat(cref, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
/* p2c: bm2font.pas, line 974:
 * Note: Possible string truncation in assignment [145] */
  strcat(cref, "abcdefghijklmnopqrstuvwxyz");
/* p2c: bm2font.pas, line 975:
 * Note: Possible string truncation in assignment [145] */
  strcpy(fontupc, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  strcpy(fontpre, "abcdefghijklmnopqrstuvwxyz");
  truehres = 0.0;
  truevres = 0.0;
  halfinch = false;
  invert = false;
  greypxl = false;
  pcxtemp = false;
  giftemp = false;
  cutgrey = false;
  aliasused = false;
  cmyk = false;
  cyan = false;
  magenta = false;
  yellow = false;
  black = false;
  saveblack = false;
  clipon = true;
  xratio = 0;
  yratio = 0;
  egastretch = true;
  ledprinter = false;
  distribute = true;
  brightness = 0;
  bitspsam = 8;
  nowhite = true;
  usepxl = 0;
  vusepxl = 0;
  hrep = 1;
  vrep = 1;
  valinc = 70.0;
  gradint = 70;
  newwidth = 0;
  newheight = 0;
  printf("This is BitMapTOfont, version 3.0 of january 94, via p2c\n");
  printf("Converting Bitmap Files to TeX-Fonts\n");
  /*assign(logfile,'test.log');rewrite(logfile);close(logfile);*/
  /*110:*/
  if (P_argc == 1) {
    printf("usage is BM2FONT filename and parameters\n");
    printf("-f<name of picture for TeX>     (std filename)\n");
    printf("-h<horizontal resolution>       (pixel/inch, std 300)\n");
    printf("-v<vertical resolution>         (pixel/inch, std 300)\n");
    printf("-l<length of mapline>           (in bytes, only pure bitmaps)\n");
    printf("-p<height of character 1 inch>  (y or n, std y)\n");
    printf("-e<stretch EGA pictures>        (y or n, std y)\n");
    printf("-i<inversion of pixels>         (y or n, std n)\n");
    printf("-g<greypixels in bitmap>        (y or n, std n)\n");
    printf("-w<let white be light grey>     (y or n, std y)\n");
    printf("-d<distribute errors>           (y or n, std y)\n");
    printf("-s<separation of grey dots>     (y or n, std n)\n");
    printf("-r<repeat each grey pixel>      (y or n, std n)\n");
    printf("-u<pixels for grey rectangle>   (less 8)\n");
    printf("-c<vert. pixels for rectangle>  (less 8)\n");
    printf("-x<bits per sample>             (0 < x < 9)\n");
    printf("-b<reduce halftone colors>      (f.e. by 1, less u*c*4, std 0)\n");
    printf("-t<gradation value>             (in %%, std 70)\n");
    printf("-z<area of gradation>           (in %%, std 70)\n");
    printf("-m<width of picture on paper>   (in mm)\n");
    printf("-n<height of picture on paper>  (in mm)\n");
    printf("-j<clip off white space>        (y or n, std y)\n");
    printf("-k<color: c,m,y or k>           (std k)\n");
    /*readln(comment);
if length(comment)=0 then goto 9999;j:=ord(comment[0])+1;
if j<=127 then move(comment[0],mem[prefixseg:$80],j);*/
    goto _L9999;
  }
  /*:110*/
  /*111:*/
  for (j = 1; j < P_argc; j++) {
    strcpy(comment, P_argv[j]);
    if (comment[0] != '-') {
      strcpy(font, comment);
      if (strlen(font) < 1 || !strcmp(font, " ")) {
	         printf("give the name of your bitmap file next time\n");
	         goto _L9999;
      }
    } 
    else {
      switch (comment[1]) {

      case 'h':
      case 'H':
        	strdelete((Anyptr)comment, 1, 2);
        	i = (sscanf(comment, "%lg", &truehres) == 0);
        	break;

      case 'v':
      case 'V':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%lg", &truevres) == 0);
      	break;

      case 'l':
      case 'L':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &mapinlen) == 0);
      	break;

      case 'm':
      case 'M':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &newwidth) == 0);
      	break;

      case 'n':
      case 'N':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &newheight) == 0);
      	break;

      case 'c':
      case 'C':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &vusepxl) == 0);
      	break;

      case 'b':
      case 'B':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &brightness) == 0);
      	break;

      case 'x':
      case 'X':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &bitspsam) == 0);
      	break;

      case 't':
      case 'T':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%lg", &valinc) == 0);
      	break;

      case 'z':
      case 'Z':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &gradint) == 0);
      	break;

      case 'g':
      case 'G':
      	strdelete((Anyptr)comment, 1, 2);
      	greypxl = (!strcmp(comment, "y") || !strcmp(comment, "Y"));
      	break;

      case 'e':
      case 'E':
      	strdelete((Anyptr)comment, 1, 2);
      	egastretch = (!strcmp(comment, "n") || !strcmp(comment, "N"));
      	egastretch = !egastretch;
      	break;

      case 'd':
      case 'D':
      	strdelete((Anyptr)comment, 1, 2);
      	distribute = (!strcmp(comment, "n") || !strcmp(comment, "N"));
      	distribute = !distribute;
      	break;

      case 'f':
      case 'F':
      	strdelete((Anyptr)comment, 1, 2);
      	strcpy(aliasname, comment);
      	aliasused = true;
      	break;

      case 's':
      case 'S':
      	strdelete((Anyptr)comment, 1, 2);
      	ledprinter = (!strcmp(comment, "y") || !strcmp(comment, "Y"));
      	break;

      case 'p':
      case 'P':
      	strdelete((Anyptr)comment, 1, 2);
      	halfinch = (!strcmp(comment, "n") || !strcmp(comment, "N"));
      	break;

      case 'r':
      case 'R':
      	strdelete((Anyptr)comment, 1, 2);
      	if (!strcmp(comment, "y")) {
      	  hrep = 2;
      	  vrep = 2;
      	}
      	break;

      case 'w':
      case 'W':
      	strdelete((Anyptr)comment, 1, 2);
      	nowhite = (!strcmp(comment, "n") || !strcmp(comment, "N"));
      	nowhite = !nowhite;
      	break;

      case 'k':
      case 'K':
      	strdelete((Anyptr)comment, 1, 2);
      	if (!strcmp(comment, "c") || !strcmp(comment, "N"))
      	  cyan = true;
      	else if (!strcmp(comment, "m") || !strcmp(comment, "M"))
      	  magenta = true;
      	else if (!strcmp(comment, "y") || !strcmp(comment, "Y"))
      	  yellow = true;
      	else if (!strcmp(comment, "k") || !strcmp(comment, "K"))
      	  black = true;
      	break;

      case 'i':
      case 'I':
      	strdelete((Anyptr)comment, 1, 2);
      	invert = (!strcmp(comment, "y") || !strcmp(comment, "Y"));
      	break;

      case 'j':
      case 'J':
      	strdelete((Anyptr)comment, 1, 2);
      	clipon = (!strcmp(comment, "y") || !strcmp(comment, "Y"));
      	break;

      case 'u':
      case 'U':
      	strdelete((Anyptr)comment, 1, 2);
      	i = (sscanf(comment, "%ld", &usepxl) == 0);
      	break;
            }
          }
        }
  /*:111*/
  /*112:*/
  if (bitspsam < 1 || bitspsam > 8)
    bitspsam = 8;
  if (invert) {
    invbit = 0;
    invbyte = 0;
  } else {
    invbit = 1;
    invbyte = 255;
  }
  if (usepxl == 0)
    usepxl = 2;
  if (vusepxl == 0)
    vusepxl = usepxl;
  if (brightness >= usepxl * vusepxl * 4)
    brightness = 0;
  if (brightness != 0 && usepxl < 2)
    brightness = 0;
  if (valinc > 99)
    valinc = 99.0;
  if (valinc > 0) {
    if (gradint == 0)
      gradint = 1;
  }
  if (gradint > 99)
    gradint = 99;
  if (newheight < 0)
    newheight = 0;
  if (newwidth < 0)
    newwidth = 0;
  if (newwidth > 200) {
    printf("Sorry, new width set to 200mm\n");
    newwidth = 200;
  }
  if (newheight > 280) {
    printf("Sorry, new height set to 280mm\n");
    newheight = 280;
  }
  if (truehres == 0)
    truehres = 300.0;
  if (truevres == 0)
    truevres = truehres;
  cmyk = (cyan || magenta || yellow || black);
  saveblack = (cyan || magenta || yellow);   /*:112*/
  /*:107*/
  /*108:*/
  for (j = 0; j <= 51; j++) {
    for (i = 0; i <= 128; i++) {
      pwidth[j][i] = 0;
      width[j][i] = 0;
      height[j][i] = 0;
      pheight[j][i] = 0;
      yoffset[j][i] = 0;
    }
  }
  for (i = 0; i <= 128; i++)
    dirpoint[i] = 0;
  for (i = 0; i <= 128; i++)
    pkpoint[i] = 0;
  for (i = 0; i <= 52; i++)
    charpf[i] = 0;
  maxx = 0;
  minx = 646;
  mapheight = 0;   /*:108*/
  fok = true;
  strcpy(bmname, font);
  strcpy(bitmap_NAME, bmname);
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  _SETIO(bitmap != NULL, FileNotFound);
  filestat = P_ioresult;
  if (filestat == 0)
    fok = false;
  else
    fok = true;
  if (fok) {   /*113:*/
    printf("File %s not found, abort\n", font);
    fileproblem();
    goto _L9999;
  }
  i = 1;
  j = 0;
  strcpy(cmd, " ");
  while (i <= strlen(bmname)) {
    if (bmname[i - 1] == '.')
      j = i;
    i++;
  }
  if (j > 0)
    strsub(cmd, bmname, j + 1, (int)(strlen(bmname) - j + 1));
  if (!strcmp(cmd, "tif") || !strcmp(cmd, "TIF") || !strcmp(cmd, "tiff") ||
      !strcmp(cmd, "TIFF"))
    tifint();
  else {
    if (!strcmp(cmd, "pcx") || !strcmp(cmd, "PCX"))
      pcxint();
    else if (!strcmp(cmd, "lbm") || !strcmp(cmd, "LBM") ||
	     !strcmp(cmd, "iff") || !strcmp(cmd, "IFF"))
      iffint();
    else if (!strcmp(cmd, "gif") || !strcmp(cmd, "GIF"))
      gifint();
    else if (!strcmp(cmd, "bmp") || !strcmp(cmd, "BMP"))
      bmpint();
    else if (!strcmp(cmd, "img") || !strcmp(cmd, "IMG"))
      imgint();
    else if (!strcmp(cmd, "cut") || !strcmp(cmd, "CUT"))
      cutint();
    else
      posbit = 0;
  }
  if (aliasused) {
    strcpy(font, aliasname);
    strcpy(bmname, aliasname);
  }
  FORLIM = strlen(bmname);
  for (i = 1; i <= FORLIM; i++) {
    sprintf(STR2, "%c", bmname[i - 1]);
    j = strpos2(fontpre, STR2, 1);
    if (j != 0)
      bmname[i - 1] = fontupc[j - 1];
  }
  FORLIM = strlen(font);
  for (i = 1; i <= FORLIM; i++) {
    sprintf(STR2, "%c", font[i - 1]);
    j = strpos2(fontupc, STR2, 1);
    if (j != 0)
      font[i - 1] = fontpre[j - 1];
  }
  korrfont();
  nameok = true;
  FORLIM = strlen(font);
  for (i = 1; i <= FORLIM; i++) {
    if (isdigit(font[i - 1]))
      nameok = false;
  }
  if (!nameok) {
    printf("no digits allowed in name of font\n");
    goto _L9999;
  }
  strcpy(bmname, font);
  FORLIM = strlen(bmname);
  for (i = 1; i <= FORLIM; i++) {   /*:113*/
    sprintf(STR2, "%c", bmname[i - 1]);
    j = strpos2(fontpre, STR2, 1);
    if (j != 0)
      bmname[i - 1] = fontupc[j - 1];
  }
  /*114:*/
  if (truehres <= 0 || truehres > 2000)
    truehres = 300.0;
  if (truevres <= 0 || truevres > 2000)
    truevres = 300.0;
  whatistrue();
  if (hres != (long)floor(truehres + 0.5))
    printf("maximum width of characters is %ld pixel\n", hres);
  if (vres != (long)floor(truevres + 0.5))
    printf("maximum height of characters is %ld pixel\n", vres);
  if (posbit != 0)
    pxlinlen = (halfk)((mapwidth + 7) / 8);
  else {
    pxlinlen = mapinlen;
    mapwidth = pxlinlen * 8;
    if (greypxl)   /*116:*/
      mapwidth /= bitspsam;
    if (mapwidth < 1) {
      printf("Width not correct!\n");
      goto _L9999;
    }
    mapheight = (P_maxpos(bitmap)) / mapinlen;
    if ((P_maxpos(bitmap)) % mapinlen > 0) {
      printf("Remainder > 0 when dividing size of file by width!\n");
      goto _L9999;
    }
/* p2c: bm2font.pas, line 1102:
 * Note: Using % for possibly-negative arguments [317] */
    if (greypxl) {
      mapdiv = 1.0;
      photoinf = 15;
      FORLIM1 = bitspsam;
      for (cb = 1; cb <= FORLIM1; cb++)
	       mapdiv *= 2;
         mapdiv /= 16;
    }  /*:116*/
  }
  if (pxlinlen > 3000) {
    printf("File not processable, width > 3000 bytes\n");
    goto _L9999;
  }  /*:114*/
  if (newwidth != 0 || newheight != 0)
    scaling();
  if (greypxl) {  /*94:*/
    printf("Halftone picture required\n");
    pxlinlen = (halfk)(((unsigned long)(mapwidth * bitspsam + 7)) >> 3);
    greypix = mapwidth;
    mapwidth *= bitspsam;   /*95:*/
    sprintf(tmpname, "%s.tmp", font);
    strcpy(tmpfil_NAME, tmpname);
    filestat = P_ioresult;
    if (filestat == 0)
      fok = false;
    else
      fok = true;
    if (fok) {
      printf("tempfile %s not accessable, abort\n", tmpname);
      fileproblem();
      goto _L9999;
    }
    if (tmpfil != NULL)
      tmpfil = freopen(tmpfil_NAME, "w+b", tmpfil);
    else
      tmpfil = fopen(tmpfil_NAME, "w+b");
    _SETIO(tmpfil != NULL, FileNotFound);
    filestat = P_ioresult;
    if (filestat == 0)
      fok = false;
    else
      fok = true;
    if (fok) {   /*:95*/
      printf("Tempfile for font %s not found, abort\n", font);
      fileproblem();
      goto _L9999;
    }
    /*101:*/
    k = 0;
    if (usepxl != vusepxl) {
      FORLIM = vusepxl;
      for (i = 0; i < FORLIM; i++) {
	FORLIM2 = usepxl;
	for (j = 0; j < FORLIM2; j++) {
	  k++;
	  tab[k - 1][0] = i + 1;
	  tab[k - 1][1] = j + 1;
	  tab[k - 1][2] = i * i * (usepxl - 1) * (usepxl - 1) +
			  j * j * (vusepxl - 1) * (vusepxl - 1);
	}
      }
      FORLIM = k;
      for (i = 1; i <= FORLIM; i++) {
	FORLIM2 = k;
	for (j = i; j <= FORLIM2; j++) {
	  if (tab[i - 1][2] > tab[j - 1][2]) {
	    lx = tab[i - 1][0];
	    tab[i - 1][0] = tab[j - 1][0];
	    tab[j - 1][0] = lx;
	    lx = tab[i - 1][1];
	    tab[i - 1][1] = tab[j - 1][1];
	    tab[j - 1][1] = lx;
	    lx = tab[i - 1][2];
	    tab[i - 1][2] = tab[j - 1][2];
	    tab[j - 1][2] = lx;
	  }
	}
      }
      FORLIM = k;
      for (i = 1; i <= FORLIM; i++) {
	lx = tab[i - 1][0];
	ly = tab[i - 1][1];
	ditherm[lx - 1][ly - 1] = i;
      }
    }
    if (usepxl > 7)
      usepxl = 7;
    if (vusepxl > 7)
      vusepxl = 7;
    maxcol = 1;
    cb = 0;
    usecol = usepxl * vusepxl * 4;
    FORLIM = bitspsam;
    for (k = 1; k <= FORLIM; k++)
      maxcol *= 2;
    maxcol--;
    for (k = 1; k <= 4; k++) {
      for (i = 0; i <= 196; i++) {
	for (j = 1; j <= 7; j++)
	  pattern[k - 1][i][j - 1] = 0;
      }
    }
    FORLIM = vusepxl;
    for (i = 1; i <= FORLIM; i++) {
      FORLIM2 = usepxl;
      for (j = 1; j <= FORLIM2; j++) {
	if (ditherm[i - 1][j - 1] <= usecol / 4 && ditherm[i - 1][j - 1] > 0) {
	  v = (ditherm[i - 1][j - 1] - 1) * 4 + 1;
	  for (ccol = 1; ccol <= 4; ccol++) {
	    if (ccol == 1)
	      c = 1;
	    else if (ccol == 2)
	      c = 3;
	    else if (ccol == 3)
	      c = 4;
	    else
	      c = 2;
	    FORLIM3 = usecol;
	    for (k = v; k <= FORLIM3; k++) {
	      switch (c) {

	      case 4:
		if (usepxl > 2 || vusepxl > 2)
		  pattern[0][k][j - 1] |= (cb + 2) << (7 - i);
		else
		  pattern[0][k][i - 1] |= (cb + 2) << (7 - j);
		break;

	      case 1:
		pattern[1][k][vusepxl - i] |= (cb + 1) << (j - usepxl + 7);
		break;

	      case 2:
		if (usepxl > 2 || vusepxl > 2)
		  pattern[2][k][vusepxl - j] |= (cb + 2) << (7 - i);
		else
		  pattern[2][k][vusepxl - i] |= (cb + 2) << (7 - j);
		break;

	      case 3:
		pattern[3][k][i - 1] |= (cb + 1) << (j - usepxl + 7);
		break;
	      }
	    }
	    v++;
	  }
	}
      }
    }
    if (nowhite)
      pattern[1][0][usepxl - 1] = 128 >> (usepxl - 1);
    usecol -= brightness;   /*:101*/
    /*[102:]append(logfile);
for k:=0 to usecol do begin for j:=1 to vusepxl do begin for i:=1 to 4
do begin cb:=pattern[i,k,j];write(logfile,cb:4,' ');
for pk:=1 to usepxl do begin if cb>127 then write(logfile,'1')else write
(logfile,'0');cb:=cb shl 1;end;write(logfile,' ');end;
writeln(logfile,'.');end;writeln(logfile,'---- ',k:1,' ----');end;
close(logfile);[:102]*/
    greypix -= greypix & 3;
    mapwidth = greypix * bitspsam;
    if (ledprinter)
      gbufpp = ((long)floor(greypix * (usepxl + 0.5) + 0.5) * hrep + 7) / 8;
    else
      gbufpp = (greypix * usepxl * hrep + 7) / 8;
    if (gbufpp > 1280) {
      printf("Only up to 1280 bytes in one row allowed!\n");
      printf("Try again by decreasing param <u> or <r=n>\n");
      _Escape(0);
    }  /*96:*/
    printf("Analysing and optimizing the picture\n");
    pminval = 255;
    pmaxval = 0;
    if (cmyk) {
      pminval = 0;
      pmaxval = maxcol;
    }
    if (cutgrey) {
      checksum = mapheight;
      pxlinlen = cutlen;
    } else
      checksum = mapheight;
    pl = 0;
    fseek(bitmap, posbit, 0);
    do {
      pxlinlen = fread(b1, 1, pxlinlen, bitmap);
      colpos = 0;
      cutrep = 0;
      FORLIM = greypix;
      for (pk = 0; pk < FORLIM; pk++) {
	tmpcolor = getcolor();
	if (tmpcolor > pmaxval)
	  pmaxval = tmpcolor;
	if (tmpcolor < pminval)
	  pminval = tmpcolor;
      }
      checksum--;
      if (cutgrey)
	pxlinlen = b1[pxlinlen - 1] * 256 + b1[pxlinlen - 2] + 2;
    } while (checksum != 0);
/* p2c: bm2font.pas, line 1165:
 * Note: Can't interpret size in BLOCKREAD [174] */
    if (pminval == pmaxval && !cmyk) {
      printf("Only one color (value %d) used by bitmap!\n", pmaxval);
      printf("It makes no sence to generate a picture!\n");
      _Escape(0);
    }  /*:96*/
    if (brightness == 0) {
      brightness = (long)floor(
	    (maxcol - pmaxval + pminval + 1.0) * usecol / (maxcol + 1) + 0.5);
      if (brightness > 0)
	printf("Best result may be with parameter -b%ld !?\n", brightness);
    }
    printf("Dithering the picture\n");
    memset((Anyptr)greymem, 255, sizeof(uchar) * 32761L);
    pgreymem = 0;
    if (cutgrey) {
      checksum = mapheight;
      pxlinlen = cutlen;
    } else
      checksum = mapheight;
    pl = 0;
    fseek(bitmap, posbit, 0);
    patswitch = 4;
    spreadcol = (maxcol + 1.0) / (pmaxval - pminval + 1);
    patref = (double)usecol / maxcol;   /*97:*/
    for (k = 0; k <= 255; k++)
      pxllook[k] = k;
    if (invert) {
      for (k = 0; k <= 255; k++)
	pxllook[k] = 255 - k;
    }
    if (invert) {
      FORLIM = pmaxval;
      for (k = pminval; k <= FORLIM; k++)
	pxllook[pmaxval - k + pminval] =
	  (long)floor((k - pminval) * spreadcol + 0.5);
      invbit = 1;
      invbyte = 255;
    } else {
      FORLIM = pmaxval;
      for (k = pminval; k <= FORLIM; k++)
	pxllook[k] = (long)floor((k - pminval) * spreadcol + 0.5);
    }
    FORLIM = maxcol;
    for (k = 0; k <= FORLIM; k++)
      lutone[k] = (long)floor((maxcol - k) * patref + 0.5);
    if (valinc > 0) {   /*98:*/
      k = pminval;
      pk = 0;
      while (pk <= gradint && k <= pmaxval) {
	pk = (long)floor(pxllook[k] * 100.0 / maxcol + 0.5);
	k++;
      }
      pkn = pxllook[k - 1];
      grxzero = pkn;
      redval = valinc / 100;
      FORLIM = pmaxval;
      for (k = pminval; k <= FORLIM; k++) {
	/*write(logfile,(pxllook[k]/maxcol):1:5
);*/
	grx = pxllook[k];
	if (grx <= pkn) {
	  if (grx > 0)
	    pxllook[k] = (long)
			 floor(0.5 * grx * (exp(redval * log(grx / grxzero)) +
				 exp(-redval * log(grx / grxzero))) + 0.5);
/* p2c: bm2font.pas, line 1353: 
 * Note: Line breaker spent 1.0 seconds, 5000 tries on line 4297 [251] */
	}
	/*writeln(logfile,' ',(pxllook[k]/maxcol):1:5);*/
      }  /*close(logfile);;*/
      /*:98*/
    }
    /*append(logfile);*/
    FORLIM = maxcol;
    for (pk = 0; pk <= FORLIM; pk++)
      hktab[pk] = (long)floor((maxcol - pk) * patref * 100 + 0.5) -
		  (long)(lutone[pk] * 100.0);
    cspread = false;
    if (usecol - 1 > maxcol) {
      pk = usecol;
      for (k = maxcol; k >= 0; k--) {
	if (invert)
	  pk = usecol - lutone[pxllook[maxcol - k]];
	else
	  pk = usecol - lutone[pxllook[k]];
	while (pk >= k) {
	  lutone[pk] = lutone[pxllook[k]];
	  hktab[pk] = (long)floor(lutone[pk] * 100.0 + 0.5) -
		      (long)floor((usecol - pk) * 100.0 + 0.5);
	  lutone[pk] -= hktab[pk] / 100;
	  pk--;
	}
      }
      if (invert) {
	FORLIM = usecol;
	for (k = 0; k <= FORLIM; k++)
	  pxllook[k] = lutone[k];
      } else {
	FORLIM = usecol;
	for (k = 0; k <= FORLIM; k++)
	  pxllook[k] = usecol - lutone[k];
      }
      maxcol = usecol;
      cspread = true;
    }
    invert = false;
    mapdiv = (usecol + 1.0) / 16;
    FORLIM = usecol;
    for (k = 0; k <= FORLIM; k++)
      lutvga[k] = (long)((usecol - k) / mapdiv);
    for (pk = -255; pk <= 255; pk++) {
      if (cspread)
	gkorh[pk + 255] = (long)(pk / 2.0);
      else
	gkorh[pk + 255] = (long)floor(pk / 2.0 * spreadcol + 0.5);
      if (cspread)
	gkordivp[pk + 255] = (long)(pk / 2.0);
      else
	gkordivp[pk + 255] = (long)(pk / 2.0 * patref + hktab[abs(pk)] / 100.0);
    }
    for (pk = 0; pk <= 255; pk++)   /*:97*/
      spreadvals[pk] = (long)floor(pk * patref + 0.5);
    do {
      pxlinlen = fread(b1, 1, pxlinlen, bitmap);
      colpos = 0;
      cutrep = 0;
      FORLIM = greypix;
      for (pk = 0; pk < FORLIM; pk++)
	b4[pk] = getcolor();
      if (cspread) {
	FORLIM = greypix;
	for (pk = 0; pk < FORLIM; pk++)
	  b4[pk] = spreadvals[b4[pk]];
      }
      if (distribute) {   /*99:*/
	pk = 1;
	pkn = 1;
	while (pk < greypix) {
	  pkn++;
	  greykor = 0;
	  if (b4[pk] != b4[pkn]) {
	    greykor = gkorh[b4[pk] - b4[pkn] + 255];
	    greykor = gkordivp[greykor + 255];
	  }
	  if (greykor != 0) {
	    tmpcolor = lutone[pxllook[b4[pkn]]];
	    if (abs(tmpcolor + greykor) <= usecol &&
		abs(tmpcolor + greykor) >= 0)
	      b4[pkn] += greykor;
	  }
	  pk++;
	}
	pk = greypix - 1;
	pkn = pk;
	while (pk > 0) {   /*:99*/
	  pkn--;
	  greykor = 0;
	  if (b4[pk] != b4[pkn]) {
	    greykor = gkorh[b4[pk] - b4[pkn] + 255];
	    greykor = gkordivp[greykor + 255];
	  }
	  if (greykor != 0) {
	    tmpcolor = lutone[pxllook[b4[pkn]]];
	    if (abs(tmpcolor + greykor) <= usecol &&
		abs(tmpcolor + greykor) >= 0)
	      b4[pkn] += greykor;
	  }
	  pk--;
	}
      }
      FORLIM = greypix;
      for (pk = 0; pk < FORLIM; pk++)
	b4[pk] = lutone[pxllook[b4[pk]]];
      FORLIM1 = vrep;
      for (yrep = 1; yrep <= FORLIM1; yrep++) {   /*100:*/
	FORLIM = vusepxl;
	for (k = 1; k <= FORLIM; k++) {
	  gbufp = 0;
	  cb = 0;
	  pn = 0;
	  switch (patswitch) {

	  case 1:
	    curpat[0] = 2;
	    curpat[1] = 3;
	    break;

	  case 2:
	    curpat[0] = 4;
	    curpat[1] = 1;
	    break;

	  case 3:
	    curpat[0] = 3;
	    curpat[1] = 2;
	    break;

	  case 4:
	    curpat[0] = 1;
	    curpat[1] = 4;
	    break;
	  }
/* p2c: bm2font.pas, line 1233:
 * Note: Can't interpret size in FILLCHAR [174] */
	  memset((Anyptr)b3, 0, (long)gbufpp);
	  FORLIM2 = greypix;
	  for (pk = 0; pk < FORLIM2; pk++) {
	    FORLIM4 = hrep;
	    for (xrep = 1; xrep <= FORLIM4; xrep++) {
	      cb = pattern[curpat[pn] - 1][b4[pk]][k - 1];
	      if (saveblack)
		cb &= ~pattern[curpat[pn] - 1][bhell[b4[pk]]][k - 1];
	      dbuf = ((unsigned)gbufp) >> 3;
	      bufsh = gbufp & 7;
	      nextbuf = bufsh + usepxl;
	      switch (bufsh) {

	      case 0:
		b3[dbuf] = cb;
		break;

	      default:
		b3[dbuf] |= cb >> bufsh;
		if (nextbuf > 8)
		  b3[dbuf + 1] = cb << (8 - bufsh);
		break;
	      }
	      gbufp += usepxl;
	      if (ledprinter) {
		if (curpat[pn] == 1 || curpat[pn] == 3)
		  gbufp++;
	      }
	      pn = abs(pn - 1);
	    }
	  }
	  FORLIM2 = gbufpp;
	  for (pk = 0; pk <= FORLIM2; pk++)
	    b3[pk] = ~b3[pk];
	  if (pgreymem + gbufpp > 65522L) {
	    _SETIO(fwrite(greymem, pgreymem, 1, tmpfil) == 1, FileWriteError);
	    filestat = P_ioresult;
	    if (filestat != 0) {
	      _SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
		     FileWriteError);
	      fileproblem();
	      _Escape(0);
	    }
	    pgreymem = 0;
	  }
/* p2c: bm2font.pas, line 1242:
 * Note: Can't interpret size in BLOCKWRITE [174] */
/* p2c: bm2font.pas, line 1245: Note: Can't interpret size in MOVE [174] */
	  memmove((Anyptr)(&greymem[pgreymem]), (Anyptr)b3, (long)gbufpp);
	  pgreymem += gbufpp;
	}
/* p2c: bm2font.pas, line 1246:
 * Note: Can't interpret size in FILLCHAR [174] */
	memset((Anyptr)b3, 255, (long)gbufpp);
	if (ledprinter) {
	  if (patswitch == 2 || patswitch == 4) {
	    if (pgreymem + gbufpp > 65522L) {
	      _SETIO(fwrite(greymem, pgreymem, 1, tmpfil) == 1,
		     FileWriteError);
	      filestat = P_ioresult;
	      if (filestat != 0) {
		_SETIO(printf("Error occured when writing file %s!\n",
			      tmpname) >= 0, FileWriteError);
		fileproblem();
		_Escape(0);
	      }
	      pgreymem = 0;
	    }
/* p2c: bm2font.pas, line 1249:
 * Note: Can't interpret size in BLOCKWRITE [174] */
/* p2c: bm2font.pas, line 1252: Note: Can't interpret size in MOVE [174] */
	    memmove((Anyptr)(&greymem[pgreymem]), (Anyptr)b3, (long)gbufpp);
	    pgreymem += gbufpp;
	  }  /*:100*/
	}
	patswitch++;
	if (patswitch > 4)
	  patswitch = 1;
      }
      pm = 128;
      pb = pl;
      FORLIM = greypix;
      for (pk = 0; pk < FORLIM; pk++) {
	pxlcolor = lutvga[b4[pk]];
	pm >>= 1;
	if (pm == 0) {
	  pm = 128;
	  pb++;
	}
      }
      pl += 80;
      if (pl >= 38400L)
	pl = 0;
      checksum--;
      if (cutgrey)
	pxlinlen = (halfk)(b1[pxlinlen - 1] * 256 + b1[pxlinlen - 2] + 2);
    } while (checksum != 0);
/* p2c: bm2font.pas, line 1213:
 * Note: Can't interpret size in BLOCKREAD [174] */
    if (pgreymem != 0) {  /*$I-*/
      _SETIO(fwrite(greymem, pgreymem, 1, tmpfil) == 1, FileWriteError);
      filestat = P_ioresult;
      if (filestat != 0) {
	_SETIO(printf("Error occured when writing file %s!\n", tmpname) >= 0,
	       FileWriteError);
	fileproblem();
	_Escape(0);
      }
    }
/* p2c: bm2font.pas, line 1259:
 * Note: Can't interpret size in BLOCKWRITE [174] */
    posbit = 0;
    if (ledprinter)
      mapwidth = (long)floor(greypix * (usepxl + 0.5) + 0.5) * hrep;
    else
      mapwidth = greypix * usepxl * hrep;
    pxlinlen = (mapwidth + 7) / 8;
    mapinlen = pxlinlen;
    if (ledprinter)
      mapheight = (long)floor(mapheight * (vusepxl + 0.5) + 0.5) * vrep;
    else
      mapheight *= vusepxl * vrep;
    if (tmpfil != NULL)
      fclose(tmpfil);
    tmpfil = NULL;
    if (bitmap != NULL)
      fclose(bitmap);
    bitmap = NULL;
    strcpy(bitmap_NAME, tmpname);
    if (bitmap != NULL)
      bitmap = freopen(bitmap_NAME, "r+b", bitmap);
    else
      bitmap = fopen(bitmap_NAME, "r+b");
    if (bitmap == NULL)
      _EscIO(FileNotFound);
  }
  mapwidth = pxlinlen * 8;
  zeropads = 0;
  maplines = mapheight;
  if (clipon)   /*117:*/
  {  /*115:*/
    checksum = mapheight * ((mapwidth + 7) / 8);
    mapheight = 0;
    freelines = 0;
    fseek(bitmap, posbit, 0);
    while (checksum >= pxlinlen) {
      fread(b1, pxlinlen, 1, bitmap);
      mapwidth = pxlinlen * 8;
      j = pxlinlen - 1;
      while (b1[j] == invbyte && j >= 0)
	j--;
      if (j >= 0) {
	i = 0;
	while (b1[i] == invbyte && i <= j)
	  i++;
	if (i < minx)
	  minx = i;
	lx = j * 8 + 8;
	cb = b1[j];
	for (i = 1; i <= 8; i++) {
	  if ((cb & 1) == invbit) {
	    cb >>= 1;
	    lx--;
	  } else
	    i = 8;
	}
	if (lx > maxx)
	  maxx = lx;
	freelines++;
	mapheight += freelines;
	freelines = 0;
      } else if (mapheight == 0)
	posbit += pxlinlen;
      else
	freelines++;
      checksum -= pxlinlen;
    }
/* p2c: bm2font.pas, line 1271:
 * Note: Can't interpret size in BLOCKREAD [174] */
    mapwidth = maxx - minx * 8;
    zeropads = pxlinlen - (mapwidth + 7) / 8;
    maplines = mapheight;
    posbit += minx;   /*:115*/
  }
  i = (mapwidth + hres - 1) / hres;
  j = (mapheight + vres - 1) / vres;
  nj = j;
  nofchars = i * j;
  mincharpf = 515832L / (vres * ((hres + 31) / 32) * 32);
  noffonts = (nofchars + mincharpf - 1) / mincharpf;
  if (noffonts > 52) {
    printf("Sorry, bitmap is too large! Giving up\n");
    goto _L9999;
  }
  if (mincharpf > 128) {   /*:117*/
    mincharpf = 128;
    noffonts = (nofchars + 127) / 128;
  }
  /*118:*/
  k = 0;
  c = 0;
  while (mapheight > 0) {   /*:118*/
    maxx = mapwidth;
    while (maxx > 0) {
      if (maxx > hres)
	pwidth[k][c] = hres;
      else
	pwidth[k][c] = maxx;
      if (mapheight > vres)
	pheight[k][c] = vres;
      else
	pheight[k][c] = mapheight;
      dsize = (long)floor(vres / truehres * 72.27 * 65536L * 16 + 0.5);
      tabdsize[k] = dsize;
      c++;
      if (c == mincharpf || mapheight <= vres && maxx <= hres) {
	FORLIM1 = mincharpf;
	for (c = 0; c < FORLIM1; c++) {
	  height[k][c] = (long)floor(pheight[k][c] / truevres * 4736286.7227 /
				     dsize * 16777215L + 0.5);
	  width[k]
	    [c] = (long)floor(pwidth[k][c] / truehres * 4736286.7227 / dsize *
			      16777215L + 0.5);
	}
	k++;
	c = 0;
      }
      maxx -= hres;
    }
    mapheight -= vres;
  }
  maxx = (mapwidth + hres - 1) / hres;
  f = 0;
  g = 0;
  pxlbmi = 4;
  if (fok) {
    printf("error occurred when allocating pxlfile ");
    puts(cmd);
    fileproblem();
    goto _L9999;
  }
  if (bitmap != NULL)
    fclose(bitmap);
  bitmap = NULL;
  if (bitmap != NULL)
    bitmap = freopen(bitmap_NAME, "rb", bitmap);
  else
    bitmap = fopen(bitmap_NAME, "rb");
  if (bitmap == NULL)
    _EscIO(FileNotFound);
  fonteject();   /*119:*/
  FORLIM = noffonts;
  for (a = 0; a < FORLIM; a++) {   /*:119*/
    lh = 17;
    bc = 0;
    ec = 127;
    while (pheight[a][ec] == 0)   /*120:*/
      ec--;
    sprintf(cmd, "%s%c.tfm", font, fontpre[a]);
    strcpy(tfmfile_NAME, cmd);
    if (tfmfile != NULL)
      tfmfile = freopen(tfmfile_NAME, "w+b", tfmfile);
    else
      tfmfile = fopen(tfmfile_NAME, "w+b");
    _SETIO(tfmfile != NULL, FileNotFound);
    filestat = P_ioresult;
    if (filestat == 3 || filestat == 5) {
      strcpy(cmd, bmname);
      sprintf(cmd + strlen(cmd), "%c.tfm", fontupc[a]);
      strcpy(tfmfile_NAME, cmd);
      if (tfmfile != NULL)
	tfmfile = freopen(tfmfile_NAME, "w+b", tfmfile);
      else
	tfmfile = fopen(tfmfile_NAME, "w+b");
      _SETIO(tfmfile != NULL, FileNotFound);
      filestat = P_ioresult;
    }
    if (filestat == 0)
      fok = false;
    else
      fok = true;
    if (fok) {
      printf("error occurred when allocating tfmfile ");
      puts(cmd);
      fileproblem();
      goto _L9999;
    }
    printf("Generating tfmfile %s\n", cmd);   /*:120*/
    dsize = (long)floor(vres / truehres * 72.27 * 65536L * 16 + 0.5);
    tabdsize[a] = dsize;
    FORLIM2 = ec;
    for (k = bc; k <= FORLIM2; k++) {
      height[a][k] = (long)floor(
	    pheight[a][k] / truevres * 4736286.7227 / dsize * 16777215L + 0.5);
      width[a][k] = (long)floor(
	    pwidth[a][k] / truehres * 4736286.7227 / dsize * 16777215L + 0.5);
    }
    fh = height[a][bc];
    fw = width[a][bc];
    sh = fh;
    sw = fw;
    nw = 2;
    nh = 2;
    FORLIM2 = ec;
    for (k = bc; k <= FORLIM2; k++) {
      if (height[a][k] != 0 && height[a][k] != fh && height[a][k] != sh) {
	sh = height[a][k];
	nh++;
      }
      if (width[a][k] != 0 && width[a][k] != fw && width[a][k] != sw) {
	sw = width[a][k];
	nw++;
      }
    }
    if (nh > 3) {
      printf("more than 2 heights, should be impossible\n");
      goto _L9999;
    }
    if (nw > 3) {
      printf("more than 2 widths, should be impossible\n");
      goto _L9999;
    }
    nd = 2;
    ni = 2;
    nl = 0;
    nk = 0;
    ne = 0;
    np = 0;
    lf = lh + ec - bc + nw + nh + nd + ni + nk + nl + ne + np + 7;
    checksum = 0;
    tfmhword(lf);
    tfmhword(lh);
    tfmhword(bc);
    tfmhword(ec);
    tfmhword(nw);
    tfmhword(nh);
    tfmhword(nd);
    tfmhword(ni);
    tfmhword(nl);
    tfmhword(nk);
    tfmhword(ne);
    tfmhword(np);
    tfmword(checksum);
    tfmword(dsize);
    strcpy(tfmstr, "0Graphic");
    tfmstr[0] = '\007';
    FORLIM2 = strlen(tfmstr);
    for (i = 1; i <= FORLIM2; i++) {
      tfmb = tfmstr[i - 1];
      fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
    }
    tfmb = 0;
    for (i = 1; i <= 32; i++)
      fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
    strcpy(tfmstr, "0Bitmap");
    tfmstr[0] = '\006';
    FORLIM2 = strlen(tfmstr);
    for (i = 1; i <= FORLIM2; i++) {
      tfmb = tfmstr[i - 1];
      fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
    }
    tfmb = 0;
    for (i = 1; i <= 13; i++)
      fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
    FORLIM2 = ec;
    for (i = bc; i <= FORLIM2; i++) {
      if (width[a][i] == 0) {
	tfmb = 0;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      } else if (width[a][i] == fw) {
	tfmb = 1;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      } else {
	tfmb = 2;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      }
      if (height[a][i] == 0) {
	tfmb = 0;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      } else if (height[a][i] == fh) {
	tfmb = 16;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      } else {
	tfmb = 32;
	fwrite(&tfmb, sizeof(uchar), 1, tfmfile);
      }
      tfmhword(0L);
    }
    tfmword(0L);
    tfmword(fw);
    if (nw > 2)
      tfmword(sw);
    tfmword(0L);
    tfmword(fh);
    if (nh > 2)
      tfmword(sh);
    tfmword(0L);
    tfmword(0L);
    tfmword(0L);
    tfmword(0L);
    if (tfmfile != NULL)
      fclose(tfmfile);
    tfmfile = NULL;
  }
  userhelp();   /*109:*/
  if (pcxtemp)
/* p2c: bm2font.pas, line 1353: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "pcxtemp.tmp");
#else
    Exec("rm", "pcxtemp.tmp");
#endif
  if (giftemp)
/* p2c: bm2font.pas, line 1353: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", "giftemp.tmp");
#else
    Exec("rm", "giftemp.tmp");
#endif
  if (greypxl)
/* p2c: bm2font.pas, line 1353: Note: Called procedure Exec [285] */
#ifdef MSDOS
    Exec("del", tmpname);
#else
    Exec("rm", tmpname);
#endif
  printf("input %s.tex into your document", font);
  printf(" and set the picture with \\set%s\n", font);   /*:109*/
_L9999:
  if (texfile != NULL)
    fclose(texfile);
  if (bitmap != NULL)
    fclose(bitmap);
  if (pxlfile != NULL)
    fclose(pxlfile);
  if (tmpfil != NULL)
    fclose(tmpfil);
  if (tfmfile != NULL)
    fclose(tfmfile);
  exit(EXIT_SUCCESS);
}  /*:106*/



/* End. */
