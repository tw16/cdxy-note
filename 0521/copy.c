#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) // ./copy src.txt dest.txt
{
	//判断参数的个数
	if(argc != 3)
	{
		printf("参数不对：%s <src> <dest>\n", argv[0]);
		return 0;
	}
	
	//打开文件
	printf("%s, %s\n", argv[1], argv[2]);
	int src_fd = open(argv[1], O_RDONLY);
	int dest_fd = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, 0644);
	if(src_fd == -1 || dest_fd == -1) //判断文件是否打开失败
	{
		perror("open() failed");
		return 0;
	}
	
	//读写复制
	char buf[100] = {0};
	int r;
	while(1)
	{
		// bzero(buf, sizeof(buf)); //对buf清0
		r = read(src_fd, buf, sizeof(buf));
		if(r == 0)	//读完
			break;
		// write(dest_fd, buf, strlen(buf));
		write(dest_fd, buf, r); //读多少，写多少
	}
	
	//关闭文件
	close(src_fd);
	close(dest_fd);
	
	return  0;
}