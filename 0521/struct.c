#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student
{
	int num;
	int age;
	char name[20];
};

// struct student 等同于char int float
// int a;
// char ch;
// struct student c;
// struct student *p;
// struct student arr[10];


int main(void)
{
	struct student zhangsan = {1, 20, "zhangsan"}; 
	 //指定成员赋值
	struct student wangwu = {.age=20,.name="wangwu"};
	struct student lisi = zhangsan;
	lisi.num = 2;
	strcpy(lisi.name, "lisi");
	
	struct student *p = malloc(sizeof(struct student)); //分配空间
	p->num = 3;
	p->age = 40;
	strcpy(p->name, "zhaoliu");
	
		
	//普通变量的成员访问
	printf("num=%d, age=%d, name=%s\n", zhangsan.num, zhangsan.age, zhangsan.name);
	printf("num=%d, age=%d, name=%s\n", lisi.num, lisi.age, lisi.name);
	
	printf("p->num=%d, p->age=%d\n", p->num, p->age);
	
	return 0;
}
