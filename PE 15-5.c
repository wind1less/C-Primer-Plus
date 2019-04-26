// ��дһ����������һ��unsigned int ����ֵ�е�����λ������תָ��������λ��
// ���磬rotate_1(x, 4)��x ������λ�����ƶ�4 ��λ�ã����Ҵ�������Ƴ���λ�����³������Ҷˡ�
// Ҳ����˵���Ѹ߽�λ�Ƴ���λ����ͽ�λ����һ�������в��Ըú�����
// ��չ��������ת�ķ���


#include <stdio.h>
#include <limits.h>

unsigned int rotate_l(unsigned int, unsigned int);
char * itobs(int, char *);

int main(void)
{
	unsigned int val;
	unsigned int rot;
	unsigned int places;

	char bstr1[CHAR_BIT * sizeof(int) + 1];
	char bstr2[CHAR_BIT * sizeof(int) + 1];

	printf("Enter an integer (q to quit): ");
	while (scanf("%ud", &val))
	{
		printf("Enter the number of bits to be rotated:\n");
		if (scanf("%ul", &places) != 1)
			break;
		rot = rotate_l(val, places);
		itobs(val, bstr1);
		itobs(rot, bstr2);
		printf("%u rotated is %u.\n", val, rot);
		printf("%s rotated is %s.\n", bstr1, bstr2);
		printf("Next value:");
	}

	puts("Done");
	return 0;
}

unsigned int rotate_l(unsigned int n, unsigned int b)
{
	static const int size = CHAR_BIT * sizeof(int);
	unsigned int overflow;

	b %= size;
	overflow = n >> (size - b);
	return (n << b) | overflow;
}

char * itobs(int n, char * ps)
{
	int i;
	const static int size = CHAR_BIT * sizeof(int);

	for (i = size - 1; i >= 0; i--, n >>= 1)
		ps[i] = (01 & n) + '0';
	ps[size] = '\0';

	return ps;
}




/*--------------------------------------
����ʹ�ò����ַ�������ƴ�ӵķ�ʽ�����λ
---------------------------------------*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//#include <string.h>
//
//void eat_line();
//void show_binary(unsigned int, char *);
//void format_bin(char * st);
//void rotate(char * st, int direct, int dist);
//
//size = CHAR_BIT * sizeof(unsigned int);
//
//int main()
//{
//	char * binarys;
//	binarys = malloc(size * sizeof(char));
//	unsigned int num = 0;
//	int direct = 1;	// 0 �������ƣ�1 �������ơ�
//	int dist = 0;
//
//	printf("Enter a number(q to quit):\n");
//	while (scanf("%d", &num) == 1)
//	{
//		eat_line();
//		//printf("Sea a direction to move binary( 1 = <<  2 = >> ):\n");
//		//scanf("%d", &direct);
//		//eat_line();
//		printf("How many distance do you want to move:\n");
//		scanf("%d", &dist);
//		eat_line();
//		show_binary(num, binarys);
//		puts("After the ratetion:");
//		rotate(binarys, direct, dist % size);
//
//		printf("\nEnter next num(q to quit):\n");
//	}
//
//	puts("Done.");
////	free(binarys);			Ϊ�δ˴��ᱨ�ڴ���󣿣���
//
//	return 0;
//}
//
//void eat_line()
//{
//	// ����scanf() ʹ�ã�������뻺����
//	while (getchar() != '\n')
//		continue;
//}
//
//void show_binary(unsigned int num, char * st)
//{
//	for (int i = size - 1; i >= 0; i--, num >>= 1)
//		st[i] = (01 & num) + '0';
//	st[size] = '\0';
//
//	format_bin(st);
//}
//
//void rotate(char * st, int direct, int dist)
//{
//	char temp;
//	char * forwards;
//	char * backwards;
//	if (dist)
//	{
//
//
//		forwards = malloc(size * sizeof(int));
//		backwards = malloc(size * sizeof(int));
//		if (direct)
//		{
//			temp = st[size - dist - 1];
//			strcpy(backwards, &st[size - dist]);
//			st[size - dist - 1] = '\0';
//			strcpy(forwards, st);
//		}
//		else
//		{
//			temp = st[dist - 1];
//			strcpy(backwards, &st[dist]);
//			st[dist] = '\0';
//			strcpy(forwards, st);
//		}
//
//		strcat(backwards, forwards);
//		backwards[size - 1] = temp;
//		backwards[size] = '\0';
//		format_bin(backwards);
//
//		free(forwards);
//		free(backwards);
//	}
//	else
//		format_bin(st);
//}
//
//void format_bin(char * st)
//{
//	for (int i = 0; i < size; i++)
//	{
//		putc(st[i], stdout);
//		if (i && ((i + 1) % 4 == 0))
//			printf(" ");
//	}
//	puts("");
//}