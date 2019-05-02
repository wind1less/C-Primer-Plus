// 修改程序清单16.17，使用struct names 元素，而不是double 类型的数组。
// 使用较少的元素，并用选定的名字显式初始化数组。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 5
#define SLEN 20

struct name {
	char first_name[SLEN];
	char second_name[SLEN];
};

//void fillarray(struct name names[], int n);
void showarray(const struct name names[], int n);
int mycomp(const struct name * p1, const struct name * p2);

int main(void)
{
	struct name names[NUM] = {
		{"tony", "hao"},
		{"li", "tony"},
		{"aha", "feg"},
		{"li", "lei"},
		{"lei", "hl"}
	};

	//double vals[NUM];
	//fillarray(vals, NUM);
	puts("Random list:");
	showarray(names, NUM);
	qsort(names, NUM, sizeof(struct name), mycomp);
	puts("\nSorted list:");
	showarray(names, NUM);

	return 0;
}

//void fillarray(double ar[], int n)
//{
//	int index;
//	`
//	for (index = 0; index < n; index++)
//		ar[index] = (double)rand() / ((double)rand() + 0.1);
//}

void showarray(const struct name names[], int n)
{
	int index;

	for (index = 0; index < n; index++)
	{
		printf("%s %s\n", names[index].first_name, names[index].second_name);
	}
	putchar('\n');
}

int mycomp(const struct name * name1, const struct name * name2)
{
	// 注意：作为qsort函数的实参的comp函数，comp函数的形参一定要是指针。
	// 经测试，使用void 类型的指针与使用实际情况类型的指针，运行效果相同。
	//struct name * name1 = (const struct name *)p1;
	//struct name * name2 = (const struct name *)p2;
	int dist;
	dist = strcmp(name1->first_name, name2->first_name);
	if (dist)
		return dist;
	else
		return strcmp(name1->second_name, name2->second_name);
}
