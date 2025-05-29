#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str(char**);

int main(int argc, char** argv) {

	// argc: 명령행 인자의 개수 (실행 파일 이름도 포함됨)
	// argv: 명령행 인자들을 문자열로 담고 있는 포인터 배열
	// → argv[0] = 실행 경로, argv[1]부터는 사용자 입력 인자

	// main 함수의 명령행 인수 사용

	int i;

	for (i = 0; i < argc; i++) {
		// 사용자가 입력한 명령행 인자를 출력
		// → 시스템 해킹에서는 argv[1]을 이용해 입력값 전달 후 BOF 유도 가능
		// → 예: strcpy(buf, argv[1]); → argv[1]을 통해 스택 오버플로우 발생
		printf("%s\n", argv[i]);
	}

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 명령행 인수를 사용한 문자열 입력 예

	char temp[80];              // 스택 버퍼 → gets()로 BOF 발생 가능
	char** str;                 // 문자열 포인터 배열 → 힙에 저장됨
	int max;
	// int i;

	if (argc < 2) {
		printf("사용법: %s [최대 문자열 개수]\n", argv[0]);
		return 1;
	}

	max = atoi(argv[1]);        // 사용자 입력 기반 → 취약점 트리거 가능
	str = malloc((max + 1) * sizeof(char*));  // 포인터 테이블 → 덮기 대상 될 수 있음

	int i = 0;
	while (1) {
		gets(temp);             // [!] BOF (길이 제한 없음)
		if (temp[0] == '\0') break;

		str[i] = malloc(strlen(temp) + 1);  // 입력 기반 힙 chunk 할당
		strcpy(str[i], temp);              // [!] 힙 오버플로우 발생 가능
		i++;

		if (i == max) break;
	}
	str[i] = 0;
	print_str(str);             // 포인터 테이블을 함수에 전달 → 익스플로잇 활용 가능

	i = 0;
	while (str[i]) free(str[i++]); // 미해제 시 UAF 위험
	free(str);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_str(char** ps) {
	
	while (*ps != 0) {
		printf("%s\n", *ps);  // 포인터 테이블 순회 → 덮히면 악성 주소 실행 가능
		ps++;
	}
}