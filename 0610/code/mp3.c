#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	char mp3[3][10] = 
	{
		"1.mp3",
		"2.mp3",
		"3.mp3"
	};
	
	char cmd[30];
	// printf("madplay %s &", mp3[0]);  //madplay 1.mp3 &
	
	// int sprintf(char *str, const char *format, ...);  
	sprintf(cmd, "madplay %s &", mp3[0]);
	system(cmd);
	
	//播放音乐
	system("madplay faded.mp3 &");
	sleep(6);
	
	//暂停
	system("killall -19 madplay");
	sleep(3);
	
	//继续
	system("killall -18 madplay");
	sleep(6);
	
	//关闭
	system("killall -9 madplay");
	
	printf("音乐结束\n");
	return 0;
}