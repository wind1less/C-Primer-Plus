// ��дһ����������ʾ�û������ա��º��ꡣ
// �·ݿ������·ݺš��·������·�����д��
// Ȼ��ó��򷵻�һ���е��û�ָ�����ӣ�������һ�죩����������

// �·���Ϣ����Ϊ�ṹ
// ��������/ƽ�� leap year/common year

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define LEN 10														// ���ڴ洢�·������ַ�����
#define MONTH 12													// һ���ڵ�����

int get_year();														// ��ȡ���������벢�����Ч��
int get_month();
int get_day(int month, struct months *);

void eat_line();													// ������뻺����
int is_leap(int year);											// �����Ƿ�Ϊ����
int calc_date(struct months *, int month, int day);		// ���㵽��ֹ�յ�����

struct months {
	char name[LEN];					// �·���
	char abbreviation[3];			// �·�����3 ����ĸ��д
	int  days;						// ���µ�����
	int  sn;						// �·ݺ�
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
	int year = 0;
	int month = 0;
	int day = 0;
	int days_ct = 0;
	struct months * month_info;

	printf("Enter a year, show you total of days in this year to that day(0 to quit):\n");
	while (year = get_year())
	{
		month_info = is_leap(year) ? leap_year : common_year;
		month = get_month();
		day = get_day(month, month_info);
		days_ct = calc_date(month_info, month, day);
		printf("%d days in this year to %d.%d.%d.\n", days_ct, year, month, day);
		printf("Enter next year(0 to quit):\n");
	}

	return 0;
}

int get_year()
{
	// ��ȡһ����ݣ��������˳�������������뻺����
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
	// ��������Ƿ�Ϊ�·�ƴд���·���д��������ת��Ϊ���֣�����Ƿ�Ϊ�Ϸ��·ݣ�������뻺����
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
	// ��ȡһ����������������Ϸ���������뻺����
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
	while (getchar() != '\n')
		continue;
}

int is_leap(int year)
{
	return ((year % 4) == 0);
}

int calc_date(struct months * month_info, int month, int day)
{
	int days_ct = 0;
	for (int i = 0; i < month - 1; i++)
	{
		days_ct += (month_info + month)->days;
	}
	days_ct += day;

	return days_ct;
}
