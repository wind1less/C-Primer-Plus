// 编写一个函数，提示用户输入日、月和年。
// 月份可以是月份号、月份名或月份名缩写。
// 然后该程序返回一年中到用户指定日子（包括这一天）的总天数。

// 月份信息整理为结构
// 处理闰年/平年 leap year/common year

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define LEN 10											// 用于存储月份名的字符数组
#define MONTH 12										// 一年内的月数

int get_year();											// 获取年月日输入并检查有效性
int get_month();
int get_day(int month, struct months *);

void eat_line();										// 清空输入缓冲区
int is_leap(int year);									// 计算是否为闰年
int calc_date(struct months *, int month, int day);		// 计算到截止日的天数

struct months {
	char name[LEN];					// 月份名
	char abbreviation[3];			// 月份名的3 个字母缩写
	int  days;						// 该月的天数
	int  sn;						// 月份号
};

struct months common_year[MONTH] = {
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

struct months leap_year[MONTH] = {
	{   "January", "Jau", 31, 1 },
	{  "February", "Feb", 29, 2 },
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
	int year = 0, month = 0, day = 0;
	int days_ct = 0;
	struct months * month_info;

	printf("Enter a year, show you total of days in this year to that day(0 to quit):\n");
	while (year = get_year())
	{
		month_info = is_leap(year) ? leap_year : common_year;
		month = get_month();
		day = get_day(month, month_info);
		days_ct = calc_date(month_info, month, day);
		printf("%d days in %d.1.1 to %d.%d.%d.\n", days_ct, year, month, day);
		printf("Enter next year(0 to quit):\n");
	}

	return 0;
}

int get_year()
{
	// 获取一个年份；检查程序退出条件；清空输入缓冲区
	int year = 0;
	while ((scanf("%d", &year)) != 1)
	{
		printf("Invaid year, try again:\n");
		eat_line();
	}

	return year;
}

int get_month()
{
	// 检测输入是否为月份拼写或月份缩写；将输入转换为数字，检测是否为合法月份；清空输入缓冲区
	char month[LEN];
	int i_month = 0;
	int find = 0;
	printf("Enter a month:\n");
	while (scanf("%s", month))
	{
		while (getchar() != '\n')
			continue;
		if (tolower(*month) == 'q')
			break;
		for (int i = 0; i < MONTH; i++)
		{
			if (strcmp(leap_year[i].name, month) == 0)
			{
				find = leap_year[i].sn;
				break;
			}
			if (strcmp(leap_year[i].abbreviation, month) == 0)
			{
				find = leap_year[i].sn;
				break;
			}
		}
		if (i_month = atoi(month))
		{
			if (i_month <= MONTH && i_month > 0)
				find = i_month;
		}
		if (!find)
			printf("No this month,try again:\n");
		else
			break;
	}
	return find;
}

int get_day(int month, struct months * month_info)
{
	// 获取一个天数；检查天数合法；清空输入缓冲区
	int day = 0;
	int max = (month_info + month)->days;

	printf("Enter a day:\n");
	while ((scanf("%d", &day)) != 1 || day < 0 || day > max)
	{
		if (day < 0 || day > max)
		{
			printf("Month %d haven't Day %d, try again:\n", month, day);
			eat_line();
		}
		else
		{
			printf("Invalid value, try again:\n");
			eat_line();
		}
	}
	return day;
}

void eat_line()
{
    // 清空输入缓冲区
	while (getchar() != '\n')
		continue;
}

int is_leap(int year)
{
    // 能被4 整除的年份为闰年
	return ((year % 4) == 0);
}

int calc_date(struct months * month_info, int month, int day)
{
    // 计算到截止日的总天数
	int days_ct = 0;
	for (int i = 0; i < month - 1; i++)
	{
		days_ct += (month_info + month)->days;
	}
	days_ct += day;

	return days_ct;
}
