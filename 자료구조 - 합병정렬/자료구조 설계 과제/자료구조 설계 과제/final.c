#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>

typedef struct
{
	int key;
	char value[10000];
}data_node; //���ڵ�


data_node* creat_node(data_node list)
{
	data_node* node = (data_node*)malloc(sizeof(data_node));
	node->key = list.key;
	strcpy(node->value, list.value);
	return node;
}

void merge(data_node list[], int left, int mid, int right, data_node sorted[]) //���� �պ� ���� 
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right)
	{
		if (list[i].key <= list[j].key)
		{
			sorted[k].key = list[i].key;
			strcpy(sorted[k].value, list[i].value);
			k = k + 1;
			i = i + 1;
		}

		else
		{
			sorted[k].key = list[j].key;
			strcpy(sorted[k].value, list[j].value);
			k = k + 1;
			j = j + 1;
		}
	}

	if (i>mid)
		for (l = j; l <= right; l++)
		{
			sorted[k].key = list[l].key;
			strcpy(sorted[k].value, list[l].value);
			k = k + 1;
		}

	else
		for (l = i; l <= mid; l++)
		{
			sorted[k].key = list[l].key;
			strcpy(sorted[k].value, list[l].value);
			k = k + 1;
		}

	for (l = left; l <= right; l++)
	{
		list[l].key = sorted[l].key;
		strncpy(list[l].value, sorted[l].value, 10000);
	}

}

void merge_sort(data_node list[], int left, int right, data_node sorted[]) //���� �պ� ���� 
{
	int mid;

	if (left<right)
	{
		mid = (left + right) / 2;
		merge_sort(list, left, mid, sorted);
		merge_sort(list, mid + 1, right, sorted);
		merge(list, left, mid, right, sorted);
	}

}

void merge_addr(data_node* list[], int left, int mid, int right, data_node* sorted[]) //���� �պ� ���� 
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	while (i <= mid && j <= right)

	{
		if (list[i]->key <= list[j]->key) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}

	if (i>mid)
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];

	else
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}

void merge_sort_addr(data_node* list[], int left, int right, data_node* sorted[]) //���� �պ� ���� 
{
	int mid;

	if (left<right)
	{
		mid = (left + right) / 2;
		merge_sort_addr(list, left, mid, sorted);
		merge_sort_addr(list, mid + 1, right, sorted);
		merge_addr(list, left, mid, right, sorted);
	}
}

void main()
{
	int i, n, size, sel_data, digit = 0;
	double  merge_result, merge_result2;

	printf("�迭�� ũ�⸦ �Է��ϼ��� : ");  //���� ũ�� ����
	scanf_s("%d", &size);
	srand(time(NULL));

	data_node* origin_list = (data_node*)malloc(sizeof(data_node) * size);//���� ������
	data_node* merge_list = (data_node*)malloc(sizeof(data_node) * size);//�պ�����(����)
	data_node* sorted_list = (data_node*)malloc(sizeof(data_node) * size);//���ĵ� �迭(����)
	data_node** merge_list_addr = (data_node**)malloc(sizeof(data_node*) * size);//�պ�����(�ּҰ�)
	data_node** sorted_list_addr = (data_node**)malloc(sizeof(data_node*) * size);//���ĵ� �迭(�ּҰ�)

	n = size;

	printf("������ ���� (1.���� 2.���ĵ� ���� 3.�������� ���ĵ� ����) : ");
	scanf_s("%d", &sel_data);

	for (i = 0; i < n; i++)
	{
		if (sel_data == 1)
		{
			origin_list[i].key = n * rand() / (double)RAND_MAX; //����

		}

		else if (sel_data == 2)
		{
			origin_list[i].key = i; //���ĵ� ����
		}

		else if (sel_data == 3)
		{
			origin_list[i].key = n - i; //����
		}

		else break;

		merge_list[i].key = origin_list[i].key; //���õ� ������ ����

		for (int j = 0; j < 10000; j++)
		{
			merge_list[i].value[j] = (char)(i % 10);  // value���� 0~9������ �� 10000���� �迭�� �߰�
		}

		data_node* value = creat_node(merge_list[i]); // key�� value�� ������ data_node�� �����ϰ� �ּ� �� ��ȯ

		merge_list_addr[i] = value; // �ּҰ��� ����Ʈ�� ����
	}

	clock_t start, finish;

	start = clock();
	merge_sort(merge_list, 0, n - 1, sorted_list); // �պ�����(����) ȣ�� 
	finish = clock();
	merge_result = (double)(finish - start) / CLOCKS_PER_SEC;

	start = clock();
	merge_sort_addr(merge_list_addr, 0, n - 1, sorted_list_addr); //�պ�����(�ּҰ�) ȣ��
	finish = clock();
	merge_result2 = (double)(finish - start) / CLOCKS_PER_SEC;


	for (i = 0; i < n; i++)
	{
		printf("%d,\t\t%d\t%d%,\t\t%d\t%d\t\n", origin_list[i].key, merge_list[i].key, merge_list[i].value[0], merge_list_addr[i]->key, merge_list_addr[i]->value[0]);
		// value���� ù��° �����͸� ���(10000���� ����ϸ� �� ���� �����..)
	}
	printf("\n key \t\tkey  value\t\tkey  value\n\n");
	printf("����\t\t�պ�����(����)\t\t�պ�����(�ּҰ�)\n");
	printf("\n�պ�����(����) �ð� : %f ��\t", merge_result);
	printf("\t�պ�����(�ּҰ�) �ð� : %f ��\n", merge_result2);
	getch();

}