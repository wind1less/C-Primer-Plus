// �޸ĳ����嵥14.2 �е�ͼ��Ŀ¼����ʹ�䰴������ͼ���˳�����ͼ�����Ϣ��
// Ȼ���ձ�����ĸ���������ͼ�����Ϣ������ռ۸���������ͼ�����Ϣ��

#include <stdio.h>
#include <string.h>

#define MAXTITL 40			// ��������
#define MAXAUTL 40			// ���߳���
#define MAXBKS 100			// �鼮���������

char * s_gets(char * st, int n);
void  output_order(struct book library[MAXBKS], int count);		// ��������˳�����
void  output_fl(struct book library[MAXBKS], int count);			// ��������ĸ�������
void  output_value(struct book library[MAXBKS], int count);		// ���ռ۸��������

struct book { char title[MAXTITL]; char author[MAXAUTL]; float value; };

int main(void)
{
	struct book library[MAXBKS];
	int count = 0;
	int index = 0;

	printf("Please enter the book title.\n");
	printf("Press [enter] at the start of a line to stop.\n");
	while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
	{
		printf("Now enter the author.\n");
		s_gets(library[count].author, MAXAUTL);
		printf("Now enter the value.\n");
		scanf("%f", &library[count++].value);
		while (getchar() != '\n')
			continue;
		if (count < MAXBKS)
			printf("Enter the next title.\n");
	}

	if (count > 0)
	{
		printf("\nHere is the list of your books(sort by order):\n");
		output_order(library, count);
		printf("\nHere is the list of your books(sort by first letter):\n");
		output_fl(library, count);
		printf("\nHere is the list of your books(sort by value):\n");
		output_value(library, count);
	}
	else
		printf("No books? Too bad.\n");

	return 0;
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}

	return ret_val;
}

void output_order(struct book library[MAXBKS], int count)
{
	for(int i = 0; i < count; i++)
		printf("< %10s > by ��%10s��: $ %.2f\n", library[i].title, library[i].author, library[i].value);
}

void output_fl(struct book library[MAXBKS], int count)
{
	struct book temp;

	for (int m = 0; m < count; m++)
	{
		for (int n = m; n < count; n++)
		{
			if (library[m].title[0] > library[n].title[0])
			{
				temp = library[m];
				library[m] = library[n];
				library[n] = temp;
			}
		}
	}
	for (int i = 0; i < count; i++)
		printf("< %10s > by ��%10s��: $ %.2f\n", library[i].title, library[i].author, library[i].value);
}

void output_value(struct book library[MAXBKS], int count)
{
	struct book temp;

	for (int m = 0; m < count; m++)
	{
		for (int n = m; n < count; n++)
		{
			if (library[m].value > library[n].value)
			{
				temp = library[m];
				library[m] = library[n];
				library[n] = temp;
			}
		}
	}
	for (int i = 0; i < count; i++)
		printf("< %10s > by ��%10s��: $ %.2f\n", library[i].title, library[i].author, library[i].value);
}



//
//#include <stdio.h>
//#include <string.h>
//
//char * s_gets(char * st, int n);
//
//#define MAXTITL 40			// ��������
//#define MAXAUTL 40			// ���߳���
//#define MAXBKS 100			// �鼮���������
//
//struct book { char title[MAXTITL]; char author[MAXAUTL]; float value; };
//
//int main(void)
//{
//	struct book library[MAXBKS];
//	int count = 0;
//	int index = 0;
//
//	printf("Please enter the book title.\n");
//	printf("Press [enter] at the start of a line to stop.\n");
//	while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL && library[count].title[0] != '\0')
//	{
//		printf("Now enter the author.\n");
//		s_gets(library[count].author, MAXAUTL);
//		printf("Now enter the value.\n");
//		scanf("%f", &library[count++].value);
//		while (getchar() != '\n')
//			continue;
//		if (count < MAXBKS)
//			printf("Enter the next title.\n");
//	}
//
//	if (count > 0)
//	{
//		printf("\nHere is the list of your books:\n");
//		for (index = 0; index < count; index++)
//			printf("< %s > by ��%s��: $%.2f\n", library[index].title, library[index].author, library[index].value);
//	}
//	else
//		printf("No books? Too bad.\n");
//
//	return 0;
//}
//
//char * s_gets(char * st, int n)
//{
//	char * ret_val;
//	char * find;
//
//	ret_val = fgets(st, n, stdin);
//	if (ret_val)
//	{
//		find = strchr(st, '\n');
//		if (find)
//			*find = '\0';
//		else
//			while (getchar() != '\n')
//				continue;
//	}
//
//	return ret_val;
//}