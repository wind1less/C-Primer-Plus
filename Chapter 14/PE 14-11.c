// ��дһ����Ϊtransform() �ĺ���������4 ��������
// �ں�double �������ݵ�Դ���������ں�double �������ݵ�Ŀ����������
// һ����ʾ����Ԫ�ظ�����int ���Ͳ���������������ȼ۵ĺ���ָ�룩��
// transform() ����Ӧ��ָ������Ӧ����Դ�����е�ÿ��Ԫ�أ����ѷ���ֵ�洢��Ŀ��������ܡ�
// ���磺
// transform(source, target, 100, sin);
// ���������target[0] ����Ϊsin(source[0]),�ȵȣ�һ����100 ��Ԫ�ء�
// ��һ�������е���transform() 4�Σ��Բ��Ըú�����
// �ֱ�ʹ��math.h �������е����������Լ��Զ��������������Ϊ������

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double (*fp)(double n);

#define MAX 100

double half(double n);
double quarter(double n);


void transform(double * source, double * target, int n, fp func);
void show_ary(double *, int n);

int main(void)
{
	double source[MAX];
	double target[MAX];
	for (int i = 0; i < MAX; i++)
		source[i] = (float)rand() / 100;
	printf("Source array:\n");
	show_ary(source, MAX);

	transform(source, target, MAX, fabs);
	printf("After fabs():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, sqrt);
	printf("After sqrt():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, half);
	printf("After half():\n");
	show_ary(target, MAX);

	transform(source, target, MAX, quarter);
	printf("After quarter():\n");
	show_ary(target, MAX);
}

void transform(double * source, double * target, int n, fp func)
{
	for (int i = 0; i < n; i++)
	{
		target[i] = func(source[i]);
	}
}

void show_ary(double * ary, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i && (i % 8 == 0))
			printf("\n");
		printf("%10f  ", ary[i]);
	}
	printf("\n________________________________________________________________________________________________\n");
}

double half(double n)
{
	return n / 2;
}

double quarter(double n)
{
	return n / 4;
}