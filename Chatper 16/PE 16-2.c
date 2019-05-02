// 两数的调和平均数这样计算：先得到两数的倒数，然后计算两个倒数的平均值，最后取计算结果的倒数。
// 使用#define 指令定义一个宏“函数”，执行该计算。编写一个简单的程序测试该宏。

#include <stdio.h>

#define  harmonic_average(X, Y) (1 / (((1 / X) + (1 / Y)) / 2))				// 计算调和平均数

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
