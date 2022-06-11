#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>   //atoi

int mk_ret, mk_fd;

int main()
{
	//创建有名管道文件
	 if(access("/tmp/mkfifo", F_OK))
	 {
		mk_ret = mkfifo("/tmp/mkfifo",0777);
		if(mk_ret == -1)
		{
			perror("mkfifo() failed");
			return -1;
		}
	 }
	 
	 
	 //打开文件
	mk_fd = open("/tmp/mkfifo", O_RDWR);
	if(mk_fd == -1)
	{
		perror("open() /tmp/mkfifo failed");
		return -1;
	}
	printf("success\n");
	
	// char buf[20] = "hello jack";
	// write(mk_fd, buf, strlen(buf));
	
	
	
	return 0;
}