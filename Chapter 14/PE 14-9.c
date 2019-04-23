// ���˺��չ�˾�Ļ�Ⱥ��12 ����λ�ķɻ���ɡ���ÿ�����һ�����ࡣ
// ���������Ҫ�󣬱�дһ����λԤ������
// a. �ó���ʹ��һ���ں�12 ���ṹ�����顣ÿ���ṹ�а�����
//    һ����Ա��ʾ��λ��š�һ����Ա��ʾ��λ�Ƿ��ѱ�Ԥ����һ����Ա��ʾԤ���˵�����һ����ʾ�ա�
// b. �ó�����ʾ����Ĳ˵���
//		To choose a function, enter its letter label:
//		a) Show number of empty seats					��ʾ����λ����
//		b) Show list of empty seats						��ʾ����λ�б�
//		c) Show alphabetical list of seats				����ĸ˳����ʾ��Ԥ����λ
//		d) Assign a customer to a seat assignment		��ͻ�����
//		e) Delete a seat assignment						ɾ������
//		f) Quit											�˳�
// c. �ó����ܳɹ�ִ����������Ĳ˵���ѡ��d) ��e) Ҫ��ʾ�û����ж������룬ÿ��ѡ������û���ֹ���롣
// d. ִ���ض�����󣬸ó����ٴ���ʾ�˵��������û�ѡ��f)��

// ���˺��չ�˾��Ҫ��һ�ܷɻ���������ͬ����ÿ���4�ࣨ����102��311��444 ��519����
// �ѳ�����չΪ���Դ���4 �����ࡣ��һ������˵��ṩ����ѡ����˳���ѡ��һ���ض����࣬�ͻ���ֺͱ����ϰ8 ���ƵĲ˵���
// ���Ǹò˵�Ҫ���һ����ѡ�ȷ����λ���䡣���ң��˵��е��˳��Ƿ��ض���˵���
// ÿ����ʾ��Ҫָ����ǰ���ڴ���ĺ���š����⣬��λ������ʾҪָ��ȷ��״̬��

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NLEN 20			// �����������ַ�����ĳ���
#define SEAT 12			// �ɻ��ϵ���λ����
#define FLIGHT 4		// ��������

void eat_line();																			// ��ջ�����
void show_menu(int flight);																			// ��ӡ�˵�
char get_order(int flight);																			// ��ȡָ��
int show_empty_seat(struct seat_info *, int num_or_list, int flight);									// ��ʾ��λ��Ϣ
void show_rsv_seat(struct seat_info *, int flight);														// ��ȡ��Ԥ����λ��������ĸ˳���������ʾ
void assign_seat(struct seat_info *, int flight);														// ѯ�ʿͻ�������λ�Ų�����
void sit_down(struct seat_info * seat, char * firname, char * surname, int seat_sn, int flight);		// ����
void del_seat(struct seat_info *, int flight);															// �˶Կͻ�������ȡ������

struct seat_info {
	int seat_sn;
	int reserve;
	char firname[NLEN];
	char surname[NLEN];
	int flight;
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
	int airplane[FLIGHT] = { 102, 311, 444, 519 };		// �����
	int FLT_NO;											// ��ǰ�����
	
	printf("Select a airplane in [102 311 444 519] (NAN to quit):\n");
	while (scanf("%d", &FLT_NO) == 1)
	{
		int no_flight = 1;
		eat_line();
		for (int i = 0; i < FLIGHT; i++)
		{
			if (FLT_NO == airplane[i])
				no_flight = 0;
		}
		if (no_flight)
		{
			printf("No this flight, try again\n");
			continue;
		}

		while ((order = get_order(FLT_NO)) != 'f')
		{
			seats = show_empty_seat(seat, 3, FLT_NO);				// ÿ�β��������ȡ��λ����������Ч����
			switch (order)
			{
			case 'a':
				show_empty_seat(seat, 1, FLT_NO);
				break;
			case 'b':
				show_empty_seat(seat, 2, FLT_NO);
				break;
			case 'c':
				if (seats)
					show_rsv_seat(seat, FLT_NO);
				else
					puts("There are no reserved seats.\n");
				break;
			case 'd':
				if (seats == SEAT)
					puts("Sorry,sir.There are no empty seats.\n");
				else
					assign_seat(seat, FLT_NO);
				break;
			case 'e':
				if (seats)
					del_seat(seat, FLT_NO);
				else
					puts("There are no reserved seats.\n");
				break;
			}
		}
		printf("Select a airplane in [102 311 444 519] (NAN to quit):\n");
	}
	printf("Done.");

	return 0;
}

void show_menu(int flight)
{
	// ��ӡ�˵�ѡ��
	printf("FLIGHT NUM: [ %d ] \n", flight);
	puts("To choose a function, enter its letter label:");
	puts("a) Show number of empty seats");
	puts("b) Show list of empty seats");
	puts("c) Show alphabetical list of seats");
	puts("d) Assign a customer to a seat assignment");
	puts("e) Delete a seat assignment");
	puts("f) Quit");
}

char get_order(int flight)
{
	char order = 0;
	show_menu(flight);
	while (scanf("%c", &order) == 1)
	{
		// ��Ϊ��ȡ����%c�ַ������������ֶ����Ի��з�
		if (order == '\n')
			continue;
		eat_line();
		// ͬʱ��Ӧ��Сдָ��
		if (strchr("abcdef", tolower(order)) == NULL)
			printf("No this option, pls try again:\n");
		else
			break;
	}

	return tolower(order);
}

int show_empty_seat(struct seat_info * seat, int mode, int flight)
{ 
	// mode 1����ӡ��λ������
	// mode 2����ӡ��λ���б�ÿ�д�ӡһ�������Ŀ�λ��
	// mode 3������ȡ��λ��
	const int seat_per_line = 4;
	int empty = 0;
	if (mode == 2)
	{
		printf("FLIGHT NUM: [ %d ]\n", flight);
		printf("This is empty seat:\n");
	}
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

void show_rsv_seat(struct seat_info * seat, int flight)
{
	// ����һ�������飬����Ԥ������λ������������
	// ���յ���ĸ˳�������Ѷ���λ����ӡ�Ѷ���λ�б�
	struct seat_info seat_copy[SEAT];
	struct seat_info temp;
	int reserve = 0;
	int i = 0;
	for (i = 0; i < SEAT; i++)
	{
		// ������Ԥ����λ
		if (seat[i].reserve)
		{
			seat_copy[reserve] = seat[i];
			//strcpy(seat_copy[reserve].firname, seat[i].firname);
			//strcpy(seat_copy[reserve].surname, seat[i].surname);
			//seat_copy[reserve].seat_sn = seat[i].seat_sn;
			//seat_copy[reserve].flight = seat[i].flight;
			reserve++;
		}
	}

	for (i = 0; i < reserve; i++)
	{
		// ����ĸ����
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

	printf("This is reserved seat:\n");
	for (i = 0; i < reserve; i++)
		printf("    %s %s : seat [ %d ] [%2d]\n", seat_copy[i].firname, seat_copy[i].surname, seat_copy[i].flight, seat_copy[i].seat_sn);
	printf("\n");
}

void assign_seat(struct seat_info * seat, int flight)
{
	// ����
	// �ṩ�ֶ�ѡ�����Զ�ѡ��
	// �Զ�ѡ����α�������δ���ʵʱ���
	// ע������ѡ����ʽ��Ҫ�����λ��ͻ
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
		sit_down(seat, firname, surname, seat_sn, flight);
	}
	else
	{
		eat_line();

		while(seat[(seat_sn = rand() % 12)].reserve == 1);
		printf("We provide seat %d for you.\n", seat_sn);
		sit_down(seat, firname, surname, seat_sn, flight);
	}
}

void sit_down(struct seat_info * seat, char * firname, char * surname, int seat_sn, int flight)
{
	// ���������õ���λ�ϣ��л�Ԥ��״̬
	strcpy(seat[seat_sn].firname, firname);
	strcpy(seat[seat_sn].surname, surname);
	seat[seat_sn].reserve = 1;
	seat[seat_sn].flight = flight;
	printf("OK, %s %s have seat [ %d ] [ %d ].\n\n", firname, surname, flight, seat_sn);
}

void del_seat(struct seat_info * seat, int flight)
{
	// ɾ���ͻ��Ķ���
	char firname[NLEN], surname[NLEN];
	int seat_sn = -1;
	puts("What's your name?");
	scanf("%s %s", &firname, &surname);
	eat_line();

	// ���ͻ���Ϣ
	for (int i = 0; i < SEAT; i++)
	{
		if (seat[i].reserve == 1)
		{
			if (strcmp(seat[i].firname, firname) == 0 && strcmp(seat[i].surname, surname) == 0)
				seat_sn = i;
		}
	}
	
	if (seat_sn == -1)
		// û���ҵ��ͻ���Ϣ
		puts("Sorry sir, you havn't reserve a seat.\n");
	else
	{
		// ����������ı�Ԥ��״̬����ӡɾ����������Ϣ��
		seat[seat_sn].firname[0] = '\0';
		seat[seat_sn].surname[0] = '\0';
		seat[seat_sn].reserve = 0;
		seat[seat_sn].flight = 0;
		printf("Mr. %s, we have cancel your seat [ %d ] [ %2d ].\n\n", firname, flight, seat_sn);
	}
}


void eat_line()
{
	// ������뻺����
	while (getchar() != '\n')
		continue;
}