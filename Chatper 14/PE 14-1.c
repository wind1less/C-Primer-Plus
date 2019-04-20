////REVIEW 14.5
//#include <stdio.h>
//#include <ctype.h>
//
//#define LEN 10					// 用于存储月份名
//int days_in_month(int month);		// 接受月份并返回一年中到该月为止的总天数
//int get_month();					// 获取一个正确的月份输入
//
//struct months {
//	char name[LEN];					// 月份名
//	char abbreviation[3];			// 月份名的3 个字母缩写
//	int  days;						// 该月的天数
//	int sn;							// 月份号
//};
//
//struct months month_info_2019[12] = {
//	{   "January", "Jau", 31, 1 },
//	{  "February", "Feb", 28, 2 },
//	{     "March", "Mar", 31, 3 },
//	{     "April", "Apr", 30, 4 },
//	{       "May", "May", 31, 5 },
//	{      "June", "Jun", 30, 6 },
//	{      "July", "Jul", 31, 7 },
//	{    "August", "Aug", 31, 8 },
//	{ "September", "Sep", 30, 9 },
//	{   "October", "Oct", 31, 10 },
//	{  "November", "Nov", 30, 11 },
//	{  "December", "Dec", 31, 12 },
//};
//
//int main(void)
//{
//	int month = 0;
//	int days = 0;
//	printf("Enter a month, show you total of days in a year to that month(0 to quit):\n");
//	while (month = get_month())
//	{
//		days = days_in_month(month);
//		printf("%d days in this year to %s.\n", days, month_info_2019[month - 1].name);
//		printf("Enter next month(q to quit):\n");
//	}
//
//	return 0;
//}
//
//int days_in_month(int month)
//{
//	// 接受月份并返回一年中到该月为止的总天数
//	int days_count = 0;
//	for (int i = 0; i < month; i++)
//		days_count += month_info_2019[i].days;
//
//	return days_count;
//}
//
//int get_month()
//{
//	// 获取一个正确的月份输入
//	int month = 0;
//	while (scanf("%d", &month) != 1 || month < 0 || month > 12)
//	{
//			printf("Invalid month, try again(0 to quit):\n");
//			while (getchar() != '\n')
//				continue;
//			continue;
//	}
//	return month;
//}

// 重新编写复习题5，用月份名的拼写代替月份号（别忘了使用strcpm()）。
// 在一个简单的程序中测试该程序。

#include <stdio.h>
#include <ctype.h>

#define LEN 10						// 用于存储月份名
#define MONTH 12					// 一年内的月数

int days_in_month(int month);		// 接受月份并返回一年中到该月为止的总天数
int get_month();					// 获取一个正确的月份拼写输入
int find_month(char *);				// 使用月份拼写寻找月份号

struct months {
	char name[LEN];					// 月份名
	char abbreviation[3];			// 月份名的3 个字母缩写
	int  days;						// 该月的天数
	int  sn;						// 月份号
};

struct months month_info_2019[MONTH] = {
	{   "January", "Jau", 31, 1 },
	{  "February", "Feb", 28, 2 },
	{     "March", "Mar", 31, 3 },
	{     "April", "Apr", 30, 4 },
	{       "May", "May", 31, 5 },
	{      "June", "Jun", 30, 6 },
	{      "July", "Jul", 31, 7 },
	{    "August", "Aug", 31, 8 },
	{ "September", "Sep", 30, 9 },
	{   "October", "Oct", 31, 10 },
	{  "November", "Nov", 30, 11 },
	{  "December", "Dec", 31, 12 },
};

int main(void)
{
	int month = 0;
	int days = 0;
	printf("Enter a month, show you total of days in a year to that month(q to quit):\n");
	while (month = get_month())
	{
		days = days_in_month(month);
		printf("%d days in this year to %s.\n", days, month_info_2019[month - 1].name);
		printf("Enter next month(q to quit):\n");
	}

	return 0;
}

int days_in_month(int month)
{
	// 接受月份并返回一年中到该月为止的总天数
	int days_count = 0;
	for (int i = 0; i < month; i++)
		days_count += month_info_2019[i].days;

	return days_count;
}

int get_month()
{
	// 获取一个正确的月份拼写输入
	// 使用月份拼写寻找月份号
	// 检测退出条件‘q’
	// 清空输入缓冲区
	char month[LEN];
	int find = 0;
	while (scanf("%s", month))
	{
		while (getchar() != '\n')
			continue;
		if (tolower(*month) == 'q')
			break;
		for (int i = 0; i < MONTH; i++)
		{
			if (strcmp(month_info_2019[i].name, month) == 0)
			{
				find = month_info_2019[i].sn;
				break;
			}
		}
		if (!find)
			printf("No this month,try again:\n");
		else
			break;
	}
	return find;
}
