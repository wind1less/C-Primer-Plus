// ��дһ������ͨ��һ������ָ������ʵ�ֲ˵���
// ���磬ѡ��˵��е�a���������ɸ������1 ��Ԫ��ָ��ĺ�����

#include <stdio.h>

int func_a();
int func_b();
int func_c();

int main(void)
{
	int order = 0;
	int(*pf[3])() = { func_a, func_b, func_c };
	printf("Select a function ( 0 - 2, overrange to quit ):\n");
	while (scanf("%d", &order) == 1 && order < 3 && order > -1)
	{
		while (getchar() != '\n')
			continue;
		pf[order]();		// ����ͨ������ָ����ú����ķ�ʽ
		//(*pf[order])();
	}
}

int func_a()
{
	printf("This is function A!\n");

	return 1;
}

int func_b()
{
	printf("This is function B!\n");

	return 2;
}

int func_c()
{
	printf("This is function C!\n");

	return 2;
}