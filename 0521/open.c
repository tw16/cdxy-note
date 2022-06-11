#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	//打开已存在的文件
	// int open(const char *pathname, int flags);
	// int fd = open("./1.txt", O_RDONLY);
	//打开不存在的文件， 创建
	int fd = open("./2.txt", O_RDONLY|O_CREAT, 0644);
	if(fd == -1)	//失败
	{
		perror("open() failed"); //open() failed:.....
		return 0;
	}
	
	printf("open() success\n");
	
	//关闭文件
	close(fd);
	
	return 0;
}