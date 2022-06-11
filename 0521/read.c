#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	//打开文件
	int fd = open("./1.txt", O_WRONLY);
	if(fd == -1) //文件打开失败
	{
		perror("open() failed");
		return 0;	//结束程序
	}
	
	char buf[10] = {0};
	//读文件数据
	// read(fd, buf, sizeof(buf));	//从fd文件中想要读取sizeof(buf)这么多个字节
	// printf("buf = %s\n", buf);
	int r;
	while(1)	//一次读不完，就读多次
	{
		r = read(fd, buf, sizeof(buf));
		if(r == -1)
		{
			perror("read() failed");
			break;
		}
		if(r == 0)//读完
		{
			break;
		}
		
		 printf("buf = %s\n", buf);
	}
	
	//关闭文件
	close(fd);
	
	return 0;
}