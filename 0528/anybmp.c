#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>


#define LCD "/dev/fb0"
#define LCD_SIZE 800*480*4
int *FB = NULL;  //定义映射指针
int lcd_fd = -1;   //液晶屏的文件描述符


//给一个像素点上色
void one_pixle(int x, int y, int color)
{
	*(FB+x+y*800) = color;
}

//初始化液晶屏
void lcd_init(void)
{
	//1、打开液晶屏
	lcd_fd = open(LCD, O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open() failed");
		exit(0); // 结束程序
	}
	//2、给液晶屏文件映射一块内存
	FB = mmap(NULL, LCD_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if(FB == MAP_FAILED)
	{
		perror("mmap LCD failed");
		exit(0);
	}
}

//资源释放
void lcd_close(void)
{
	munmap(FB, LCD_SIZE);
	close(lcd_fd);
}

//显示bmp图片
void show_bmp(char *bmpname, int x, int y)
{
	char bmp_info[54] = {0};
	char bmp_buf[800*480*3] = {0};
	
	if(bmpname == NULL)
	{
		printf("没有图片名字路径\n");
		exit(0); 
	}
	//打开bmp文件
	int bmp_fd = open(bmpname, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open bmp failed");
		exit(0); //结束程序
	}
	
	//读取bmp文件头和信息头
	read(bmp_fd, bmp_info, 54);
	int w = bmp_info[18] | bmp_info[19]<<8;
	int h = bmp_info[22] | bmp_info[23]<<8;
	if(x+w > 800  || y+h > 480)
	{
		printf("超出屏幕范围\n");
		exit(0);
	}
	//读取图片数据
	read(bmp_fd, bmp_buf, w*h*3);
	
	//24位转32位
	int color, i = 0, lcd_x, lcd_y;
	for(lcd_y=0; lcd_y<h; lcd_y++)
	{
		 for(lcd_x=0; lcd_x<w; lcd_x++)
		{
			  color = bmp_buf[i+0] | bmp_buf[i+1]<<8 | bmp_buf[i+2]<<16;
			  i+=3;
			  one_pixle(lcd_x+x, h-1-lcd_y+y);    //加上x和y其实映射坐标偏移量
			  // *(FB+lcd_x+x+(h-1-lcd_y+y)*800) = color;
		}
	}
	
	//关闭打开的图片
	close(bmp_fd);
}


int main(int argc, char *argv[])  //  ./any 100 100 1.bmp
{
	// char bmp[3][10] = 
	// {
		// "1.bmp",
		// "2.bmp",
		// "3.bmp"
	// };
	if(argc != 4)
	{
		printf("%s <x> <y> <bmpname>\n", argv[0]);
		exit(0);
	}
	
	//初始化液晶屏
	lcd_init();
	
	//显示bmp图片 atoi()字符串转整形
	show_bmp(argv[3], atoi(argv[1]), atoi(argv[2]));   
	
	// for(int i=0; i<3; i++)
	// {
		// show_bmp(bmp[i], 0, 0);
	// }

	//资源释放
	lcd_close();
	
	return 0;
}