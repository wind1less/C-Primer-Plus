#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ID_MASK		0xFF
#define ID_RESET    0xFFF00
#define SIZE_MASK   0x7F00
#define SIZE_RESET    0xF80FF
#define LEFT		0x00000
#define CENTER      0x08000
#define RIGHT       0x10000
#define ALIGN_MASK  0x18000
#define REGULAR     0x00000
#define BOLD		0x20000
#define ITALIC		0x40000
#define UNDERLINE	0x80000
#define STYLE_MASK	0xE0000
#define SIZE_SHIFT	8

typedef unsigned long font;

char do_menu(font * f);
char get_choice(const char *);
void show_menu(void);
void show_font(font f);
void eat_line();
void get_id(font * f);
void get_size(font * f);
void get_align(font * f);

int main(void)
{
	font sample = 1 | (12 << SIZE_SHIFT) | LEFT | ITALIC;
	
	while (do_menu(&sample) != 'q')
		continue;
	puts("Bye!");

	return 0;
}

char do_menu(font *f)
{
	char response;

	show_font(*f);
	show_menu();
	response = get_choice("fsabiuq");
	switch (response)
	{
	case 'f': get_id(f);			break;
	case 's': get_size(f);			break;
	case 'a': get_align(f);			break;
	case 'b': *f ^= BOLD;			break;
	case 'i': *f ^= ITALIC;			break;
	case 'u': *f ^= UNDERLINE;		break;
	case 'q':						break;
	default: fprintf(stderr, "menu problem\n");
	}

	return response;
}

char get_choice(const char * str)
{
	char ch;
	
	ch = getchar();
	ch = tolower(ch);
	eat_line();
	while (strchr(str, ch) == NULL)
	{
		printf("Please enter one of the following: %s\n", str);
		ch = tolower(getchar());
		eat_line();
	}

	return ch;
}

void eat_line(void)
{
	while (getchar() != '\n')
		continue;
}

void show_menu(void)
{
	puts("f)change font    s)change size    a)change alignment");
	puts("b)toggle bold    i)toggle italic  u)toggle underline");
	puts("q)quit");
}

void show_font(font f)
{
	printf("\n%4s %4s %9s %3s %3s %3s\n", "ID", "SIZE", "ALIGNMENT", "B", "I", "u");
	printf("%4lu %4lu", f & ID_MASK, (f & SIZE_MASK) >> SIZE_SHIFT);
	switch (f & ALIGN_MASK)
	{
	case LEFT   : printf("%7s", "left");     break;
	case RIGHT  : printf("%7s", "right");    break;
	case CENTER : printf("%7s", "center");   break;
	default     : printf("%7s", "unknown");  break;
	}
	printf("%8s %3s %3s\n\n",
		(f & BOLD)      == BOLD      ? "ON" : "OFF",
		(f & ITALIC)    == ITALIC    ? "ON" : "OFF",
		(f & UNDERLINE) == UNDERLINE ? "ON" : "OFF"
	);
}

void get_id(font * f)
{
	int id;

	printf("Enter font ID (0~255):");
	scanf("%d", &id);
	*f &= ID_RESET;
	*f |= id;
	eat_line();
}

void get_size(font * f)
{
	int size;

	printf("Enter font size (0~127):");
	scanf("%d", &size);
	*f &= SIZE_RESET;
	*f |= (size << SIZE_SHIFT);
	eat_line();
}

void get_align(font * f)
{
	puts("Select alignment:");
	puts("l)left    c)center    r)right");
	switch (get_choice("lcr"))
	{
	case 'l' : *f &= ~ALIGN_MASK;  *f |= LEFT;      break;
	case 'c' : *f &= ~ALIGN_MASK;  *f |= CENTER;    break;
	case 'r' : *f &= ~ALIGN_MASK;  *f |= RIGHT;     break;
	default:fprintf(stderr, "alignment problem\n");
	}
}













