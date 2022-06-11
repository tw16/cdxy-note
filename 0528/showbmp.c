#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LCD "/dev/fb0"

//传一个图片名，显示指定图片
int main(int argc, char *argv[])   //   ./showbmp 1.bmp
{
	int lcd_fd, bmp_fd;
	int lcd_buf[800*480] = {0}; // LCD缓冲区
	char bmp_buf[800*480*3] = {0};  //BMP图片的缓冲区
	
	
	if(argc != 2)	//判断参数个数是否正确
	{
		printf("%s <xxx.bmp>\n", argv[0]);
		return -1;
	}
	
	//打开液晶屏和图片
	lcd_fd = open(LCD, O_WRONLY);
	if(lcd_fd == -1)
	{
		perror("open lcd failed");
		return -1;
	}
	
	bmp_fd = open(argv[1], O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open bmp failed");
		return -1;
	}
	
	//读取图片颜色数据
	//把图片的文件头和信息偏移
	// lseek(bmp_fd, 54, SEEK_SET);
	//读出信息头获取图片像素宽和像素高
	char bmp_info[54] = {0};
	read(bmp_fd, bmp_info, 54);
	
	int w = bmp_info[18] | bmp_info[19]<<8;
	int h = bmp_info[22] | bmp_info[23]<<8;
	printf("w = %d, h = %d\n", w, h);
	
	//读图片的颜色数据
	read(bmp_fd, bmp_buf, 800*480*3);
	
	int i = 0;
	int x, y;
	//24位转32位， 颜色重排
	for(y=0; y<480; y++)
	{
		 for(x=0; x<800; x++)
		{
			  lcd_buf[x+(479-y)*800] = bmp_buf[i+0] | bmp_buf[i+1]<<8 | bmp_buf[i+2]<<16;
			  i+=3;
		}
	}
	
	
	//把图片颜色数据写入液晶屏
	write(lcd_fd, lcd_buf, 800*480*4);
	
	
	//关闭液晶屏和图片
	close(lcd_fd);
	close(bmp_fd);
	
	
	return 0;
}
