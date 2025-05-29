#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print_ary(int* pa); // �迭�� �����ͷ� �޾� ����ϴ� �Լ� ����

void print_ary2(int* pa, int size); // �迭 �����Ϳ� ũ�⸦ �޾� �迭 ��ü�� ����ϴ� �Լ� ����

void input_ary(double* pa, int size);
double find_max(double* pa, int size);

int main(void) {

	// �迭�� ���� ����ϴ� �Լ�

	int ary[5] = { 10,20,30,40,50 };

	print_ary(ary); // �迭���� ���ڷ� ���� �� ��ǻ� ù ��� �ּ� "&ary[0]" ����

	printf("\n\n"); //--------------------------------------------------------------------------------

	// �迭 ����� ������ �ٸ� �迭�� ����ϴ� �Լ�

	int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };


	// �迭 �ּҿ� ũ�⸦ �Բ� ���� �� ������ + ����
	print_ary2(ary1, 5);
	printf("\n");
	print_ary2(ary2, 7);

	printf("\n\n"); //--------------------------------------------------------------------------------

	// �迭�� ���� �Է��ϴ� �Լ�

	double db[5];
	double max;
	int size = sizeof(db) / sizeof(db[0]);

	input_ary(db, size);
	max = find_max(db, size);
	printf("�迭�� �ִ�: %.1f\n", max);

}

void print_ary(int* pa) {	// �迭�� �����ͷ� �޾� ����ϴ� �Լ�
	int i;

	for (i = 0; i < 5; i++) {
		printf("%d  ", pa[i]); // == *(pa + i) �� �迭 ��ȸ�ϸ� �� ���
	}
}

void print_ary2(int* pa, int size) {  // �迭 �����Ϳ� ũ�⸦ �޾� �迭 ��ü�� ����ϴ� �Լ�
	int i;

	for (i = 0; i < size; i++) {
		printf("%d  ", pa[i]); // == *(pa + i) �� �迭 ��ȸ�ϸ� �� ���
	}
}

void input_ary(double* pa, int size) { // [�Է� �Լ�] - �迭 �ּҿ� ũ�⸦ �޾�, �迭�� ����� �Է°� ����
	int i;

	printf("%d���� �Ǽ��� �Է�: ", size);
	for (i = 0; i < size; i++) {
		scanf("%lf", pa + i);   // pa + i �� i��° ��� �ּ� �� �� �Է� (������ �� ���� ���� �ּ�)
								// == &pa[i]
	}
}

double find_max(double* pa, int size) { // [�ִ� Ž�� �Լ�] - �����ͷ� �迭 ����, �ݺ��ϸ� �ִ밪 ���
	double max;
	int i;

	max = pa[0];	 // �迭 ù ������ �ʱ�ȭ "== *(pa + 0)"
	for (i = 0; i < size; i++) {
		if (pa[i] > max)	// pa[i] == *(pa + i) �� ���� ���� max���� ũ�� ����
			max = pa[i];
	}

	return max;    // ���� �ִ밪 ��ȯ

}