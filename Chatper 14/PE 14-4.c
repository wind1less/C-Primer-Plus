// ��дһ�����򣬴���һ����������Ա�Ľṹģ�壺
// a. ��1 ����Ա����ᱣ�պţ�
// ��2 ����Ա��һ����3 ����Ա�Ľṹ����1 ����Ա����������2 ����Ա�����м�������3 ����Ա�����ա�
// ��������ʼ��һ���ں�5 �������ͽṹ�����顣
// �ó���������ĸ�ʽ��ӡ���ݣ�   Dribble, Flossie M. -- 302039823
// ������м�����ֻ��ӡ���ĵ�1 ����ĸ�������һ���㣨.����
// ���û���м��������ô�ӡ�㡣
// ��дһ��������д�ӡ���ѽṹ���鴫�ݸ����������
// b. �޸�a ���֣����ݽṹ��ֵ�����ǽṹ�ĵ�ַ��

#include <stdio.h>
#include <string.h>

#define SLEN 6
#define MEN  5

struct all_name { char firname[SLEN]; char midname[SLEN]; char surname[SLEN]; };

struct persion_info {
	long long society_security;
	struct all_name name;
};

void ashow_info(struct persion_info * info);				// ��ʽa. �����ṹ�����ڵ���Ϣ������ʽ��ӡ
void bshow_info(struct persion_info info[MEN]);				// ��ʽb. �����ṹ�����ڵ���Ϣ������ʽ��ӡ

int main(void)
{
	struct persion_info zyzn[MEN] =
	{
 		{ 41272419970803, { "Wang", "Xiao", "Hao" }},
		{ 41272419950603, { "Xiao", "Da", "Di" }},
		{ 41272419960330, { "Liu", " ", "Hao" }},
		{ 41272419750224, { "Zhou", "Da", "Chao" } },
		{ 41148419850319, { "Zheng", "Xiao", "Gang" }}
	};
	printf("Method A: ----------\n");
	ashow_info(zyzn);
	printf("\nMethod B: ----------\n");
	bshow_info(zyzn);
	printf("\nBye!\n");

	return 0;
}

void ashow_info(struct persion_info * info)
{
	// ��ʽa. �����ṹ�����ڵ���Ϣ������ʽ��ӡ
	for (int i = 0; i < MEN; i++)
	{
		printf("%*s %*s ", SLEN, (info + i)->name.surname, SLEN, (info + i)->name.firname);
		if ((info + i)->name.midname[0] != ' ')
			printf("%c. ", (info + i)->name.midname[0]);
		else
			printf("   ");
		printf(" -- %lld\n", (info + i)->society_security);
	}
}

void bshow_info(struct persion_info info[MEN])
{
	// ��ʽb. �����ṹ�����ڵ���Ϣ������ʽ��ӡ
	for (int i = 0; i < MEN; i++)
	{
		printf("%*s %*s ", SLEN, info[i].name.surname, SLEN, info[i].name.firname);
		if (info[i].name.midname[0] != ' ')
			printf("%c. ", info[i].name.midname[0]);
		else
			printf("   ");
		printf(" -- %lld\n", info[i].society_security);
	}
} 