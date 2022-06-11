#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*note: 
	PAJ7620U2-手势探测驱动驱动文件：/dev/IIC_drv
	接口函数：open   read   close
	通信协议：用read函数每次只能读取1个字节并且100ms后会后返回值
				返回值--> -1:没有探测到手势    1-9：分别对应9中手势
				
	
	接线说明： 模块J10<--连接--->GEC6818J10
			     VCC			PIN1
				 GND			PIN19/20
				 SCL			PIN15
				 SDA			PIN17
				 

*/
int main(void)
{
	int fd;
	char tmp;
	fd = open("/dev/IIC_drv", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;	
	}
	
	while(1)
	{
		read(fd,&tmp,1);
		
		if(tmp>=1 && tmp<=9)//1<=tmp<=9,这种是数学的写法，在计算机里面逻辑不一样
		{
			printf("%x\n",tmp);
			switch(tmp)
			{
				
				case 1:printf("test-Up\n");break;
				case 2:printf("test-Down\n");break;
				case 3:printf("test-Left\n");break;
				case 4:printf("test-Right\n");break;
				case 5:printf("test-Forward\n");break;
				case 6:printf("test-Backward\n");break;
				case 7:printf("test-Clockwise\n");break;
				case 8:printf("test-AntiClockwise\n");break;
				case 9:printf("test-Wave\n");break;
				default:printf("test-fail\n");break;
			}
			
		}
	}
	
	
	close(fd);
	return 0;
}