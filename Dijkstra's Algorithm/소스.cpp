#define _CRT_SECURE_NO_WARNINGS	
#define MAX_VERTICES 100
#define True 1
#define False 0
#define INF 9999
#include <stdio.h>
#include <limits.h>

int distance[MAX_VERTICES];//최단경로 거리
int found[MAX_VERTICES];//방문한 정점 표시
int weight[MAX_VERTICES][MAX_VERTICES];//가중치 인접 행렬

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 1; i <= n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}//거리가 가장 작은 정점 인덱스 반환
void shortest_path(int start, int n) {
	int i, u, w;
	for (i = 1; i <= n; i++) {//초기화
		distance[i] = weight[start][i];
		found[i] = False;
	}
	found[start] = True;//시작정점 방문 표시
	distance[start] = 0;

	for (i = 0; i < n - 1; i++) {
		u = choose(distance, n, found);//가장 가까운 u찾기
		found[u] = True;
		for (w = 1; w <= n; w++) {//u에 인접한 w들의 distance 재계산
			if (!found[w]) {
				if (distance[u] + weight[u][w] < distance[w]) {
					distance[w] = distance[u] + weight[u][w];
				}
			}
		}
	}
}
void init(int weight[][100], int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			weight[i][j] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		weight[i][i] = 0;
	}
}//weight 이차원배열 초기화

int main(void) {
	int n, m;
	int a, b, c;

	FILE* file = fopen("graph6.txt", "r");//파일 열기
	if (file != NULL) {
		fscanf(file, "%d %d ", &n, &m);//n과 m 입력받기
		init(weight, n);
		for (int i = 0; i < m; i++) {
			fscanf(file, "%d %d %d ", &a, &b, &c);
			weight[a][b] = c;//파일에서 받은 위치를 인덱스로 가지는 배열에 가중치값 저장
		}
	}//파일에서 각 정수 받아서 변수에 알맞게 저장
	else printf("안 열림");
	fclose(file);//파일 닫기

	printf("graph6.txt\n");
	printf(" Adjacency matrix\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("  %d\t", weight[i][j]);
		}
		printf("\n");
	}//matrix 출력하기

	for (int i = 1; i <= n; i++) {
		printf("\nShortest paths from v%d = (", i);
		shortest_path(i, n);//최단경로
		for (int i = 1; i < n; i++) {
			printf("%d, ", distance[i]);
		}
		printf("%d)", distance[n]);//최단경로 출력하기
	}//정점의 개수만큼 반복하며 출력
}