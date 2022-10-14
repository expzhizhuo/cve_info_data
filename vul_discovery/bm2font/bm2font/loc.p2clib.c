Exec(s1,s2)
char *s1, *s2;
{  char line[100];
   sprintf(line,"%s %s",s1,s2);
/* printf("%s\n",line); */
   system(line);
}
