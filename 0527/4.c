#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(void)
{
	int lcd_buf[800*480] = {0}; //液晶屏的缓冲区
	int color[3] = {0x00ff0000, 0x0000ff00, 0x000000ff};	//红绿蓝
	//1、打开液晶屏设备
	int lcd_fd = open("/dev/fb0", O_WRONLY);
	if(lcd_fd == -1)
	{
		perror("open() failed");
		return  -1; // 结束程序
	}
	
	
	//2、准备颜色数据
	
	int x, y, i=0;
	
	while(1)
	{
		for(y=0; y<480; y++)  //控制每一行
		{
			for(x=0; x<800; x++)	//控制每一行的偏移量
			{
				lcd_buf[x+y*800] = color[i]; 
			}
		}
	
		i++;	//显示下一个颜色
		if(i == 3)
			i = 0;
		
		//3、把颜色数据写入液晶屏
		write(lcd_fd, lcd_buf, 800*480*4);
		lseek(lcd_fd, 0, SEEK_SET);	//把偏移量重定位到文件开头
		sleep(1);		
	}
	
	//4、关闭液晶屏设备
	close(lcd_fd);
	
	return 0;
}