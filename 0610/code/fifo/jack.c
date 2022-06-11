#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>   //atoi

int mk_ret, mk_ret1, jtor_fd, rtoj_fd;

int main()
{
	//创建有名管道文件
	 if(access("/tmp/jtor", F_OK))
	 {
		mk_ret = mkfifo("/tmp/jtor",0777);
		if(mk_ret == -1)
		{
			perror("mkfifo() failed");
			return -1;
		}
	 }
	 if(access("/tmp/rtoj", F_OK))
	 {
		mk_ret1 = mkfifo("/tmp/rtoj",0777);
		if(mk_ret == -1)
		{
			perror("mkfifo() failed");
			return -1;
		}
	 }
	 
	 
	 //打开文件
	jtor_fd = open("/tmp/jtor", O_RDWR);
	if(jtor_fd == -1)
	{
		perror("open() /tmp/jtor failed");
		return -1;
	}
	
	rtoj_fd = open("/tmp/rtoj", O_RDWR);
	if(rtoj_fd == -1)
	{
		perror("open() /tmp/rtoj failed");
		return -1;
	}
	
	char buf[20] = "ls -lh";
	
	while(1)
	{
		// bzero(buf, sizeof(buf));
		// scanf("%s", buf);
		
		write(jtor_fd, buf, strlen(buf));//发给rose
		
		read(rtoj_fd, buf, sizeof(buf));//读rose
		printf("form rose:%s\n", buf);	
	}
	
	return 0;
}

