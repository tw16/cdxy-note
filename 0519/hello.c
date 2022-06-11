#include <stdio.h>

int main(void)
{
	
	printf("hello world!\n");
	printf("hello world!\n");
	printf("hello world!");
	printf("hello world!");
	printf("hello world!\n");
	
	while(1);	//让程序阻塞
	return 0;	//main里面return表示程序结束，子函数里面的return表示调用返回
}


//编译程序、执行程序
//gcc  -o hello hello.c   -o表示指定编译之后生成的文件名
//多文件编译：  gcc -o target a.c b.c c.c
//路径+文件名  ./hello