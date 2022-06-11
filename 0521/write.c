#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	//打开文件
	int fd = open("./1.txt", O_WRONLY|O_TRUNC);
	if(fd == -1) //文件打开失败
	{
		perror("open() failed");
		return 0;	//结束程序
	}
	
	
	char buf[10] = {"hello"};
	
	write(fd, buf, strlen(buf));
	
	//关闭文件
	close(fd);
	
	return 0;
}
