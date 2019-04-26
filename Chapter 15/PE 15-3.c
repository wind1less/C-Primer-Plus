// ��дһ������������һ��int ���͵Ĳ����������ظò����д�λ��������
// ��һ�������в��Ըú�����

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int show_binary(int num);

int main()
{
	int num;
	int count;
	printf("Enter a number:(q to quit)\n");
	while (scanf("%d", &num) == 1)
	{
		count = show_binary(num);
		printf("%d has %d open bits.\n", num, count);
		printf("\nEnter next number(q to quit):\n");
	}

	printf("Done.");

	return 0;
}

int show_binary(int num)
{
	const static size = CHAR_BIT * sizeof(int);
	int * bit;
	int count = 0;
	bit = malloc(size * sizeof(int));
	for (int i = size - 1; i >= 0; i--, num >>= 1)
	{
		bit[i] = (01 & num);
	}
	for (int i = 0; i < size; i++)
	{
		if (bit[i])
		{
			printf("|");
			count++;
		}
		else
			printf("-");
	}

	puts("");

	return count;
}