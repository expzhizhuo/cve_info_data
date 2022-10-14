/*
 * Bitmap to LaTeX Sprite 
 * by Marc David Rovner (mrovner@ic.sunysb.edu)
 * June 7th, 1992
 */

#include	<stdio.h>
#include	<stdlib.h>

#define MAXFILENAME	1024
#define INITWIDTH	1.5
#define INITHEIGHT	1.5

typedef struct {
	char OutFileName[MAXFILENAME];
	float WidthRatio, HeightRatio;
} ConvInfo;

void conv_bitmap(Stuff,bitmapfile,spritefile,spritename)
ConvInfo Stuff;
FILE *bitmapfile, *spritefile;
char *spritename;
{ char buffer0[80], buffer1[80], temp;
  int width, height, Row, Column, byte, i;

	if ( (fscanf(bitmapfile, "%s %s %i", buffer0, buffer1, &width) == EOF)
		|| (fscanf(bitmapfile, "%s %s %i", buffer0, buffer1, &height) == EOF) )
	{
		fprintf(stderr, "File not correct bitmap file.\n");
		fclose(bitmapfile);
		exit(-1);
	}
	do
	{
		fscanf(bitmapfile, "%s", buffer0);
	}
	while (buffer0[0] != '{');
		
		fprintf(spritefile,"\\sprite{\\%s}(%i,%i)[%.3fin,%.3fin]\n",
			spritename, width, height,
			((width * Stuff.WidthRatio)/160.0),
			((height * Stuff.HeightRatio)/160.0) );

	for (Row = 0; Row < height; ++Row)
	{
		fprintf(spritefile,":");
		for (Column = 0; Column < width; Column = Column + 8)
		{
			if (fscanf(bitmapfile, "%i%c ", &byte, &temp) == EOF)
			{
				fprintf(stderr, "File not correct bitmap file.\n");
				fclose(bitmapfile);
				exit(-1);
			}
			for(i = 0; i<= 7; i++)
			{
				if ( (byte >> i) & 1)
				{
					fprintf(spritefile,"B");
				}
				else
				{
					fprintf(spritefile,".");
				}
			}
		}
		fprintf(spritefile," |\n");
	
	}
	fprintf(spritefile,"\\endsprite\n");

	fclose(bitmapfile);
}

void main(argc,argv)
int argc; char *argv[];
{ ConvInfo Stuff;
  FILE *bitmapfile, *spritefile;
  int filestatus;
  char *c;
  

	/* Assign initial values to conversion information record */
	Stuff.WidthRatio=INITWIDTH;
	Stuff.HeightRatio=INITHEIGHT;
	sprintf(Stuff.OutFileName,"\0");

	/* While there are still command line options...*/
	while (--argc>0 && (*++argv)[0] == '-')
	{
		c = ++(*argv);

		/* User is redefining the width ratio */
		if (strcmp("width",c) == 0)
		{
			--argc; (*++argv);
			Stuff.WidthRatio= atof(*argv);
		}

		/* User is redefining the height ratio */
		else if (strcmp("height",c) == 0)
		{
			--argc; (*++argv);
			Stuff.HeightRatio= atof(*argv);
		}

		/* User is naming a file to put the output in */
		else if (strcmp("output", c) == 0)
		{
			--argc; (*++argv);
			strcpy(Stuff.OutFileName, *argv);
		}

		/* User has given an invalid option */
		else
		{
			fprintf(stderr,"usage:\n  bit2spr [-width width] [-height height] [-output outputfile] [bitmapfiles]\n");
			exit(-1);
		}
	}

	/* Test to see if the user gave an output file */
	if (strcmp("\0", Stuff.OutFileName) != 0)
	{
		/* User did, so try to open it for writing */
		if ( (spritefile = fopen(Stuff.OutFileName, "wt")) == NULL)
		{
			/* Open failed, tell user and quit */
			fprintf(stderr,"Cannot open output file %s\n",Stuff.OutFileName);
			exit(-1);
		}
		/* Open sucess */
		else fprintf(stderr,"Writing to %s\n",Stuff.OutFileName);
	}

	/* User didn't supply an output file, so send output to
	 * standard output (usually the screen)
         */
	else spritefile = stdout;
		

	/* Test to see if user supplied files to be read... */
	if (argc == 0)
		/* User didn't, so get files from stardard input */
		conv_bitmap(Stuff,stdin,spritefile,"Dummy\0");

	/* User did supply files to be read, so while there are still name */
	else while (--argc>=0)
	{
		/* ...try opening current file for reading */
		if ( (bitmapfile=fopen(*argv,"r")) == NULL)
			/* Error opening file for read, so tell user & continue */
			fprintf(stderr,"%s doesn't exists.\n",*argv);
		/* Success opening file, so convert it */
		else
		{
			fprintf(stderr,"Converting %s...\n", *argv);
			conv_bitmap(Stuff,bitmapfile,spritefile,*argv);
		}

		/* move to next name */
		(*++argv);
	}
}

