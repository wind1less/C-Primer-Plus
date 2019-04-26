// ��дһ������ͨ�������в�����ȡ�����������ַ��������������������ַ���ʹ��~�������&�������|�������^�����
// ���Զ������ַ�����ʽ��ӡ�����

#include <stdio.h>
#include <stdlib.h>

int bstr_to_dec(const char * str);				// �������ַ���ת��Ϊʮ������ֵ
char * itobs(int, char *);						// ʮ������ֵת��Ϊ�������ַ���

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
	// �������ַ���ת��Ϊʮ������ֵ
	int val = 0;

	while (*str != '\0')
		val = 2 * val + (*str++ - '0');
	return val;
}

char * itobs(int n, char * ps)
{
	// ʮ������ֵת��Ϊ�������ַ���
	int i;
	static int size = 8 * sizeof(int);

	for (i = size - 1; i >= 0; i--, n >>= 1)
		ps[i] = (01 & n) + '0';
	ps[size] = '\0';

	return ps;
}