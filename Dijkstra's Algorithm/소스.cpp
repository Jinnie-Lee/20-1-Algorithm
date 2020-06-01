#define _CRT_SECURE_NO_WARNINGS	
#define MAX_VERTICES 100
#define True 1
#define False 0
#define INF 9999
#include <stdio.h>
#include <limits.h>

int distance[MAX_VERTICES];//�ִܰ�� �Ÿ�
int found[MAX_VERTICES];//�湮�� ���� ǥ��
int weight[MAX_VERTICES][MAX_VERTICES];//����ġ ���� ���

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
}//�Ÿ��� ���� ���� ���� �ε��� ��ȯ
void shortest_path(int start, int n) {
	int i, u, w;
	for (i = 1; i <= n; i++) {//�ʱ�ȭ
		distance[i] = weight[start][i];
		found[i] = False;
	}
	found[start] = True;//�������� �湮 ǥ��
	distance[start] = 0;

	for (i = 0; i < n - 1; i++) {
		u = choose(distance, n, found);//���� ����� uã��
		found[u] = True;
		for (w = 1; w <= n; w++) {//u�� ������ w���� distance ����
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
}//weight �������迭 �ʱ�ȭ

int main(void) {
	int n, m;
	int a, b, c;

	FILE* file = fopen("graph6.txt", "r");//���� ����
	if (file != NULL) {
		fscanf(file, "%d %d ", &n, &m);//n�� m �Է¹ޱ�
		init(weight, n);
		for (int i = 0; i < m; i++) {
			fscanf(file, "%d %d %d ", &a, &b, &c);
			weight[a][b] = c;//���Ͽ��� ���� ��ġ�� �ε����� ������ �迭�� ����ġ�� ����
		}
	}//���Ͽ��� �� ���� �޾Ƽ� ������ �˸°� ����
	else printf("�� ����");
	fclose(file);//���� �ݱ�

	printf("graph6.txt\n");
	printf(" Adjacency matrix\n");
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("  %d\t", weight[i][j]);
		}
		printf("\n");
	}//matrix ����ϱ�

	for (int i = 1; i <= n; i++) {
		printf("\nShortest paths from v%d = (", i);
		shortest_path(i, n);//�ִܰ��
		for (int i = 1; i < n; i++) {
			printf("%d, ", distance[i]);
		}
		printf("%d)", distance[n]);//�ִܰ�� ����ϱ�
	}//������ ������ŭ �ݺ��ϸ� ���
}