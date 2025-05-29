#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {

	// 포인터 배열 선언과 사용

	char* pary[5];  // 포인터 배열 → 각 요소가 char* (문자열 주소)를 가짐
	int i;

	pary[0] = "dog";       // "dog\0"이 저장된 메모리의 주소
	pary[1] = "elephant";  // "elephant\0"
	pary[2] = "horse";
	pary[3] = "tiger";
	pary[4] = "lion";

	// 포인터 배열을 이용해 문자열 출력
	for (i = 0; i < 5; i++) {
		printf("%s\n", pary[i]);  // 각 포인터가 가리키는 문자열 출력
	}

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 2차원 배열처럼 활용하는 포인터 배열

	int ary1[4] = { 1,2,3,4 };
	int ary2[4] = { 11,12,13,14 };
	int ary3[4] = { 21,22,23,24 };

	// 포인터 배열 선언 → 각 요소는 int 배열을 가리키는 포인터
	int* pary1[3] = { ary1, ary2, ary3 };
	// pary1[0] → ary1
	// pary1[1] → ary2
	// pary1[2] → ary3
	
	// int i;
	int j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			printf("%5d", pary1[i][j]); // → *(pary1[i] + j)
		}
		printf("\n");
	}
}