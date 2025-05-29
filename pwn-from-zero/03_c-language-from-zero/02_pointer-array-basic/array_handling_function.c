#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void print_ary(int* pa); // 배열을 포인터로 받아 출력하는 함수 선언

void print_ary2(int* pa, int size); // 배열 포인터와 크기를 받아 배열 전체를 출력하는 함수 선언

void input_ary(double* pa, int size);
double find_max(double* pa, int size);

int main(void) {

	// 배열의 값을 출력하는 함수

	int ary[5] = { 10,20,30,40,50 };

	print_ary(ary); // 배열명을 인자로 전달 → 사실상 첫 요소 주소 "&ary[0]" 전달

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 배열 요소의 개수가 다른 배열도 출력하는 함수

	int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };


	// 배열 주소와 크기를 함께 전달 → 포인터 + 길이
	print_ary2(ary1, 5);
	printf("\n");
	print_ary2(ary2, 7);

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 배열에 값을 입력하는 함수

	double db[5];
	double max;
	int size = sizeof(db) / sizeof(db[0]);

	input_ary(db, size);
	max = find_max(db, size);
	printf("배열의 최댓값: %.1f\n", max);

}

void print_ary(int* pa) {	// 배열을 포인터로 받아 출력하는 함수
	int i;

	for (i = 0; i < 5; i++) {
		printf("%d  ", pa[i]); // == *(pa + i) → 배열 순회하며 값 출력
	}
}

void print_ary2(int* pa, int size) {  // 배열 포인터와 크기를 받아 배열 전체를 출력하는 함수
	int i;

	for (i = 0; i < size; i++) {
		printf("%d  ", pa[i]); // == *(pa + i) → 배열 순회하며 값 출력
	}
}

void input_ary(double* pa, int size) { // [입력 함수] - 배열 주소와 크기를 받아, 배열에 사용자 입력값 저장
	int i;

	printf("%d개의 실수값 입력: ", size);
	for (i = 0; i < size; i++) {
		scanf("%lf", pa + i);   // pa + i → i번째 요소 주소 → 값 입력 (역참조 안 쓰고 직접 주소)
								// == &pa[i]
	}
}

double find_max(double* pa, int size) { // [최댓값 탐색 함수] - 포인터로 배열 접근, 반복하며 최대값 계산
	double max;
	int i;

	max = pa[0];	 // 배열 첫 값으로 초기화 "== *(pa + 0)"
	for (i = 0; i < size; i++) {
		if (pa[i] > max)	// pa[i] == *(pa + i) → 현재 값이 max보다 크면 갱신
			max = pa[i];
	}

	return max;    // 최종 최대값 반환

}