// ��дһ���������Ѷ������ַ���ת��Ϊһ����ֵ�����磬���������䣺
// char * pbin = "01001001";
// ��ô��pbin ��Ϊ�������ݸ��ú�������Ӧ�÷���һ��int ���͵�ֵ73��

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
	// �����ȡ�ַ����е��ַ���-'0' �õ���Ӧ���֣���������λ�õ�ʮ����ֵ���ۼӵõ����
	int num = 0;
	int length = strlen(st);

	for (int i = 0; i < length; i++)
		num += ((int)(st[length - 1 - i] - '0') * (int)pow(2, i));

	return num;
}