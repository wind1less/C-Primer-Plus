// 编写一个函数，把二进制字符串转换为一个数值。例如，有下面的语句：
// char * pbin = "01001001";
// 那么把pbin 作为参数传递给该函数后，它应该返回一个int 类型的值73。

#include <stdio.h>
#include <string.h>
#include <math.h>

int invert_to_num(char *);

int main(void)
{
	char * num[32];

	printf("Enter a binary number as string:\n");
	scanf("%s", num);
	printf("Your num is %d.", invert_to_num(num));

	return 0;
}

int invert_to_num(char * st)
{
	// 倒序读取字符串中的字符，-'0' 得到对应数字，乘以所在位置的十进制值，累加得到结果
	int num = 0;
	int length = strlen(st);

	for (int i = 0; i < length; i++)
		num += ((int)(st[length - 1 - i] - '0') * (int)pow(2, i));

	return num;
}