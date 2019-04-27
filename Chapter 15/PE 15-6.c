// ���һ��λ�ֶνṹ�Դ����������Ϣ
// ����ID��0~255 ֮���һ����
// �����С��0~127 ֮���һ����
// ���룺0~2֮���һ��������ʾ����롢���С��Ҷ���
// �Ӵ֣�����1����գ�0��
// б�壺����1����գ�0��
// ��һ��������ʹ�øýṹ����ӡ�����������ʹ��ѭ���˵������û��ı������
// �ó���Ҫʹ�ð�λ���������&���ͺ��ʵ�������������ID �������Сת����ָ���ķ�Χ�ڡ�


/*----------\
û��ʹ�ð�λ��ת��
��������
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

void eat_line();
void show_order();
void show_info(struct font_info *);
void set_id(struct font_info *);
void set_size(struct font_info *);
void set_alignment(struct font_info *);
void set_bold(struct font_info *);
void set_italic(struct font_info *);
void set_underline(struct font_info *);

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