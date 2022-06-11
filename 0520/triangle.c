#include <stdio.h>


int main(void)
{
	int a, b, c;
	//1、判断是否能够成三角形
	printf("请输入三条边长\n");
	scanf("%d%d%d", &a, &b, &c);	
	if(a+b>c && a+c>b && b+c>a)
	{
		//等边
		if(a==b && b==c && a==c)
		{
			printf("等边\n");
		}
		//等腰
		else if(a==b || b==c || a==c)
		{
			printf("等腰\n");
		}
		//直角
		else if(a*a+b*b==c*c || a*a+c*c==b*b || b*b+c*c==a*a)
		{
			printf("直角\n");
		}
		else
		{
			printf("其他\n");
		}
		
	}
	else
	{
		printf("不构成三角形\n");
	}
	

	return 0;
}