#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>

#define TS "/dev/input/event0"	//触摸屏文件


int main(void)
{
	int x, y;
	//1， 打开触摸屏
	int ts_fd = open(TS, O_RDONLY);	//以只读的方式打开触摸屏
	if(ts_fd == -1)	//判断是否打开成功
	{
		perror("open touch failed");
		return 0;
	}
	//2，读触摸屏文件，每次读一个结构体
	struct input_event buf;	//输入事件结构体变量
	while(1)
	{
		read(ts_fd, &buf, sizeof(buf));		//读取输入设备的数据变化存到结构体变量buf里面
		if(buf.type == EV_ABS)	//读到绝对事件
		{
			if(buf.code == ABS_X)	//读到x轴事件
			{
				// x = buf.value;	//读到x坐标值
				x = buf.value*800/1024;	//读到x坐标值
			}
			else if(buf.code == ABS_Y)	//y轴事件
			{
				// y = buf.value;	//读到y坐标值
				y = buf.value*480/600;	//读到y坐标值
			}
		}
		if(buf.type == EV_KEY && buf.code == BTN_TOUCH)	//按压事件（黑边框和蓝边框都可以以此判断）
		{
			if(buf.value == 0)	//0表示默认值，没有按下
			{
				printf("松开\n");
			}
			else
			{
				printf("按下\n");
			}
		}
		
		printf("(%d, %d)\n", x, y);	//打印获取到的坐标
		
		if(x > 400)		//判断点击屏幕的右边还是左边（黑边框的板子要改成612）
			printf("右边\n");
		else
			printf("左边\n");
		
	}
	
	//关闭触摸屏文件
	close(ts_fd);
	
	return 0;
}