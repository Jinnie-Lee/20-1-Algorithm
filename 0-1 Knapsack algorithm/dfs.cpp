#define _CRT_SECURE_NO_WARNINGS	
#define MAX 40
#include <stdio.h>

struct item {
	int id;
	int w;
	int p;
};	//인덱스, weight, profit 담는 구조체 생성

void insertion_sort(item[], int);
bool promising(int, int, item[]);
void knapsack(int, int, int, item[]);

int maxprice, num, M, profit;
int numbest = 0;	//고려한 것들 개수
char bestset[MAX];	//최대 이익일 때 선택한 것들
char include[MAX];	//현재 선택한 것

int main(void) {
	item ITEM[MAX];

	int p[MAX];				//이윤
	int w[MAX];				//무게
	int index[MAX] = { 0 };	//해 백터 원래 인덱스 순서로

	FILE* file = fopen("p2data6.txt", "r");	//파일 열기
	if (file != NULL) {
		fscanf(file, "%d ", &num);			//물건개수 입력받기
		for (int i = 0; i < num; i++) {
			fscanf(file, "%d ", &p[i]);
		}									//profit 입력받기
		for (int i = 0; i < num; i++) {
			fscanf(file, "%d ", &w[i]);
		}									//weight 입력받기
		fscanf(file, "%d ", &M);			//배낭크기 입력받기
	}										//파일에서 각 값 받아서 변수에 알맞게 저장
	else printf("안 열림");
	fclose(file);//파일 닫기

	ITEM[0].p = 0;
	ITEM[0].w = 0;
	for (int i = 1; i <= num; i++) {
		ITEM[i].id = i;
		ITEM[i].p = p[i - 1];
		ITEM[i].w = w[i - 1];
	}	//각 인덱스별로 profit, weight 입력

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
	printf("\nM = %d\n\n", M);		//출력

	insertion_sort(ITEM, num);		// pi/wi를 내림차순으로 정렬

	knapsack(0, 0, 0, ITEM);		//knapsack 알고리즘 실행
	for (int i = 1; i <= num; i++) {
		if (bestset[i] == 'y') {
			index[ITEM[i].id] = 1;	//인덱스 원래 순서대로 출력하기 위해
		}
	}

	printf("\nThe maximum profit is = $%d\n", maxprice);
	printf("The solution vector X = (");
	for (int i = 1; i < num; i++) {
		printf("%d, ", index[i]);
	}
	printf("%d)", index[num]);
}
bool promising(int i, int weight, item ITEM[]) {	//해당 물건이 유망한지
	int j, k;
	int totweight;
	float bound;

	if (weight >= M) return false;		//weight가 M보다 크면 F
	else {
		j = i + 1;				//다음 물건
		bound = profit;
		totweight = weight;

		while (j <= num && totweight + ITEM[j].w <= M) {	//M보다 작을 때까지 포함
			totweight = totweight + ITEM[j].w;
			bound = bound + ITEM[j].p;
			j++;
		}
		k = j;
		if (k <= num) {		//bound값 계산
			bound = bound + (M - totweight) * (float)ITEM[k].p / ITEM[k].w;
		}
		return bound > maxprice;
	}
}
void knapsack(int i, int price, int weight, item ITEM[]) {
	if (weight <= M && price > maxprice) {	//현재 이익이 최대이익보다 크면 
		maxprice = price;					//최대이익에 현재 이익 저장
		numbest = i;
		for (int i = 0; i < num; i++) {
			bestset[i] = include[i];
		}									//사용한 물건 y, 사용안한 물건 n
	}
	if (promising(i, weight, ITEM)) {
		include[i + 1] = 'y';		//다음 물건 포함
		profit = price + ITEM[i + 1].p;
		knapsack(i + 1, price + ITEM[i + 1].p, weight + ITEM[i + 1].w, ITEM);

									//promising 통과 못하면
		include[i + 1] = 'n';		//다음 물건 포함X
		profit = price;
		knapsack(i + 1, price, weight, ITEM);
	}
}
void insertion_sort(item list[], int n) {	// pi/wi 내림차순 정렬(인덱스, p, w 같이 정렬)
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