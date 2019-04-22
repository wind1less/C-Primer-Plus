// �޸ĳ����嵥14.14�����ļ��ж�ȡÿ����¼����ʾ�����������û�ɾ����¼���޸ļ�¼�����ݡ�
// ���ɾ����¼���ѿճ����Ŀռ�������һ��Ҫ��������ݡ�
// Ҫ�޸����е��ļ����ݣ������á�r+b��ģʽ�������ǡ�a+b��ģʽ��
// ���ң��������ע�ⶨλ�ļ�ָ�룬��ֹ�¼���ļ�¼�������м�¼��
// ��򵥵ķ����ǸĶ��������ڴ��е��������ݣ�Ȼ���ٰ�������Ϣд���ļ���
// ���ٵ�һ����������book �ṹ�����һ����Ա��ʾ�Ƿ���ɾ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

char * s_gets(char * st, int n);
char select_operator(void);										// ѡ�����ģʽ
int find_title(struct book *sp, char *title, int count);		// ������book �б���Ѱ�������book
void add_record(struct book *);									// ����book
int del_record(struct book *, int count);						// ɾ��book
void amend_record(struct book *, int count);					// �޸�book
void refresh(struct book library[MAXBKS], int count);			// ÿ�β�����ɺ�ˢ��book �б�

struct book {
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
};

int main(void)
{
	struct book library[MAXBKS];
	int count = 0;								// �ۼ�book ������������ʱ�ӣ�ɾ��ʱ��
	FILE * pbooks;
	int size = sizeof(struct book);				// ����ṹ���ֽڴ�С�����д���ļ��Ķ������ֽ���Ϊ����¼������ * �ṹ���ֽڴ�С��
	int select = 0;								// ѡ��Ĳ���ģʽ

	if ((pbooks = fopen("book.dat", "r+b")) == NULL)
	{
		// �Ҳ�����Ӧ���ļ�ʱ�˳����˴���r+b, �ȶ���д��������д���ļ�ʱ��Ҫ���ļ�λ��ָ��rewind��������Ϊ׷��ģʽ�����ʹ��w+b��ɾ��ԭ�ļ������ݣ�
		fputs("Can't open book.dat file\n", stderr);
		exit(1);
	}

	rewind(pbooks);
	while (count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
	{
		// û�м�¼
		if (count == 0)
			puts("Current contents of book.dat:");
		printf("< %s> by < %8s >: $%.2f\n", library[count].title, library[count].author, library[count].value);
		count++;
	}
	if (count == MAXBKS)
	{
		// book ������Ա
		fputs("The book.dat file is full.", stderr);
		exit(2);
	}

	while ((select = select_operator()) != 'q')
	{
		// ���������б���Ӧ����
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
		refresh(library, count);		// ÿ����ɲ������ˢ��book �б�
	}

	rewind(pbooks);			// �������˴������ļ�ָ���б����õĻ�����һ�е�д��ʼ�ջ���׷��
	fwrite(library, size, count, pbooks);
	fclose(pbooks);
	puts("Bye.\n");
	 
	return 0;
}

void refresh(struct book library[MAXBKS], int count)
{
	// ÿ�β�����ɺ�ˢ��book �б�
	puts("\n\nCurrent contents of book.dat:");
	for (int i = 0; i < count; i++)
		printf("< %s> by < %8s >: $%.2f\n", library[i].title, library[i].author, library[i].value);
	printf("\n\n");
}

char select_operator(void)
{
	// ѡ�����ģʽ
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

	return tolower(select);				// ͬʱ֧�ִ�Сд
}

void add_record(struct book * sp)
{
	// ׷��һ����¼
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
	// ɾ��һ����¼�������ļ�¼ȫ����ǰ��һλ����������
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
	// �޸ļ�¼
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
	// ��book �б����ҵ������book
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