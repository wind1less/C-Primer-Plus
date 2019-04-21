// һ���ı��ļ��б�����һ������ӵ���Ϣ��
// ÿ�����ݶ����������У�4 Jessie Joybat 5 2 1 1
// ��һ������Ա�ţ��䷶Χ��0~18��
// ��2 ������Ա����
// ��3 ������Ա���ա������ն���һ�����ʡ�
// ��4 ���ǹٷ�ͳ�Ƶ���Ա�ϳ�������
// ����3 ��ֱ��ǻ��������������ʹ�㣨RBI����
// 
// �ļ����ܰ����ೡ���������ݣ�����ͬһλ��Ա�����ж������ݣ�����ͬһλ��Ա�Ķ�������֮�������������Ա�����ݡ�
// ��дһ�����򣬰����ݴ��浽һ�����ݽṹ�С��ýṹ�еĳ�ԱҪ�ֱ��ʾ��Ա�������ա��ϳ������������������Ͱ����ʡ�
// ����ʹ����Ա����Ϊ������������ó���Ҫ�����ļ���β����ͳ��ÿλ��Ա�ĸ����ۼ��ۺϡ�
// 
// Ҫʵ����Щ���ܣ���򵥵ķ����ǰѽṹ�����ݶ���ʼ��Ϊ�㣬���ļ��е����ݶ�����ʱ�����У�Ȼ���������Ӧ�Ľṹ�С�
// ��������ļ���Ӧ����ÿλ��Ա�İ����ʣ����Ѽ��������浽�ṹ����Ӧ��Ա�С����㰲����������Ա���ۼƻ����������ϳ��ۼƴ���������һ�����������㡣
// ��󣬳�����������ӵ�ͳ�����ݣ�һ����ʾһλ��Ա���ۼ����ݡ�

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLEN 20						// �洢�������ַ����鳤��
#define FILELEN 20					// �洢�ļ������ַ����鳤��
#define PLAYER 19					// ��Ա����
#define LINE 128					// ���ļ��ж�ȡһ������ʱ��������ַ���

void update_info(struct team_info *, FILE *);												// ���ļ������ж�ȡ���ݲ���������ܵ������Ϣ�ṹ����
int find_player(struct team_info * sb_team, char *firname, char *surname);					// ��ÿ���е���Ա����Ѱ����Ա�������Ϣ�����е�����
void calc_bat(struct team_info *);															// ���㰲����
void show_info(struct team_info *);															// ���ո�ʽ��ӡ������Ϣ

struct team_info {
	char firname[SLEN];		// ����һ������
	char surname[SLEN];		// �գ�һ������
	int on_game;			// �ϳ�����
	int hit;				// ������
	int walk_home;			// ������
	int RBI;				// ���
	float batting_avg;		// ������
};

int main(void)
{
	FILE * fp;
	char file_name[FILELEN];

	struct team_info sb_team[PLAYER] = {
		{.firname = "Russell",.surname = "Westbrook"},
		{.firname = "Derrick",.surname = "Rose"},
		{.firname = "Kawhi",.surname = "Leonard"},
		{.firname = "Chris",.surname = "Paul"},
		{.firname = "Paul",.surname = "Millsap"},
		{.firname = "Kevin",.surname = "Garnett"},
		{.firname = "Leborn",.surname = "James"},
		{.firname = "Carmelo",.surname = "Anthony"},
		{.firname = "Kobe",.surname = "Bryant"},
		{.firname = "Andre",.surname = "Iguodala"},
		{.firname = "Tim",.surname = "Hardaway"},
		{.firname = "Kyrie",.surname = "Irving"},
		{.firname = "Dwight",.surname = "Howard"},
		{.firname = "James",.surname = "Hardon"},
		{.firname = "Bob",.surname = "Cousy"},
		{.firname = "Vince",.surname = "Carter"},
		{.firname = "Pau",.surname = "Gasol"},
		{.firname = "John",.surname = "Havlicek"},
		{.firname = "Phil",.surname = "Jackson"},
	};

	printf("enter the file's name(q to quit):\n");
	scanf("%s", file_name);
	while ((fp = fopen(file_name, "r")) == NULL || file_name[0] == 'q')
	{
		printf("Can't open %s, try again:\n", file_name);
		scanf("%s", file_name);
	}

	update_info(sb_team, fp);
	calc_bat(sb_team);
	show_info(sb_team);

	fclose(fp);

	return 0;
}

void update_info(struct team_info * sb_team, FILE * fp)
{
	// ���ļ������ж�ȡ���ݲ���������ܵ������Ϣ�ṹ����
	char line[LINE];
	char analyse[7][SLEN];

	// �Ƿ���ļ�
	rewind(fp);
	if (fgets(line, LINE, fp) == NULL || *line == EOF)
	{
		printf("Empty file!\n");
		exit(1);
	}

	// ��ȡ���� - ����ַ��� - �ۼƸ�������
	rewind(fp);
	while (fgets(line, LINE, fp) != NULL || *line == EOF)
	{
		int i = 0;
		int space = 0;
		int player_num;
		int pos = 0;
		while (line[i] != '\0')
		{
			if(line[i] != ' ')
				analyse[space][pos++] = line[i];
			else
			{
				analyse[space][pos++] = '\0';
				space++;
				pos = 0;
			}
			i++;
		}
		player_num = find_player(sb_team, analyse[1], analyse[2]);
		sb_team[player_num].on_game += atoi(analyse[3]);
		sb_team[player_num].hit += atoi(analyse[4]);
		sb_team[player_num].walk_home += atoi(analyse[5]);
		sb_team[player_num].RBI += atoi(analyse[6]);
	}
}

int find_player(struct team_info * sb_team, char *firname, char *surname)
{
	// // ��ÿ���е���Ա����Ѱ����Ա�������Ϣ�����е�����
	for (int i = 0; i < PLAYER; i++)
		if (strcmp(sb_team[i].firname, firname) == 0 && (strcmp(sb_team[i].surname, surname) == 0))
			return i;
	return -1;
}

void calc_bat(struct team_info * sb_team)
{
	// ���㰲����
	for (int i = 0; i < PLAYER; i++)
		sb_team[i].batting_avg = (float)sb_team[i].hit / (float)sb_team[i].on_game;
}

void show_info(struct team_info * sb_team)
{
	// ���ո�ʽ��ӡ������Ϣ
	printf("\nNo.  Name               ON_GAME   HIT   WALK HOME   RBI   BATTING AVG\n");
	for (int i = 0; i < PLAYER; i++)
		printf("%2d   %7s %-9s    %5d   %3d   %9d   %3d   %11.2f\n", 
				i, sb_team[i].firname, sb_team[i].surname, sb_team[i].on_game, sb_team[i].hit, sb_team[i].walk_home, sb_team[i].RBI, sb_team[i].batting_avg);
}






/************************************************************

// ������ĿҪ����ļ�

#include <stdio.h>
#include <stdlib.h>

#define TIMES 1000

int main(void)
{
	int index = 0;
	FILE * fp;
	fp = fopen("team_info.txt", "a+");

	char team[19][20] = {
		"Russell Westbrook",
		"Derrick Rose",
		"Kawhi Leonard",
		"Chris Paul",
		"Paul Millsap",
		"Kevin Garnett",
		"Leborn James",
		"Carmelo Anthony",
		"Kobe Bryant",
		"Andre Iguodala",
		"Tim Hardaway",
		"Kyrie Irving",
		"Dwight Howard",
		"James Hardon",
		"Bob Cousy",
		"Vince Carter",
		"Pau Gasol",
		"John Havlicek",
		"Phil Jackson"
	};

	for (int i = 0; i < TIMES; i++)
	{
		index = rand() % 19;
		fprintf(fp, "%d %s %d %d %d %d\n", index, team[index], rand() % 5, rand() % 4, rand() % 4, rand() % 3);
	}
	fclose(fp);
	printf("Over!");
}

************************************************/