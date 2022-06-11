#if 0
lseek()：重新定位文件描述符
off_t lseek(int fd, off_t offset, int whence);
头文件： 
#include <sys/types.h>
#include <unistd.h>
参数含义：
fd：文件描述符
offset:偏移量（字节）
whence:基准点
	SEEK_SET：从文件头开始偏移
    SEEK_CUR：从当前位置偏移
	SEEK_END：从文件摩围偏移
#endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd = open("1.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("open failed");
		return 0;
	}
	
	char buf[10] = {0};
	lseek(fd, 6, SEEK_SET);
	read(fd, buf, sizeof(buf));
	printf("buf = %s\n", buf);
	
	int len = lseek(fd, 0, SEEK_END);
	printf("len = %d\n", len);
	
	close(fd);
	
	return 0;
}