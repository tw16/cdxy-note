#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>   //atoi
#include <linux/input.h>

int mk_ret, mk_fd;

#define TS "/dev/input/event0"	//触摸屏文件
int ts_fd;

int mplayer_init()
{
	//创建有名管道文件
	 if(access("/tmp/mk_video", F_OK))
	 {
		mk_ret = mkfifo("/tmp/mk_video",0777);
		if(mk_ret == -1)
		{
			perror("mkfifo() failed");
			return -1;
		}
	 }
 
	 //打开文件
	mk_fd = open("/tmp/mk_video", O_RDWR);
	if(mk_fd == -1)
	{
		perror("open() /tmp/mk_video failed");
		return -1;
	}
	

	return 0;
}



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

//给管道文件写入命令
void write_cmd(char *cmd)
{
	write(mk_fd, cmd, strlen(cmd));
}


int main(int argc, char **argv)
{
	int x, y;
	ts_init();
	mplayer_init();
	
	system("mplayer -slave -quiet -input file=/tmp/mk_video -geometry 0:0 -zoom -x 800 -y 480 1.avi &");
	
	while(1)
	{
		get_xy(&x, &y);
		if(x>0 && x<400)
		{
			write_cmd("seek -10\n");
		}
		else if(x>400 && x<800)
		{
			write_cmd("seek 10\n");
		}
		
	}	
}