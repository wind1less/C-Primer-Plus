// 一个文本文件中保存着一个垒球队的信息。
// 每行数据都是这样排列：4 Jessie Joybat 5 2 1 1
// 第一项是球员号，其范围是0~18。
// 第2 项是球员的名
// 第3 项是球员的姓。名和姓都是一个单词。
// 第4 项是官方统计的球员上场次数。
// 接着3 项分别是击中数、走垒数和打点（RBI）。
// 
// 文件可能包含多场比赛的数据，所以同一位球员可能有多行数据，而且同一位球员的多行数据之间可能有其他球员的数据。
// 编写一个程序，把数据储存到一个数据结构中。该结构中的成员要分别表示球员的名、姓、上场次数、走垒数、打点和安打率。
// 可以使用球员号作为数组的索引。该程序要读到文件结尾，并统计每位球员的各项累计综合。
// 
// 要实现这些功能，最简单的方法是把结构的内容都初始化为零，把文件中的数据读入临时变量中，然后将其加入相应的结构中。
// 程序读完文件后，应计算每位球员的安打率，并把计算结果储存到结构的相应成员中。计算安打率是用球员的累计击中数除以上场累计次数。这是一个浮点数计算。
// 最后，程序结合整个球队的统计数据，一行显示一位球员的累计数据。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLEN 20						// 存储姓名的字符数组长度
#define FILELEN 20					// 存储文件名的字符数组长度
#define PLAYER 19					// 球员数量
#define LINE 128					// 从文件中读取一行数据时单行最大字符数

void update_info(struct team_info *, FILE *);												// 从文件中逐行读取数据并分析后汇总到球队信息结构数组
int find_player(struct team_info * sb_team, char *firname, char *surname);					// 从每行中的球员姓名寻找球员在球队信息数组中的索引
void calc_bat(struct team_info *);															// 计算安打率
void show_info(struct team_info *);															// 按照格式打印所有信息

struct team_info {
	char firname[SLEN];		// 名，一个单词
	char surname[SLEN];		// 姓，一个单词
	int on_game;			// 上场次数
	int hit;			// 击中数
	int walk_home;			// 走垒数
	int RBI;			// 打点
	float batting_avg;		// 安打率
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
	// 从文件中逐行读取数据并分析后汇总到球队信息结构数组
	char line[LINE];
	char analyse[7][SLEN];

	// 是否空文件
	rewind(fp);
	if (fgets(line, LINE, fp) == NULL || *line == EOF)
	{
		printf("Empty file!\n");
		exit(1);
	}

	// 读取数据 - 拆分字符行 - 累计各项数据
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
	// // 从每行中的球员姓名寻找球员在球队信息数组中的索引
	for (int i = 0; i < PLAYER; i++)
		if (strcmp(sb_team[i].firname, firname) == 0 && (strcmp(sb_team[i].surname, surname) == 0))
			return i;
	return -1;
}

void calc_bat(struct team_info * sb_team)
{
	// 计算安打率
	for (int i = 0; i < PLAYER; i++)
		sb_team[i].batting_avg = (float)sb_team[i].hit / (float)sb_team[i].on_game;
}

void show_info(struct team_info * sb_team)
{
	// 按照格式打印所有信息
	printf("\nNo.  Name               ON_GAME   HIT   WALK HOME   RBI   BATTING AVG\n");
	for (int i = 0; i < PLAYER; i++)
		printf("%2d   %7s %-9s    %5d   %3d   %9d   %3d   %11.2f\n", 
				i, sb_team[i].firname, sb_team[i].surname, sb_team[i].on_game, sb_team[i].hit, sb_team[i].walk_home, sb_team[i].RBI, sb_team[i].batting_avg);
}






/************************************************************

// 生成题目要求的文件

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
