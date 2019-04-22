// 修改程序清单14.14，从文件中读取每条记录并显示出来，允许用户删除记录或修改记录的内容。
// 如果删除记录，把空出来的空间留给下一个要读入的内容。
// 要修改现有的文件内容，必须用“r+b”模式，而不是“a+b”模式。
// 而且，必须更加注意定位文件指针，防止新加入的记录覆盖现有记录。
// 最简单的方法是改动储存在内存中的所有数据，然后再把最后的信息写入文件。
// 跟踪的一个方法是在book 结构中添加一个成员表示是否该项被删除。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

char * s_gets(char * st, int n);
char select_operator(void);										// 选择操作模式
int find_title(struct book *sp, char *title, int count);		// 从现有book 列表中寻找输入的book
void add_record(struct book *);									// 新增book
int del_record(struct book *, int count);						// 删除book
void amend_record(struct book *, int count);					// 修改book
void refresh(struct book library[MAXBKS], int count);			// 每次操作完成后刷新book 列表

struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};

int main(void)
{
	struct book library[MAXBKS];
	int count = 0;								// 累计book 的数量，新增时加，删除时减
	FILE * pbooks;
	int size = sizeof(struct book);				// 计算结构的字节大小，最后写入文件的二进制字节数为（记录的数量 * 结构的字节大小）
	int select = 0;								// 选择的操作模式

	if ((pbooks = fopen("book.dat", "r+b")) == NULL)
	{
		// 找不到对应的文件时退出；此处用r+b, 先读后写，在最终写入文件时需要将文件位置指针rewind，否则会成为追加模式；如果使用w+b会删除原文件内数据；
		fputs("Can't open book.dat file\n", stderr);
		exit(1);
	}

	rewind(pbooks);
	while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
	{
		// 没有记录
		if (count == 0)
			puts("Current contents of book.dat:");
		printf("< %s> by < %8s >: $%.2f\n", library[count].title, library[count].author, library[count].value);
		count++;
	}
	if (count == MAXBKS)
	{
		// book 数组满员
		fputs("The book.dat file is full.", stderr);
		exit(2);
	}

	while ((select = select_operator()) != 'q')
	{
		// 给出操作列表，响应操作
		switch (select)
		{
		case 'n':
			add_record(&library[count]);
			count++;
			break;
		case 'd':
			if(del_record(library, count))
				count--;
			break;
		case 'a':
			amend_record(library, count);
			break;
		}
		refresh(library, count);		// 每次完成操作后均刷新book 列表
	}

	rewind(pbooks);			// ！！！此处不将文件指针列表重置的话，下一行的写入始终会变成追加
	fwrite(library, size, count, pbooks);
	fclose(pbooks);
	puts("Bye.\n");
	 
	return 0;
}

void refresh(struct book library[MAXBKS], int count)
{
	// 每次操作完成后刷新book 列表
	puts("\n\nCurrent contents of book.dat:");
	for (int i = 0; i < count; i++)
		printf("< %s> by < %8s >: $%.2f\n", library[i].title, library[i].author, library[i].value);
	printf("\n\n");
}

char select_operator(void)
{
	// 选择操作模式
	char select = 0;
	
	printf("Select a operator:\n");
	printf("N:) add new record    D:) delete a record\n");
	printf("A:) amend a record         Q:) quit program\n");
	scanf("%c", &select);
	while (getchar() != '\n')
		continue;
	while (strchr("ndaqNDAQ", select) == NULL)
	{
		printf("Invalid choice, try again:\n");
		scanf("%c", &select);
		while (getchar() != '\n')
			continue;
	}

	return tolower(select);				// 同时支持大小写
}

void add_record(struct book * sp)
{
	// 追加一条记录
	puts("Please add new book titles.");
	while (s_gets(sp->title, MAXTITL) == NULL || sp->title[0] == '\0')
		puts("Invalid input,try again\n");
	puts("Now enter the author.");
	s_gets(sp->author, MAXAUTL);
	puts("Now enter the value.");
	scanf("%f", &sp->value);
	while (getchar() != '\n')
			continue;
}

int del_record(struct book * sp, int count)
{
	// 删除一条记录，后续的记录全部向前移一位（索引）。
	//struct book temp;
	int del = 0;
	char title[MAXTITL];
	puts("Whick books do you want to delete?");
	while (s_gets(title, MAXTITL) == NULL || title[0] == '\0')
		puts("Invalid input,try again\n");
	if ((del = find_title(sp, title, count)) == -1)
	{
		puts("No this book!\n");
		return 0;
	}
	else
	{
		for (int i = del; i < count; i++)
		{
			//temp = sp[i + 1];
			//sp[i] = temp;
			sp[i] = sp[i + 1];
		}
		return 1;
	}
}

void amend_record(struct book * sp, int count)
{
	// 修改记录
	int amend = 0;
	char title[MAXTITL];
	puts("Which books do you want to amend?");
	while (s_gets(title, MAXTITL) == NULL || title[0] == '\0')
		puts("Invalid input,try again\n");
	if ((amend = find_title(sp, title, count)) == -1)
	{
		puts("No this book!\n");
	}
	else
	{
		puts("Please amend new book titles.");
		while (s_gets(sp[amend].title, MAXTITL) == NULL || sp[amend].title[0] == '\0')
			puts("Invalid input,try again\n");
		puts("Now enter the author.");
		s_gets(sp[amend].author, MAXAUTL);
		puts("Now enter the value.");
		scanf("%f", &sp[amend].value);
	}
}


int find_title(struct book *sp, char *title, int count)
{
	// 从book 列表里找到请求的book
	int find = -1;
	for (int i = 0; i < count; i++)
	{
		if (strcmp(sp[i].title, title) == 0)
			find = i;
	}

	return find;
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