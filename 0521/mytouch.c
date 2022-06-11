#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])  //  ./mytouch 1.txt
{
	//打开并创建文件
	int fd = open(argv[1], O_RDONLY|O_CREAT, 0644);
	if(fd == -1)	//失败
	{
		perror("open() failed"); //open() failed:.....
		return 0;
	}
	
	// printf("open() success\n");
	
	//关闭文件
	close(fd);
	
	return 0;
}