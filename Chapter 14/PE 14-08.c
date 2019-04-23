// 巨人航空公司的机群由12 个座位的飞机组成。它每天飞行一个航班。
// 根据下面的要求，编写一个座位预定程序。

// a. 该程序使用一个内含12 个结构的数组。每个结构中包括：
//    一个成员表示座位编号、一个成员表示座位是否已被预定、一个成员表示预定人的名、一个表示姓。

// b. 该程序显示下面的菜单：
//		To choose a function, enter its letter label:
//		a) Show number of empty seats					显示空座位数量
//		b) Show list of empty seats					显示空座位列表
//		c) Show alphabetical list of seats				按字母顺序显示已预订座位
//		d) Assign a customer to a seat assignment			帮客户订座
//		e) Delete a seat assignment					删除订座
//		f) Quit								退出

// c. 该程序能成功执行上面给出的菜单。选择d) 和e) 要提示用户进行额外输入，每个选项都能让用户中止输入。

// d. 执行特定程序后，该程序再次显示菜单，除非用户选择f)。

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NLEN 20			// 储存姓名的字符数组的长度
#define SEAT 12			// 飞机上的座位数量

void eat_line();										// 清空缓冲区
void show_menu();										// 打印菜单
char get_order();										// 获取指令
int show_empty_seat(struct seat_info *, int num_or_list);					// 显示空位信息
void show_rsv_seat(struct seat_info *);								// 获取已预定座位并按照字母顺序排序后显示
void assign_seat(struct seat_info *);								// 询问客户姓名座位号并入座
void sit_down(struct seat_info * seat, char * firname, char * surname, int seat_sn);		// 入座
void del_seat(struct seat_info *);								// 核对客户姓名并取消订座

struct seat_info {
	int seat_sn;
	int reserve;
	char firname[NLEN];
	char surname[NLEN];
};

int main(void)
{
	struct seat_info seat[SEAT] = {
		{.seat_sn = 0, .reserve = 0},
		{.seat_sn = 1, .reserve = 0},
		{.seat_sn = 2, .reserve = 0},
		{.seat_sn = 3, .reserve = 0},
		{.seat_sn = 4, .reserve = 0},
		{.seat_sn = 5, .reserve = 0},
		{.seat_sn = 6, .reserve = 0},
		{.seat_sn = 7, .reserve = 0},
		{.seat_sn = 8, .reserve = 0},
		{.seat_sn = 9, .reserve = 0},
		{.seat_sn = 10, .reserve = 0},
		{.seat_sn = 11, .reserve = 0},
	};

	int seats = 0;
	char order;
	while ((order = get_order()) != 'f')
	{
		seats = show_empty_seat(seat, 3);				// 每次操作后均获取座位数，避免无效操作
		switch (order)
		{
		case 'a':
			show_empty_seat(seat, 1);
			break;
		case 'b':
			show_empty_seat(seat, 2);
			break;
		case 'c':
			if (seats)
				show_rsv_seat(seat);
			else
				puts("There are no reserved seats.\n");
			break;
		case 'd':
			if (seats == SEAT)
				puts("Sorry,sir.There are no empty seats.\n");
			else
				assign_seat(seat);
			break;
		case 'e':
			if(seats)
				del_seat(seat);
			else
				puts("There are no reserved seats.\n");
			break;
		} 
	}
	printf("Done.");

	return 0;
}

void show_menu()
{
	// 打印菜单选项
	puts("To choose a function, enter its letter label:");
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Show alphabetical list of seats");
	puts("d) Assign a customer to a seat assignment");
	puts("e) Delete a seat assignment");
	puts("f) Quit");
}

char get_order()
{
	char order = 0;
	show_menu();
	while (scanf("%c", &order) == 1)
	{
		// 因为读取的是%c字符，所以下面手动忽略换行符
		if (order == '\n')
			continue;
		eat_line();
		// 同时相应大小写指令
		if (strchr("abcdef", tolower(order)) == NULL)
			printf("No this option, pls try again:\n");
		else
			break;
	}

	return tolower(order);
}

int show_empty_seat(struct seat_info * seat, int mode)
{ 
	// mode 1：打印空位的数量
	// mode 2：打印空位的列表；每行打印一定数量的空位。
	// mode 3：仅获取空位数
	const int seat_per_line = 4;
	int empty = 0;
	if(mode == 2)
		printf("This is empty seat:\n");
	for (int i = 0; i < SEAT; i++)
	{
		if (seat[i].reserve == 0)
		{
			empty++;
			if (mode == 2)
			{
				printf("SEAT %d is empty.\t", seat[i].seat_sn);
				if (empty && (empty % seat_per_line == 0))
					printf("\n");
			}
		}
	}
	if (mode == 1)
	{
		if (empty)
			printf("There are %d empty %s.\n", empty, empty == 1 ? "seat" : "seats");
		else
			printf("Sorry, no empty seats.\n");
	}
	if (mode != 3)
		printf("\n");

	return (SEAT - empty);
}

void show_rsv_seat(struct seat_info * seat)
{
	// 创建一个新数组，将已预定的座位拷贝至新数组
	// 按姓的字母顺序排序已定座位；打印已定座位列表。
	struct seat_info seat_copy[SEAT];
	struct seat_info temp;
	int reserve = 0;
	int i = 0;
	for (i = 0; i < SEAT; i++)
	{
		// 拷贝已预定座位
		if (seat[i].reserve)
		{
			strcpy(seat_copy[reserve].firname, seat[i].firname);
			strcpy(seat_copy[reserve].surname, seat[i].surname);
			seat_copy[reserve].seat_sn = seat[i].seat_sn;
			reserve++;
		}
	}

	for (i = 0; i < reserve; i++)
	{
		// 按字母排序
		for (int n = i; n < reserve; n++)
		{
			if (strcmp(seat_copy[i].firname, seat_copy[n].firname) > 0)
			{
				temp = seat_copy[i];
				seat_copy[i] = seat_copy[n];
				seat_copy[n] = temp;
			}
		}
	}

	for (i = 0; i < reserve; i++)
		printf("%s %s : seat [%2d]\n", seat_copy[i].firname, seat_copy[i].surname, seat_copy[i].seat_sn);
	printf("\n");
}

void assign_seat(struct seat_info * seat)
{
	// 订座
	// 提供手动选座或自动选座
	// 自动选座是伪随机，暂未添加实时随机
	// 注意两种选座方式都要检测座位冲突
	char firname[NLEN], surname[NLEN];
	int seat_sn = 0;
	puts("What's your name?");
	scanf("%s %s", &firname, &surname);
	eat_line();
	printf("Hello, MR.%s, enter 'a' to enter a seat number, or we'll give you a random seat number:\n", firname);
	if (getchar() == 'a')
	{
		eat_line();
		printf("enter the seat number you want:\n");
		while (scanf("%d", &seat_sn) != 1 || seat_sn > SEAT || seat_sn < 1 || seat[seat_sn].reserve)
		{
			eat_line();
			if (seat_sn > SEAT || seat_sn < 1)
				printf("No this seat, try again:\n");
			else if (seat[seat_sn].reserve == 1)
				printf("Sorry, this seat has been reserved, please choice another:\n");
			seat_sn = -1;
		}
		sit_down(seat, firname, surname, seat_sn);
	}
	else
	{
		eat_line();

		while(seat[(seat_sn = rand() % 12)].reserve == 1);
		printf("We provide seat %d for you.\n", seat_sn);
		sit_down(seat, firname, surname, seat_sn);
	}
}

void sit_down(struct seat_info * seat, char * firname, char * surname, int seat_sn)
{
	// 将姓名设置到座位上，切换预定状态
	strcpy(seat[seat_sn].firname, firname);
	strcpy(seat[seat_sn].surname, surname);
	seat[seat_sn].reserve = 1;
	printf("OK, %s %s have seat %d.\n\n", firname, surname, seat_sn);
}

void del_seat(struct seat_info * seat)
{
	// 删除客户的订座
	char firname[NLEN], surname[NLEN];
	int seat_sn = -1;
	puts("What's your name?");
	scanf("%s %s", &firname, &surname);
	eat_line();

	// 检测客户信息
	for (int i = 0; i < SEAT; i++)
	{
		if (seat[i].reserve == 1)
		{
			if (strcmp(seat[i].firname, firname) == 0 && strcmp(seat[i].surname, surname) == 0)
				seat_sn = i;
		}
	}
	
	if (seat_sn == -1)
		// 没有找到客户信息
		puts("Sorry sir, you havn't reserve a seat.\n");
	else
	{
		// 清空姓名，改变预定状态，打印删除订单的信息。
		seat[seat_sn].firname[0] = '\0';
		seat[seat_sn].surname[0] = '\0';
		seat[seat_sn].reserve = 0;
		printf("Mr. %s, we have cancel your seat [%2d].\n\n", firname, seat_sn);
	}
}


void eat_line()
{
	// 清空输入缓冲区
	while (getchar() != '\n')
		continue;
}
