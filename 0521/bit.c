// & | ~ ^ << >> 

#include <stdio.h>


int main(void)
{
	unsigned int a = 202113793;
	unsigned char *p = (unsigned char *)&a;
	
	printf("%d, %d, %d, %d\n", *p, *(p+1), *(p+2), *(p+3));
	
	unsigned int b = *p | *(p+1)<<8 | *(p+2)<<16 | *(p+3)<<24;
	printf("b = %d\n", b);
	
	return 0;
}
