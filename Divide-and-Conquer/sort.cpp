#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100000
#define swap(a, b) {double t; t=a; a=b; b=t;}

void merge(double[], int, int, int);		//병합하기
void mergesort(double[], int, int);			//병합정렬

void quicksort(double[], int, int);			//퀵정렬
int partition(double[], int, int);			//분할

int rand_partition(double[], int, int);		//랜덤퀵정렬
void rand_quicksort(double[], int, int);	//분할


double sorted[MAX_SIZE] = { 0 };				//mergesort할 때 사용하는 임시 배열
double list_merge[MAX_SIZE] = { 0 };			//mergesort할 때 사용할 배열
double list_quick[MAX_SIZE] = { 0 };			//quicksort할 때 사용할 배열
double list_random[MAX_SIZE] = { 0 };			//random quicksort 할 때 사용할 배열

int cnt1 = 0, cnt2 = 0, cnt3 = 0;			//비교횟수 넣을 변수

int main(void) {
	char filename[10][20] = { "1000(1).txt", "1000(2).txt", "5000(1).txt", "5000(2).txt", "10000(1).txt", "10000(2).txt",
							"50000(1).txt", "50000(2).txt", "100000(1).txt", "100000(2).txt", };
	int num = 0;							//데이터 개수 넣을 변수
	double temp = 0;						//데이터 임시로 받을 변수

	clock_t start1, end1, start2, end2, start3, end3;	//ms로 표시
	double result1, result2, result3;					//수행시간 넣을 변수

	FILE* file = fopen(filename[0], "r");	//파일 읽기
	if (file != NULL) {
		fscanf(file, "%d ", &num);
		for (int i = 0; i < num; i++) {
			fscanf(file, "%lf ", &temp);
			list_merge[i] = temp;
			list_quick[i] = temp;
			list_random[i] = temp;
		}									//파일 읽어 데이터 개수는 num에 데이터들은 배열에 넣기
	}
	else printf("파일 안 열림");
	fclose(file);


	printf("n = %d 인 랜덤 데이터\n\n", num);
	/*printf("n = %d 인 역정렬 데이터\n\n", num);*/

	printf("< 병합정렬 >\n");
	start1 = clock();
	mergesort(list_merge, 0, num - 1);			//병합정렬 실행
	end1 = clock();
	result1 = ((double)end1 - start1);

	for (int i = 0; i < 10; i++) {				//앞뒤 10개 출력
		printf("%.4f  ", list_merge[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_merge[i]);
	}
	printf("\n수행시간 = %lf\n", result1);
	printf("수행횟수 = %d\n\n", cnt1);


	printf("< 랜덤퀵정렬 >\n");
	start3 = clock();
	rand_quicksort(list_random, 0, num - 1);	//랜덤퀵정렬 실행
	end3 = clock();
	result3 = ((double)end3 - start3);

	for (int i = 0; i < 10; i++) {				//앞뒤 10개 출력
		printf("%.4f  ", list_random[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_random[i]);
	}
	printf("\n수행시간 = %lf\n", result3);
	printf("수행횟수 = %d\n\n", cnt3);			//랜덤이기 때문에 실행할 때마다 다름


	
	printf("< 퀵정렬 >\n");
	start2 = clock();
	quicksort(list_quick, 0, num - 1);			//퀵정렬 실행
	end2 = clock();
	result2 = ((double)end2- start2);

	for (int i = 0; i < 10; i++) {				//앞뒤 10개 출력
		printf("%.4f  ", list_quick[i]);
	}
	printf("\n...\n");
	for (int i = num - 10; i < num; i++) {
		printf("%.4f  ", list_quick[i]);
	}
	printf("\n수행시간 = %lf\n", result2);
	printf("수행횟수 = %d\n\n", cnt2);
}

void merge(double list[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;

	while (i <= mid && j <= right) {		//분할 정렬된 list 병합하기
		cnt1 += 1;
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}

	cnt1 += 1;
	if (i > mid)							//남아있는 데이터 sorted로 복사
		for (int l = j; l <= right; l++)
			sorted[k++] = list[l];
	else
		for (int l = i; l <= mid; l++)
			sorted[k++] = list[l];

	for (int l = left; l <= right; l++)		//정렬된 데이터 list 배열로 복사
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
	pivot = list[left];						//pivot = list의 가장 왼쪽 원소
	do {
		do {
			low++;
			cnt2 += 1;
		} while (list[low] < pivot);
		do {
			high--;
			cnt2 += 1;
		} while (list[high] > pivot);
		if (low < high) swap(list[low], list[high]);	//low, high 둘 다 while문 나오면 swap
	} while (low < high);					//low와 high가 서로 지나칠 때까지 반복

	swap(list[left], list[high]);			//pivot과 high 원소값 swap
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
	int rand_num = rand() % (right - left + 1) + left;		//left~right 사이의 난수 생성

	low = left;
	high = right + 1;
	pivot = list[rand_num];				//난수를 인덱스로 하는 배열 값 = pivot

	swap(list[rand_num], list[left]);	//정렬을 하기 전에 기존 정렬방식과 동일하게 하기 위해 list[left]값과 swap
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