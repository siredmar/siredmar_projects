#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fp;
fp = fopen("test.txt", "a");
if(fp == NULL)
	printf("error fopen\n");

fputs("AAAAAAAAAAAAAAAAAAAAAA", fp);
fclose(fp);
return 0;
}
