// 设计一个位字段结构以储存下面的信息
// 字体ID：0~255 之间的一个数
// 字体大小：0~127 之间的一个数
// 对齐：0~2之间的一个数，表示左对齐、居中、右对齐
// 加粗：开（1）或闭（0）
// 斜体：开（1）或闭（0）
// 在一个程序中使用该结构来打印字体参数，并使用循环菜单来让用户改变参数。
// 该程序要使用按位与运算符（&）和合适的掩码来把字体ID 和字体大小转换到指定的范围内。


/*----------\
没有使用按位与转换
检验流程
/---------*/
#include <stdio.h>
#include <stdbool.h>

const char * alignment[3] = { "left", "center", "right" };

struct font_info {
	unsigned int font_id        : 8;
	unsigned int font_size      : 7;
	unsigned int                : 1;
	unsigned int font_alignment : 2;
	bool         font_bold      : 1;
	bool         font_italic    : 1;
	bool         font_underline : 1;
	unsigned int                : 3;
};

void eat_line();				// 清空输入缓冲区
void show_order();				// 显示选择菜单
void show_info(struct font_info *);		// 按格式打印字体结构中的信息
void set_id(struct font_info *);		// 设置字体ID
void set_size(struct font_info *);		// 设置字体尺寸
void set_alignment(struct font_info *);		// 设置字体对齐方式
void set_bold(struct font_info *);		// 设置字体加粗
void set_italic(struct font_info *);		// 设置字体倾斜
void set_underline(struct font_info *);		// 设置字体下换线

int main()
{
	char command;
	struct font_info ft = { 1, 12, 0, false, false, false };

	show_info(&ft);
	show_order();
	while (scanf("%c", &command) == 1 && command != 'q')
	{
		eat_line();
		switch (command)
		{
		case 'f':
			set_id(&ft);	 	 show_info(&ft);	break;
		case 's':
			set_size(&ft);		 show_info(&ft);	break;
		case 'a': 
			set_alignment(&ft);	 show_info(&ft);	break;
		case 'b':
			set_bold(&ft);	     show_info(&ft);	break;
		case 'i':
			set_italic(&ft);	 show_info(&ft);	break;
		case 'u':
			set_underline(&ft);	 show_info(&ft);	break;
		default:
			printf("Invalid command,try again:\n");
			break;
		}
		show_order();
	}
	puts("Bye!");

	return 0;
}

void show_order()
{
	puts("f)change font    s)change size    a)change alignment");
	puts("b)toggle bold    i)toggle italic  u)toggle underline");
	puts("q)quit");
}

void show_info(struct font_info * pfont)
{
	printf("  ID  SIZE  ALIGNMENT  B   I   U\n");
	printf("  %2d", pfont->font_id);
	printf("  %4d", pfont->font_size);
	printf("    %5s", alignment[pfont->font_alignment]);
	printf("   %-3s", pfont->font_bold ? "on" : "off");
	printf(" %-3s", pfont->font_italic ? "on" : "off");
	printf(" %-3s", pfont->font_underline ? "on" : "off");
	printf("\n\n");
}

void eat_line()
{
	while (getchar() != '\n')
		continue;
}

void set_id(struct font_info * pfont)
{
	unsigned int id;
	puts("Enter font id (0~255):");
	while (!(scanf("%ud", &id) == 1 && id >= 0 && id <= 255))
	{
		eat_line();
		puts("Invalid fond id,try again:");
	}
	eat_line();
	pfont->font_id = id;
}

void set_size(struct font_info * pfont)
{
	unsigned int size;
	puts("Enter font size (0~127):");
	while (!(scanf("%ud", &size) == 1 && size >= 0 && size <= 127))
	{
		eat_line();
		puts("Invalid fond id,try again:");
	}
	eat_line();
	pfont->font_size = size;
}

void set_alignment(struct font_info * pfont)
{
	char alignment;
	puts("Select alignment:");
	puts("l)left    c)center    r)right");
	int invalid_alg = 1;
	while (scanf("%c", &alignment) && strchr("lcrLCR", alignment) == NULL)
	{
		eat_line();
		puts("Invalid alignment, try again:");
	}
		eat_line();
		switch (alignment)
		{
		case 'l': 
			pfont->font_alignment = 0;	invalid_alg = 0; break;
		case 'c': 
			pfont->font_alignment = 1;	invalid_alg = 0; break;
		case 'r': 
			pfont->font_alignment = 2;	invalid_alg = 0; break;
		}
}

void set_bold(struct font_info * pfont)
{
	pfont->font_bold = !pfont->font_bold;
}

void set_italic(struct font_info * pfont)
{
	pfont->font_italic = !pfont->font_italic;
}

void set_underline(struct font_info * pfont)
{
	pfont->font_underline = !pfont->font_underline;
}
