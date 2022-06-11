#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>


#define LCD "/dev/fb0"
#define LCD_SIZE 800*480*4
int *FB = NULL;  //����ӳ��ָ��
int lcd_fd = -1;   //Һ�������ļ�������


char bmp[3][10] = 
{
	"1.bmp",
	"2.bmp",
	"3.bmp"
};


//��һ�����ص���ɫ
void one_pixle(int x, int y, int color)
{
	*(FB+x+y*800) = color;
}

//��ʼ��Һ����
void lcd_init(void)
{
	//1����Һ����
	lcd_fd = open(LCD, O_RDWR);
	if(lcd_fd == -1)
	{
		perror("open() failed");
		exit(0); // ��������
	}
	//2����Һ�����ļ�ӳ��һ���ڴ�
	FB = mmap(NULL, LCD_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
	if(FB == MAP_FAILED)
	{
		perror("mmap LCD failed");
		exit(0);
	}
}

//��Դ�ͷ�
void lcd_close(void)
{
	munmap(FB, LCD_SIZE);
	close(lcd_fd);
}

//��ʾbmpͼƬ
//bmpname��ͼƬ����·��
//x������ʾ��x��ʼλ��
//y������ʾ��y��ʼλ��
void show_bmp(char *bmpname, int x, int y)
{
	char bmp_info[54] = {0};
	char bmp_buf[800*480*3] = {0};
	
	if(bmpname == NULL)
	{
		printf("û��ͼƬ����·��\n");
		exit(0); 
	}
	//��bmp�ļ�
	int bmp_fd = open(bmpname, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open bmp failed");
		exit(0); //��������
	}
	
	//��ȡbmp�ļ�ͷ����Ϣͷ
	read(bmp_fd, bmp_info, 54);
	int w = bmp_info[18] | bmp_info[19]<<8;
	int h = bmp_info[22] | bmp_info[23]<<8;
	if(x+w > 800  || y+h > 480)
	{
		printf("������Ļ��Χ\n");
		exit(0);
	}
	//��ȡͼƬ����
	read(bmp_fd, bmp_buf, w*h*3);
	
	//24λת32λ
	int color, i = 0, lcd_x, lcd_y;
	for(lcd_y=0; lcd_y<h; lcd_y++)
	{
		 for(lcd_x=0; lcd_x<w; lcd_x++)
		{
			  color = bmp_buf[i+0] | bmp_buf[i+1]<<8 | bmp_buf[i+2]<<16;
			  i+=3;
			  one_pixle(lcd_x+x, h-1-lcd_y+y, color);    //����x��y��ʵӳ������ƫ����
			  // *(FB+lcd_x+x+(h-1-lcd_y+y)*800) = color;
		}
	}
	
	//�رմ򿪵�ͼƬ
	close(bmp_fd);
}


int main(int argc, char *argv[])  //  ./any 100 100 1.bmp
{
	if(argc != 4)
	{
		printf("%s <x> <y> <bmpname>\n", argv[0]);
		exit(0);
	}
	
	//��ʼ��Һ����
	lcd_init();
	
	while(1)
	{
		for(int i=0; i<3; i++)
		{
			show_bmp(bmp[i], 0, 0);
			// showbmp("1.bmp", );
			sleep(1);
		}
	}
		
	//��Դ�ͷ�
	lcd_close();
	
	return 0;
}