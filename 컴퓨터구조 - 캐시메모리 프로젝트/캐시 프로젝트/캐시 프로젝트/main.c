#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

static int menu;
#define Trial 300
#define Cache_size 8

typedef struct {
	int word[4];   //����
	int tag;      //�±�
	int count;      //���� ȸ��
	int valid;      //��ȿ ��Ʈ
	int access_time;   //���� �ð�
} block_type;



typedef struct {
	int count; // �ֱ� ���� �ð� ����
	block_type line[Cache_size];   //ĳ�ø޸� ���
} cache;

void time_count(cache* c, int access)  // �ֱ� ���� �ð� ����
{
	//ĳ���� ��� ��ü�� �̷������ ��� ���� ĳ�ú�ϵ��� �ֱ� ���ٽð� ����
	int i;
	for (i = 0; i < Cache_size; i++) {
		if (access < c->line[i].access_time) {
			c->line[i].access_time--;
		}
	}
}

init_cache(cache* c)  //ĳ�� �ʱ�ȭ
{
	int i;
	c->count = 0;
	for (i = 0; i < Cache_size; i++)
	{
		c->line[i].tag = 0;
		c->line[i].valid = 0;
		c->line[i].count = 0;
		c->line[i].access_time = 0;
	}
}

int cache_check(int tag, cache* c)  //ĳ���� �±׸޸� ��
{

	int i, j;
	//�±� ��
	//�±� ��
	for (i = 0; i < Cache_size; i++) {
		if (tag == c->line[i].tag) {
			if (menu == 1) {	//FIFO�϶�
				c->line[i].count++;
				printf("����-> %d\n", c->line[i].tag);
				return 1;
			}
			else {	//LRU�϶�
				c->line[i].count++;
				time_count(c, c->line[i].access_time);
				c->line[i].access_time = c->count - 1;
				printf("����-> %d\n", c->line[i].tag);
				return 1;
			}
		}
	}
	return 0;
}

//LRFU ���
void LRU_method(cache* c, int tag) {
	//LRFU ����
	int count_min = c->line[1].count;
	int change_line;

	for (int i = 0; i < Cache_size; i++) {
		if (count_min >= c->line[i].count) {
			count_min = c->line[i].count;
			change_line = i;
		}
	}
	

	int order_access = c->line[change_line].access_time;
	for (int i = 0; i < Cache_size; i++) {
		if(c->line[change_line].count == c->line[i].count)
			if (c->line[change_line].access_time > c->line[i].access_time) {
				change_line = i;
			}
	}

	for (int i = 0; i < Cache_size; i++)
	{
		if (c->line[change_line].access_time < c->line[i].access_time)
			c->line[i].access_time--;
	}
	  
	c->line[change_line].tag = tag;
	c->line[change_line].valid = 1;
	c->line[change_line].count = 1;
	c->line[change_line].access_time = 7;
}


//FIFO ���
void FIFO_method(cache* c, int tag) {
	//FIFO ����
	
	int line;
	for (int i = 0; i < Cache_size; i++) {
		if (c->line[i].access_time == 0) {
			c->line[i].tag = tag;
			c->line[i].valid = 1;
			//c->line[i].count = 1;	// ĳ�ÿ� �����͸� ������ �� ī��Ʈ�� �ʱ�ȭ�� ���� �ʴ´�.
			c->line[i].access_time = 7;
			line = i;
		}
	}
	
	for (int i = 0; i < Cache_size; i++) {
		if (line != i)
			c->line[i].access_time--;
	}
	
}

void memory_load(int tag, cache* c)            //�޸𸮿��� ��ɾ� ��� �о����
{
	int i, j, temp, valid = 0;

	FILE* memory = fopen("memory.txt", "r+");      //�޸� ����
	if (memory == NULL) {
		// ������ �������� ������ ���α׷� ����
		printf("���� ���� ����! ���α׷��� �����մϴ�.\n");
		return 0;
	}
	for (i = 0; i < 512; i++)         // EX) 512Byte �޸� ����
	{
		fscanf(memory, "%d", &temp);   //�޸��� ��� ��ȣ ����

		if (temp == tag)   //ĳ���� �±׿� �޸� ��� ��ȣ�� ��ġ�ϴ� ���
		{
			for (j = 0; j < Cache_size; j++) {
				if (c->line[j].valid == 0) { //ĳ���� ��ȿ��Ʈ Ȯ�� �� 0�̸� ��밡��
					c->line[j].valid = 1;   //��ȿ��Ʈ ����
					c->line[j].tag = temp;   //�޸� ��� ��ȣ ĳ�ÿ� ���
					c->line[j].count++;   //LRFU�� ���� ���� Ƚ�� ����
					c->line[j].access_time = j; //LRFU �� FIFO ����� ���� ���� �ð� ����
					valid = 1;
					c->count++;   //���� �ð� ���� ����
					break;
				}
			}
			if (valid == 0) {
				if (menu == 1)
					FIFO_method(c, tag);// FIFO ��� ��� ��ü
				else if (menu == 2)
					LRU_method(c, tag);   // LRFU ��� ��� ��ü   
				else
					printf("�߸� �����ϼ̽��ϴ�.");
			}

			printf("ĳ������|	Tag	|	count	|	access	|	��ȿ��Ʈ|\n");
			for (j = 0; j < Cache_size; j++) {
				printf("ĳ�� %d:	|	%d	|	%d	|	%d	|	%d	|\n", j, c->line[j].tag, c->line[j].count, c->line[j].access_time, c->line[j].valid);
			}
		}

	}
}

void input_data(FILE* input, cache* c)
{
	int temp;
	int i, j, k;

	int hit = 0;
	for (i = 0; i < Trial; i++)  //��ɾ� �� ��ŭ �ݺ�
	{
		fscanf(input, "%d", &temp);
		printf("ĳ�� Ȯ�� : %d\n", temp);
		if (cache_check(temp, c))  //ĳ�� ���� ��ɾ� �±װ� �ִ��� Ȯ��
		{
			hit++;  //ĳ�� ����
			printf("ĳ������|	Tag	|	count	|	access	|	��ȿ��Ʈ|\n");
			for (j = 0; j < Cache_size; j++) {

				printf("ĳ�� %d:	|	%d	|	%d	|	%d	|	%d	|\n", j, c->line[j].tag, c->line[j].count, c->line[j].access_time, c->line[j].valid);
			}
		}
		else               //ĳ�� ���� ��ɾ� �±װ� ���� ���
		{
			printf("����\n");
			memory_load(temp, c);  //�޸𸮿��� ��ɾ� ��� �о����
		}
	}
	printf("���� : %d ȸ\n", hit);
}



int main() {

	cache c;

	FILE* input = fopen("input.txt", "r+");
	//FILE* input = fopen("input2.txt", "r+");
	if (input == NULL) {
		// ������ �������� ������ ���α׷� ����
		printf("���� ���� ����! ���α׷��� �����մϴ�.\n");
		return 0;
	}
	while (1) {
		printf("1. FIFO ���\n2. LRFU ���\n����� �������ּ���:");
		scanf("%d", &menu);
		if (menu == 1 || menu == 2)
			break;
	}
	init_cache(&c);  //ĳ�� �ʱ�ȭ
	input_data(input, &c); //������ �Է�
	system("pause");
}