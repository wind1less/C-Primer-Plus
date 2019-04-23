// 编写一个程序，创建一个有两个成员的结构模板：
// a. 第1 个成员是社会保险号，
// 第2 个成员是一个有3 个成员的结构，第1 个成员代表名，第2 个成员代表中间名，第3 个成员代表姓。
// 创建并初始化一个内含5 个该类型结构的数组。
// 该程序以下面的格式打印数据：   Dribble, Flossie M. -- 302039823
// 如果有中间名，只打印它的第1 个字母，后面加一个点（.）；
// 如果没有中间名，则不用打印点。
// 编写一个程序进行打印，把结构数组传递给这个函数。
// b. 修改a 部分，传递结构的值而不是结构的地址。

#include <stdio.h>
#include <string.h>

#define SLEN 6
#define MEN  5

struct all_name { char firname[SLEN]; char midname[SLEN]; char surname[SLEN]; };

struct persion_info {
	long long society_security;
	struct all_name name;
};

void ashow_info(struct persion_info * info);				// 方式a. 解析结构数组内的信息并按格式打印
void bshow_info(struct persion_info info[MEN]);				// 方式b. 解析结构数组内的信息并按格式打印

int main(void)
{
	struct persion_info zyzn[MEN] =
	{
 		{ 41272419970803, { "Wang", "Xiao", "Hao" }},
		{ 41272419950603, { "Xiao", "Da", "Di" }},
		{ 41272419960330, { "Liu", " ", "Hao" }},
		{ 41272419750224, { "Zhou", "Da", "Chao" } },
		{ 41148419850319, { "Zheng", "Xiao", "Gang" }}
	};
	printf("Method A: ----------\n");
	ashow_info(zyzn);
	printf("\nMethod B: ----------\n");
	bshow_info(zyzn);
	printf("\nBye!\n");

	return 0;
}

void ashow_info(struct persion_info * info)
{
	// 方式a. 解析结构数组内的信息并按格式打印
	for (int i = 0; i < MEN; i++)
	{
		printf("%*s %*s ", SLEN, (info + i)->name.surname, SLEN, (info + i)->name.firname);
		if ((info + i)->name.midname[0] != ' ')
			printf("%c. ", (info + i)->name.midname[0]);
		else
			printf("   ");
		printf(" -- %lld\n", (info + i)->society_security);
	}
}

void bshow_info(struct persion_info info[MEN])
{
	// 方式b. 解析结构数组内的信息并按格式打印
	for (int i = 0; i < MEN; i++)
	{
		printf("%*s %*s ", SLEN, info[i].name.surname, SLEN, info[i].name.firname);
		if (info[i].name.midname[0] != ' ')
			printf("%c. ", info[i].name.midname[0]);
		else
			printf("   ");
		printf(" -- %lld\n", info[i].society_security);
	}
} 
