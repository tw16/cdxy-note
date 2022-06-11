#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define LCD_SIZE 800*480*4
int *FB = NULL;  //定义映射指针

//给一个像素点上色
void one_pixle(int x, int y, int color)
{
	*(FB+x+y*800) = color;
}


int main(void)
{
	int lcd_buf[800*480] = {0}; //液晶屏的缓冲区
	//1、打开液晶屏设备
	int lcd_fd = open("/dev/fb0", O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open() failed");
		return  -1; // 结束程序
	}
	
	//2、给液晶屏文件映射一块内存
	FB = mmap(NULL, LCD_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if(FB == MAP_FAILED)
	{
		perror("mmap LCD failed");
		return -1;
	}
	
	for(int y=0; y<480; y++)  //控制每一行
	{
		for(int x=0; x<800; x++)	//控制每一行的偏移量
		{
			one_pixle(x, y, 0x00ff0000);
		}
	}
	
	// int color = 0x00ff0000;
	// memcpy(FB, &color, LCD_SIZE);

	//4、释放资源
	munmap(FB, LCD_SIZE);
	close(lcd_fd);
	
	return 0;
}