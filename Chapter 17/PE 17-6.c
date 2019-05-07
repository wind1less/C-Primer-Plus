// 编写一个函数接受3个参数： 一个数组名、该数组的元素个数和待查找的整数。
// 如果待查找的整数在数组中，那么该函数返回1；如果该数不在数组中，该函数返回0；
// 用二分查找法实现

#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 11

int find(int arr[], int n, int finded);

int comp(const void * p1, const void * p2)
{
	int a1 = *(const int *)p1;
	int a2 = *(const int *)p2;
	return (a1 - a2);
}

int main(void)
{
	int temp;
	int arr[ARSIZE] = { 99, 7, 5, 9, 14, 4, 34, 12, 1, 43, 6 };
	// 1 4 5 6 7 9 12 14 34 43 99
	qsort(arr, ARSIZE, sizeof(int), comp);

	printf("Enter a number to be found:\n");
	while (scanf("%d", &temp) == 1)
	{
		while (getchar() != '\n')
			continue;
		if (find(arr, ARSIZE, temp))
			printf("%d is in the arr.\n", temp);
		else
			printf("%d is not in the arr.\n", temp);
		printf("Enter next number:\n");
	}
	printf("Done.");
	return 0;
}

int find(int arr[], int n, int finded)
{
	int max = n - 1;
	int min = 0;
	int mid = 0;
	while (min > max)
	{
		mid = (max + min) / 2;
		if (arr[mid] == finded)
			return 1;
		else if (arr[mid] > finded)
			max = mid - 1;
		else
			min = mid + 1;
	}
	return 0;
}
