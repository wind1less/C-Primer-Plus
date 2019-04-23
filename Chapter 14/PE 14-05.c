// 编写一个程序满足下面的要求：
// a. 外部定义一个有两个成员的结构模板name： 一个字符串储存名，一个字符串储存姓。
// b. 外部定义一个有3 个成员的结构模板student：一个name 类型的结构，一个grade 数组储存3 个浮点型分数，一个变量储存3 个分数平均数。
// c. 在main() 函数中声明一个内含CSIZE（CSIZE = 4）个student 类型结构的数组，并初始化这些结构的名字部分。用函数执行g、e、f 和g 中描述的任务。
// d. 以交互的方式获取每个学生的成绩，提示用户输入学生的姓名和分数。把分数储存到grade 数组相应的结构中。可以在main() 函数或其他函数中用循环来完成。
// e. 计算每个结构的平均分，并把计算后的值赋给合适的成员。
// f. 打印每个结构的信息。
// g. 打印班级的平均分，即所有结构的数值成员的平均值。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NLEN 10
#define CSIZE 4
#define SUBJECT 3

void get_grade(struct student *);				// 获取学生姓名，核对成功后获取每个科目的分数
int find_student(char *, char *, struct student *);		// 当返回值为-1 时代表没找到对应的学生；当接收到Q时，返回退出程序的标记
void calc_avg(struct student *);				// 计算每个学生的科目平均分数
void show_info(struct student *);				//  打印结构内的所有信息
void show_class_avg(struct student *);				// 计算班级平均分数并打印
void eat_line();						// 清空输入缓冲区
struct name_model { char firname[NLEN]; char surname[NLEN]; };

struct student {
	struct name_model name;
	float grade[3];
	float avg;
};

int main(void)
{
	struct student arrstd[CSIZE] = {
		{ .name = { "Wang", "Hao" } },
		{ .name = { "Di", "Xiao" } },
		{ .name = { "Hao", "Liu" } },
		{ .name = { "Chao", "Zhao" } }
	};
	get_grade(arrstd);
	calc_avg(arrstd);
	show_info(arrstd);
	show_class_avg(arrstd);

	printf("Done!");

	return 0;
}

void get_grade(struct student *ars)
{
	// 获取学生姓名，核对成功后获取每个科目的分数
	int index = 0;
	char firname[NLEN], surname[NLEN];
	char subject[SUBJECT][10] = { "Language", "Math", "English" };

	printf("Enter a students's name(Q to quit):\n");
	while ((scanf("%s", &firname) == 1) && toupper(firname[0]) != 'Q')
	{
		scanf("%s", &surname);
		eat_line();
		index = find_student(firname, surname, ars);
		if (index == -1)
		{
			printf("No this student, try again(Q to quit):\n");
			continue;
		}
		for (int i = 0; i < SUBJECT; i++)
		{
			printf("Enter his sorce of %s:\n", subject[i]);
			scanf("%f", &ars[index].grade[i]);
			eat_line();
		}
		printf("Enter next student's name(Q to quit):\n");
	}
	eat_line();
}

int find_student(char *firname, char *surname, struct student * ars)
{
	// 当返回值为-1 时代表没找到对应的学生
	// 当接收到Q时，返回退出程序的标记
	int index = -1;
	if (*firname == 'Q')
		index = -2;
	for (int i = 0; i < CSIZE; i++)
	{
		if (strcmp(firname, ars[i].name.firname) == 0 && strcmp(surname, ars[i].name.surname) == 0)
			index = i;
	}
	return index;
}

void calc_avg(struct student * ars)
{
	// 计算每个学生的科目平均分数
	for (int i = 0; i < CSIZE; i++)
	{
		float total = 0;
		for (int i = 0; i < SUBJECT; i++)
			total += ars->grade[i];
		ars->avg = total / SUBJECT;
	}
}

void show_info(struct student * ars)
{
	//  打印结构内的所有信息
	printf("Name	Surname's Score: Language	Math	English\n");
	for (int i = 0; i < CSIZE; i++)
	{
		printf("%-7s %-7s        %10.2f %10.2f %10.2f\n", ars[i].name.firname, ars[i].name.surname, ars[i].grade[0], ars[i].grade[1], ars[i].grade[2]);
	}
}

void show_class_avg(struct student * ars)
{
	// 计算班级平均分数并打印
	float total = 0;
	float avg = 0.0;

	for (int i = 0; i < CSIZE; i++)
		total += ars[i].avg;
	avg = total / CSIZE;
	printf("This class has average score: %.2f.\n", avg);
}

void eat_line()
{
	// 清空输入缓冲区
	while (getchar() != '\n')
		continue;
}
