#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>

#define TS "/dev/input/event0"	//触摸屏文件
int ts_fd = -1;
int i = 0;

void ts_init(void)
{
	//1， 打开触摸屏
	ts_fd = open(TS, O_RDONLY);	//以只读的方式打开触摸屏
	if(ts_fd == -1)	//判断是否打开成功
	{
		perror("open touch failed");
		exit(0);
	}
}


void ts_close(void)
{
	
	//关闭触摸屏文件
	close(ts_fd);
}

//获取坐标
void  get_xy(int *x, int *y)
{
	//读触摸屏文件，每次读一个结构体
	struct input_event buf;	//输入事件结构体变量
	while(1)
	{
		read(ts_fd, &buf, sizeof(buf));		//读取输入设备的数据变化存到结构体变量buf里面
		printf("i = %d\n", i++);
		if(buf.type == EV_ABS)	//读到绝对事件
		{
			if(buf.code == ABS_X)	//读到x轴事件
			{
				// x = buf.value;	//读到x坐标值
				*x = buf.value*800/1024;	//读到x坐标值
			}
			else if(buf.code == ABS_Y)	//y轴事件
			{
				// y = buf.value;	//读到y坐标值
				*y = buf.value*480/600;	//读到y坐标值
			}
		}
		if(buf.type == EV_KEY && buf.code == BTN_TOUCH)	//按压事件（黑边框和蓝边框都可以以此判断）
		{
			if(buf.value == 0)	//0表示默认值，没有按下
			{
				printf("松开\n");
				break;
			}
			else
			{
				printf("按下\n");
			}
		}
		
		printf("get_xy-----(%d, %d)\n", *x, *y);	//打印获取到的坐标	
	}
	
}


int main(void)
{
	int x, y;
	
	//初始化触摸屏
	ts_init();
	
	while(1)
	{
		get_xy(&x, &y);
		printf("main-----(%d, %d)\n", x, y);	//打印获取到的坐标
		if(x>300 && x<500 && y>200 && y<300)
			printf("这是屏幕中心\n");
		else
			printf("屏幕的外围\n");
	}
	
	//关闭触摸屏
	ts_close();
	
	return 0;
}