// ��дһ���������������Ҫ��
// a. �ⲿ����һ����������Ա�Ľṹģ��name�� һ���ַ�����������һ���ַ��������ա�
// b. �ⲿ����һ����3 ����Ա�Ľṹģ��student��һ��name ���͵Ľṹ��һ��grade ���鴢��3 �������ͷ�����һ����������3 ������ƽ������
// c. ��main() ����������һ���ں�CSIZE��CSIZE = 4����student ���ͽṹ�����飬����ʼ����Щ�ṹ�����ֲ��֡��ú���ִ��g��e��f ��g ������������
// d. �Խ����ķ�ʽ��ȡÿ��ѧ���ĳɼ�����ʾ�û�����ѧ���������ͷ������ѷ������浽grade ������Ӧ�Ľṹ�С�������main() ������������������ѭ������ɡ�
// e. ����ÿ���ṹ��ƽ���֣����Ѽ�����ֵ�������ʵĳ�Ա��
// f. ��ӡÿ���ṹ����Ϣ��
// g. ��ӡ�༶��ƽ���֣������нṹ����ֵ��Ա��ƽ��ֵ��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NLEN 10
#define CSIZE 4
#define SUBJECT 3

void get_grade(struct student *);						// ��ȡѧ���������˶Գɹ����ȡÿ����Ŀ�ķ���
int find_student(char *, char *, struct student *);		// ������ֵΪ-1 ʱ����û�ҵ���Ӧ��ѧ���������յ�Qʱ�������˳�����ı��
void calc_avg(struct student *);						// ����ÿ��ѧ���Ŀ�Ŀƽ������
void show_info(struct student *);						//  ��ӡ�ṹ�ڵ�������Ϣ
void show_class_avg(struct student *);					// ����༶ƽ����������ӡ
void eat_line();										// ������뻺����
struct name_model { char firname[NLEN]; char surname[NLEN]; };

struct student {
	struct name_model name;
	float grade[3];
	float avg;
};

int main(void)
{
	struct student arrstd[CSIZE] = {
		{ .name = { "Wang", "Hao" } },
		{ .name = { "Di", "Xiao" } },
		{ .name = { "Hao", "Liu" } },
		{ .name = { "Chao", "Zhao" } }
	};
	get_grade(arrstd);
	calc_avg(arrstd);
	show_info(arrstd);
	show_class_avg(arrstd);

	printf("Done!");

	return 0;
}

void get_grade(struct student *ars)
{
	// ��ȡѧ���������˶Գɹ����ȡÿ����Ŀ�ķ���
	int index = 0;
	char firname[NLEN], surname[NLEN];
	char subject[SUBJECT][10] = { "Language", "Math", "English" };

	printf("Enter a students's name(Q to quit):\n");
	while ((scanf("%s", &firname) == 1) && toupper(firname[0]) != 'Q')
	{
		scanf("%s", &surname);
		eat_line();
		index = find_student(firname, surname, ars);
		if (index == -1)
		{
			printf("No this student, try again(Q to quit):\n");
			continue;
		}
		for (int i = 0; i < SUBJECT; i++)
		{
			printf("Enter his sorce of %s:\n", subject[i]);
			scanf("%f", &ars[index].grade[i]);
			eat_line();
		}
		printf("Enter next student's name(Q to quit):\n");
	}
	eat_line();
}

int find_student(char *firname, char *surname, struct student * ars)
{
	// ������ֵΪ-1 ʱ����û�ҵ���Ӧ��ѧ��
	// �����յ�Qʱ�������˳�����ı��
	int index = -1;
	if (*firname == 'Q')
		index = -2;
	for (int i = 0; i < CSIZE; i++)
	{
		if (strcmp(firname, ars[i].name.firname) == 0 && strcmp(surname, ars[i].name.surname) == 0)
			index = i;
	}
	return index;
}

void calc_avg(struct student * ars)
{
	// ����ÿ��ѧ���Ŀ�Ŀƽ������
	for (int i = 0; i < CSIZE; i++)
	{
		float total = 0;
		for (int i = 0; i < SUBJECT; i++)
			total += ars->grade[i];
		ars->avg = total / SUBJECT;
	}
}

void show_info(struct student * ars)
{
	//  ��ӡ�ṹ�ڵ�������Ϣ
	printf("Name	Surname's Score: Language	Math	English\n");
	for (int i = 0; i < CSIZE; i++)
	{
		printf("%-7s %-7s        %10.2f %10.2f %10.2f\n", ars[i].name.firname, ars[i].name.surname, ars[i].grade[0], ars[i].grade[1], ars[i].grade[2]);
	}
}

void show_class_avg(struct student * ars)
{
	// ����༶ƽ����������ӡ
	float total = 0;
	float avg = 0.0;

	for (int i = 0; i < CSIZE; i++)
		total += ars[i].avg;
	avg = total / CSIZE;
	printf("This class has average score: %.2f.\n", avg);
}

void eat_line()
{
	// ������뻺����
	while (getchar() != '\n')
		continue;
}