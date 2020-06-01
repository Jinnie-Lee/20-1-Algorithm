#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000
#define swap(a, b) {double t; t=a; a=b; b=t;}

void merge(double[], int, int, int);		//�����ϱ�
void mergesort(double[], int, int);			//��������

void quicksort(double[], int, int);			//������
int partition(double[], int, int);			//����

int rand_partition(double[], int, int);		//����������
void rand_quicksort(double[], int, int);	//����


double sorted[MAX_SIZE] = { 0 };				//mergesort�� �� ����ϴ� �ӽ� �迭
double list_merge[MAX_SIZE] = { 0 };			//mergesort�� �� ����� �迭
double list_quick[MAX_SIZE] = { 0 };			//quicksort�� �� ����� �迭
double list_random[MAX_SIZE] = { 0 };			//random quicksort �� �� ����� �迭

int cnt1 = 0, cnt2 = 0, cnt3 = 0;			//��Ƚ�� ���� ����

int main(void) {
	char filename[10][20] = { "1000(1).txt", "1000(2).txt", "5000(1).txt", "5000(2).txt", "10000(1).txt", "10000(2).txt",
							"50000(1).txt", "50000(2).txt", "100000(1).txt", "100000(2).txt", };
	int num = 0;							//������ ���� ���� ����
	double temp = 0;						//������ �ӽ÷� ���� ����

	clock_t start1, end1, start2, end2, start3, end3;	//ms�� ǥ��
	double result1, result2, result3;					//����ð� ���� ����

	FILE* file = fopen(filename[0], "r");	//���� �б�
	if (file != NULL) {
		fscanf(file, "%d ", &num);
		for (int i = 0; i < num; i++) {
			fscanf(file, "%lf ", &temp);
			list_merge[i] = temp;
			list_quick[i] = temp;
			list_random[i] = temp;
		}									//���� �о� ������ ������ num�� �����͵��� �迭�� �ֱ�
	}
	else printf("���� �� ����");
	fclose(file);


	printf("n = %d �� ���� ������\n\n", num);
	/*printf("n = %d �� ������ ������\n\n", num);*/

	printf("< �������� >\n");
	start1 = clock();
	mergesort(list_merge, 0, num - 1);			//�������� ����
	end1 = clock();
	result1 = ((double)end1 - start1);

	for (int i = 0; i < 10; i++) {				//�յ� 10�� ���
		printf("%.4f  ", list_merge[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_merge[i]);
	}
	printf("\n����ð� = %lf\n", result1);
	printf("����Ƚ�� = %d\n\n", cnt1);


	printf("< ���������� >\n");
	start3 = clock();
	rand_quicksort(list_random, 0, num - 1);	//���������� ����
	end3 = clock();
	result3 = ((double)end3 - start3);

	for (int i = 0; i < 10; i++) {				//�յ� 10�� ���
		printf("%.4f  ", list_random[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_random[i]);
	}
	printf("\n����ð� = %lf\n", result3);
	printf("����Ƚ�� = %d\n\n", cnt3);			//�����̱� ������ ������ ������ �ٸ�


	
	printf("< ������ >\n");
	start2 = clock();
	quicksort(list_quick, 0, num - 1);			//������ ����
	end2 = clock();
	result2 = ((double)end2- start2);

	for (int i = 0; i < 10; i++) {				//�յ� 10�� ���
		printf("%.4f  ", list_quick[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_quick[i]);
	}
	printf("\n����ð� = %lf\n", result2);
	printf("����Ƚ�� = %d\n\n", cnt2);
}

void merge(double list[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {		//���� ���ĵ� list �����ϱ�
		cnt1 += 1;
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}

	cnt1 += 1;
	if (i > mid)							//�����ִ� ������ sorted�� ����
		for (int l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (int l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (int l = left; l <= right; l++)		//���ĵ� ������ list �迭�� ����
		list[l] = sorted[l];
}
void mergesort(double list[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergesort(list, left, mid);
		mergesort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(double list[], int left, int right) {
	double pivot;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];						//pivot = list�� ���� ���� ����
	do {
		do {
			low++;
			cnt2 += 1;
		} while (list[low] < pivot);
		do {
			high--;
			cnt2 += 1;
		} while (list[high] > pivot);
		if (low < high) swap(list[low], list[high]);	//low, high �� �� while�� ������ swap
	} while (low < high);					//low�� high�� ���� ����ĥ ������ �ݺ�

	swap(list[left], list[high]);			//pivot�� high ���Ұ� swap
	return high;
}
void quicksort(double list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quicksort(list, left, q - 1);
		quicksort(list, q + 1, right);
	}
}

int rand_partition(double list[], int left, int right) {
	srand(time(NULL));
	double pivot;
	int low, high;
	int rand_num = rand() % (right - left + 1) + left;		//left~right ������ ���� ����

	low = left;
	high = right + 1;
	pivot = list[rand_num];				//������ �ε����� �ϴ� �迭 �� = pivot

	swap(list[rand_num], list[left]);	//������ �ϱ� ���� ���� ���Ĺ�İ� �����ϰ� �ϱ� ���� list[left]���� swap
	do {
		do {
			low++;
			cnt3 += 1;
		} while (list[low] < pivot);
		do {
			high--;
			cnt3 += 1;
		} while (list[high] > pivot);
		if (low < high) swap(list[low], list[high]);
	} while (low < high);

	swap(list[left], list[high]);
	return high;
}
void rand_quicksort(double list[], int left, int right) {
	if (left < right) {
		int q = rand_partition(list, left, right);
		rand_quicksort(list, left, q - 1);
		rand_quicksort(list, q + 1, right);
	}
}