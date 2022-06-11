#include <stdio.h>

//argc:参数的个数， argv：参数的内容
// int main(int argc, char *argv[])
int main(int argc, char **argv)
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	return 0;
}