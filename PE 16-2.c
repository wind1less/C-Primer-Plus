// �����ĵ���ƽ�����������㣺�ȵõ������ĵ�����Ȼ���������������ƽ��ֵ�����ȡ�������ĵ�����
// ʹ��#define ָ���һ���ꡰ��������ִ�иü��㡣��дһ���򵥵ĳ�����Ըúꡣ

#include <stdio.h>

#define  harmonic_average(X, Y) (1 / (((1 / X) + (1 / Y)) / 2))				// �������ƽ����

int main(void)
{
	float num1, num2;

	puts("Enter two number to calc its harmonic average(q to quit):");
	while (scanf("%f %f", &num1, &num2) == 2)
	{
		while (getchar() != '\n')
			continue;
		printf("%.2f and %.2f has harmonic average: %.4f.\n", num1, num2, harmonic_average(num1, num2));
		printf("Enter next pair of number(q to quit):\n");
	}
	printf("Bye!");
	
	return 0;
}