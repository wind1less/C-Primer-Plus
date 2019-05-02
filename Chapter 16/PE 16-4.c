// ANSI 库这样描述clock() 函数的特性：
// #include <time.h>
// clock_t clock(void);
// 这里，clock_t 是定义在time.h 中的类型。
// 该函数返回处理器时间，其单位取决于实现（如果处理器时间不可用或无法表示，该函数将返回-1）。
// 然而，CLOCKS_PER_SEC（也定义在time.h中）是每秒处理器时间单位的数量。因此，两个clock() 返回值的差值除以CLOCKS_PER_SEC 得到两次调用之间经过的秒数。
// 在进行除法运算之前，接受一个double 类型的参数表示时间延迟数，然后在这段时间运行一个循环。
// 编写一个简单的程序测试该函数。

#include <stdio.h>
#include <time.h>

int main(void)
{
	clock_t time;
	float dividend = 9.99;
	float divisor = 3.33;
	int times = 1000000;

	time = clock();
	for(int i = 0; i < times; i++)
		dividend / divisor;
	time = clock() - time;

	printf("[%.2f / %.2f] calculate %d times spend %f sec.", dividend, divisor, times, (float)time / (float)CLOCKS_PER_SEC);

	return 0;
}
