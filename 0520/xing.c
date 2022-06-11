#include <stdio.h>


int main(void)
{
	int n;
	printf("请如数一个整数\n");
	scanf("%d", &n);
	
	int i, j;
	for(i=0; i<n; i++) //控制层 0, 1, 2, 
	{
		for(j=0; j<=i; j++)
			printf("*");
		printf("\n");
	}

	return 0;
}