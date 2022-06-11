#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//使用线程函数需要链接线程库，  
//gcc  xxx.c -o xxx -lpthread


int a=1;

void * fun(void *arg)
{
	while(1)
	{
		sleep(1);
		a++;
		printf("pthread---a=%d\n", a);
	}
}

int main(void)
{
	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);	//创建一条线程
	
	while(1)
	{
		if(a%10 == 0)
			pthread_cancel(tid);
	}
	
	return 0;
}