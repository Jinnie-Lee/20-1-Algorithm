#define _CRT_SECURE_NO_WARNINGS	
#define MAX 40
#include <stdio.h>

struct item {
	int id;
	int w;
	int p;
};	//�ε���, weight, profit ��� ����ü ����

void insertion_sort(item[], int);
bool promising(int, int, item[]);
void knapsack(int, int, int, item[]);

int maxprice, num, M, profit;
int numbest = 0;	//����� �͵� ����
char bestset[MAX];	//�ִ� ������ �� ������ �͵�
char include[MAX];	//���� ������ ��

int main(void) {
	item ITEM[MAX];

	int p[MAX];				//����
	int w[MAX];				//����
	int index[MAX] = { 0 };	//�� ���� ���� �ε��� ������

	FILE* file = fopen("p2data6.txt", "r");	//���� ����
	if (file != NULL) {
		fscanf(file, "%d ", &num);			//���ǰ��� �Է¹ޱ�
		for (int i = 0; i < num; i++) {
			fscanf(file, "%d ", &p[i]);
		}									//profit �Է¹ޱ�
		for (int i = 0; i < num; i++) {
			fscanf(file, "%d ", &w[i]);
		}									//weight �Է¹ޱ�
		fscanf(file, "%d ", &M);			//�賶ũ�� �Է¹ޱ�
	}										//���Ͽ��� �� �� �޾Ƽ� ������ �˸°� ����
	else printf("�� ����");
	fclose(file);//���� �ݱ�

	ITEM[0].p = 0;
	ITEM[0].w = 0;
	for (int i = 1; i <= num; i++) {
		ITEM[i].id = i;
		ITEM[i].p = p[i - 1];
		ITEM[i].w = w[i - 1];
	}	//�� �ε������� profit, weight �Է�

	printf("n = %d\n", num);
	printf("pi = ");
	for (int i = 0; i < num; i++) {
		printf("%d ", p[i]);
	}
	printf("\nwi = ");
	for (int i = 0; i < num; i++) {
		printf("%d ", w[i]);
	}
	printf("\npi/wi = ");
	for (int i = 0; i < num; i++) {
		printf("%.1f ", (float)p[i]/w[i]);
	}
	printf("\nM = %d\n\n", M);		//���

	insertion_sort(ITEM, num);		// pi/wi�� ������������ ����

	knapsack(0, 0, 0, ITEM);		//knapsack �˰��� ����
	for (int i = 1; i <= num; i++) {
		if (bestset[i] == 'y') {
			index[ITEM[i].id] = 1;	//�ε��� ���� ������� ����ϱ� ����
		}
	}

	printf("\nThe maximum profit is = $%d\n", maxprice);
	printf("The solution vector X = (");
	for (int i = 1; i < num; i++) {
		printf("%d, ", index[i]);
	}
	printf("%d)", index[num]);
}
bool promising(int i, int weight, item ITEM[]) {	//�ش� ������ ��������
	int j, k;
	int totweight;
	float bound;

	if (weight >= M) return false;		//weight�� M���� ũ�� F
	else {
		j = i + 1;				//���� ����
		bound = profit;
		totweight = weight;

		while (j <= num && totweight + ITEM[j].w <= M) {	//M���� ���� ������ ����
			totweight = totweight + ITEM[j].w;
			bound = bound + ITEM[j].p;
			j++;
		}
		k = j;
		if (k <= num) {		//bound�� ���
			bound = bound + (M - totweight) * (float)ITEM[k].p / ITEM[k].w;
		}
		return bound > maxprice;
	}
}
void knapsack(int i, int price, int weight, item ITEM[]) {
	if (weight <= M && price > maxprice) {	//���� ������ �ִ����ͺ��� ũ�� 
		maxprice = price;					//�ִ����Ϳ� ���� ���� ����
		numbest = i;
		for (int i = 0; i < num; i++) {
			bestset[i] = include[i];
		}									//����� ���� y, ������ ���� n
	}
	if (promising(i, weight, ITEM)) {
		include[i + 1] = 'y';		//���� ���� ����
		profit = price + ITEM[i + 1].p;
		knapsack(i + 1, price + ITEM[i + 1].p, weight + ITEM[i + 1].w, ITEM);

									//promising ��� ���ϸ�
		include[i + 1] = 'n';		//���� ���� ����X
		profit = price;
		knapsack(i + 1, price, weight, ITEM);
	}
}
void insertion_sort(item list[], int n) {	// pi/wi �������� ����(�ε���, p, w ���� ����)
	int j;
	for (int i = 2; i <= n; i++) {
		float key = (float)list[i].p/list[i].w;
		int id = list[i].id;
		int p = list[i].p;
		int w = list[i].w;
		for (j = i - 1; j >= 1 && ((float)list[j].p/list[j].w) < key; j--) {
			list[j + 1].p = list[j].p;
			list[j + 1].id = list[j].id;
			list[j + 1].w = list[j].w;
		}
		list[j + 1].id = id;
		list[j + 1].p = p;
		list[j + 1].w = w;
	}
}