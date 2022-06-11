#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int lcd_buf[800*480] = {0}; //液晶屏的缓冲区
	//1、打开液晶屏设备
	int lcd_fd = open("/dev/fb0", O_WRONLY);
	if(lcd_fd == -1)
	{
		perror("open() failed");
		return  -1; // 结束程序
	}
	
	//2、准备颜色数据
	// for(int i=0; i<800*480; i++)	//遍历所有的像素点
	// {
		// lcd_buf[i] = 0x00ff0000; //红色
	// }
	for(int y=0; y<480; y++)  //控制每一行
	{
		for(int x=0; x<800; x++)	//控制每一行的偏移量
		{
			lcd_buf[x+y*800] = 0x00ff0000;
		}
	}
	
	
	//3、把颜色数据写入液晶屏
	write(lcd_fd, lcd_buf, 800*480*4);
	
	//4、关闭液晶屏设备
	close(lcd_fd);
	
	return 0;
}