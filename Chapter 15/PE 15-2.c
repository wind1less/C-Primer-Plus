// 编写一个程序，通过命令行参数读取两个二进制字符串，对这两个二进制字符串使用~运算符、&运算符、|运算符和^运算符
// 并以二进制字符串形式打印结果。

#include <stdio.h>
#include <stdlib.h>

int bstr_to_dec(const char * str);				// 二进制字符串转换为十进制数值
char * itobs(int, char *);						// 十进制数值转换为二进制字符串

int main()
{
	int v1;
	int v2;
	char bstr[8 * sizeof(int) + 1];
	char argv[3][32];
	//if (argc != 3)
	//{ int argc, char * argv[]
	//	fprintf(stderr, "Usage: %s binarynum1 binarynum2\n", argv[0]);
	//	exit(EXIT_FAILURE);
	//}
	printf("Enter first parament:\n");
	scanf("%s", argv[1]);
	printf("Enter second parament:\n");
	scanf("%s", argv[2]);

	v1 = bstr_to_dec(argv[1]);
	v2 = bstr_to_dec(argv[2]);
	int temp;
	temp = ~v1;
	printf("~%s = %s\n", argv[1], itobs(~v1, bstr));
	printf("~%s = %s\n", argv[2], itobs(~v2, bstr));
	printf("%s & %s = %s\n", argv[1], argv[2], itobs(v1 & v2, bstr));
	printf("%s | %s = %s\n", argv[1], argv[2], itobs(v1 | v2, bstr));
	printf("%s ^ %s = %s\n", argv[1], argv[2], itobs(v1 ^ v2, bstr));

	puts("Done");
	return 0;
}

int bstr_to_dec(const char * str)
{
	// 二进制字符串转换为十进制数值
	int val = 0;

	while (*str != '\0')
		val = 2 * val + (*str++ - '0');
	return val;
}

char * itobs(int n, char * ps)
{
	// 十进制数值转换为二进制字符串
	int i;
	static int size = 8 * sizeof(int);

	for (i = size - 1; i >= 0; i--, n >>= 1)
		ps[i] = (01 & n) + '0';
	ps[size] = '\0';

	return ps;
}