// ��дһ�����򣬽�������int ���͵Ĳ�����һ����ֵ��һ����λ��λ�á�
// ���ָ��λ��λ��Ϊ1���ú������أ����򷵻�0��
// ��һ�������в��Ըú�����

#include <stdio.h>
#include <stdlib.h>

int get_value(int *);
int get_pos(int *);
int find_pos(int, int);

const size = CHAR_BIT * sizeof(int);

int main()
{
	int value;
	int pos;

	while (get_value(&value) && get_pos(&pos))
	{
		printf("%d as binary num, pos %d is %d.\n", value, pos, find_pos(value, pos));
	}

	puts("Done.");

	return 0;
}

int get_value(int * n)
{
	printf("Enter a number(q to quit):\n");
	
	return (scanf("%d", n) == 1);
}

int get_pos(int * n)
{

	printf("Enter a pos(0 ~ %d)\n", size - 1);
	while (scanf("%d", n) != 1 || *n < 0 || *n > size)
		printf("Invalid value, try again:\n");

	return 1;
}

int find_pos(int value, int pos)
{
	int find;

	for (int i = 0; i < pos; i++, value >>= 1)
		;
	find = (01 & value);

	return find;
}





