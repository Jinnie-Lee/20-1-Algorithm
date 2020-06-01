#define _CRT_SECURE_NO_WARNINGS
#define swap(a, b) {double t; t=a; a=b; b=t;}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void makefile(char*, int);
void reverse(char*, int);

int main(void) {
	int num[5] = {1000, 5000, 10000, 50000, 100000};
	char file[10][20] = {"1000(1).txt", "1000(2).txt", "5000(1).txt", "5000(2).txt", "10000(1).txt", "10000(2).txt", 
						"50000(1).txt", "50000(2).txt", "100000(1).txt", "100000(2).txt", };

	for (int i = 0; i < 5; i++) {
		makefile(file[2*i], num[i]);					//���� ���� ���� ���� ����
		reverse(file[2*i + 1], num[i]);					//�����ĵ� ���� ���� ���� ����
	}
}
void makefile(char*filename, int num) {	
	srand(time(NULL));									//���� �ð� ���� �ҷ��� seed�� �ʱ�ȭ
	FILE* f;
	f = fopen(filename, "w");
	if (f == NULL) {
		printf("���Ͽ��½���");
		exit(1);
	}
	fprintf(f, "%d\n", num);
	for (int i = 0; i < num; i++) {
		fprintf(f, "%.4f ", (double)rand() / RAND_MAX * 1000);//0~1000������ ������ �����Ѵ�.
	}
	fclose(f);
}
void reverse(char*filename, int num) {					//�������� ����
	srand(time(NULL));
	double random[100000] = { 0 };

	for (int i = 0; i < num; i++) {						//���� ����
		random[i] = (double)rand() / RAND_MAX * 1000;
	}
	for (int i = 0; i < num; i++) {						//�迭 ������ �̿��� ���������ϱ�
		for (int j = i + 1; j < num; j++) {
			if (*(random + i) < *(random + j)) {
				swap(*(random + i), *(random + j));
			}
		}
	}

	FILE* f;
	f = fopen(filename, "w");
	if (f == NULL) {
		printf("���Ͽ��½���");
		exit(1);
	}
	fprintf(f, "%d\n", num);
	for (int i = 0; i < num; i++) {
		fprintf(f, "%.4f ", random[i]);
	}
	fclose(f);											//������ ������ ���Ϸ� ����
}