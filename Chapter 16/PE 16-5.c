// 编写一个函数接受这些参数：内含int 类型元素的数组名、数组的大小和一个代表选取次数的值。
// 该函数从数组中随机选择指定数量的元素，并打印它们。
// 每个元素只能选择一次（模拟抽奖数字或挑选陪审团成员）。
// 另外，如果你的实现有time()或类似的函数，可在srand()中使用这个函数来初始化随机数生成器rand()。
// 编写一个简单的程序测试该函数。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void randomly_select(int *ar, int size, int times);
int check_used(int *, int, int);
int main(void)
{
	int ar[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int times = 0;

	printf("Now we have 10 numbers.\n");
	printf("Enter a num to choice some number(q to quit):\n");
	while (scanf("%d", &times) == 1)
	{
		if (times > SIZE)
		{
			printf("No that many numbers,try again:\n");
			continue;
		}
		randomly_select(ar, SIZE, times);
		printf("Enter next number(q to quit):\n");
	}

	return 0;
}

void randomly_select(int *ar, int size, int times)
{
	int used[SIZE];
	int cur_rand;
	int used_index = 0;

	int seed = (int)time(NULL) % size;
	srand(seed);

	printf("Randomly select %d times:\n", times);
	for (int i = 0; i < times; i++)
	{
		cur_rand = rand() % size;

		while (check_used(used, size, cur_rand) > 0)
			cur_rand = rand() % size;
		used[used_index] = cur_rand;
		used_index++;

		printf("%3d  ", ar[cur_rand]);
		if ((i % 5) == 4)
			printf("\n");
	}
	if((times % 5) != 0)
		printf("\n");
	printf("\n");
}

int check_used(int * ar, int size, int cur_rand)
{
	// 检查随机数是否已存在
	for (int i = 0; i < size; i++)
	{
		if (ar[i] == cur_rand)
			return i;
	}
	return -1;
}
