#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str(char** ps);

int main(void) {

	// 동적 할당을 사용한 문자열 처리

    // 임시 입력용 버퍼 (스택 영역, 고정 크기)
    char temp[80];

    // 문자열 3개를 가리킬 포인터 배열 (str[0] ~ str[2])
    char* str[3];

    int i;

    for (i = 0; i < 3; i++) {
        printf("문자열을 입력하세요: ");

        // [!] gets()는 버퍼 크기 제한이 없어서 버퍼 오버플로우 취약점 발생 가능
        // BOF, RET overwrite, 스택 깨짐 등 실전 해킹에 자주 나옴
        gets(temp);

        // 입력받은 문자열 크기 + 1만큼 동적 메모리 할당 (널 문자 포함)
        str[i] = (char*)malloc(strlen(temp) + 1);

        // 입력한 문자열을 힙 영역으로 복사 → strcpy도 취약 함수 (길이 제한 없음)
        strcpy(str[i], temp);
    }

    // 저장된 문자열 출력
    for (i = 0; i < 3; i++) {
        printf("%s\n", str[i]);
    }

    // 동적 할당된 힙 메모리 해제 (메모리 누수 방지)
    for (i = 0; i < 3; i++) {
        free(str[i]);
    }

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 동적 할당 영역에 저장한 문자열을 함수로 처리하는 예

    char temp1[80];        // 임시 입력 버퍼 (스택 영역)
    char* str1[21] = { 0 };  // 문자열 주소를 담는 포인터 배열 (최대 20개 + NULL)
    int j = 0;

    while (j < 20) {                               // 최대 20개 문자열 입력
        printf("문자열을 입력하세요: ");
        gets(temp1);                                // [i] BOF 발생 가능 (길이 제한 없음)

        if (strcmp(temp1, "end") == 0) break;       // "end" 입력 시 종료

        str1[j] = (char*)malloc(strlen(temp1) + 1);  // 입력 크기만큼 힙 메모리 할당
        strcpy(str1[j], temp1);                      // 입력 복사 (strcpy = BOF 가능성)
        j++;
    }

    print_str(str1);  // 이중 포인터로 문자열 리스트 전달 → 함수에서 접근

    for (j = 0; str1[j] != NULL; j++) {
        free(str1[j]); // 동적으로 할당한 메모리 해제 → 미해제 시 메모리 누수
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_str(char** ps) { // 이중 포인터를 받아 문자열들을 출력하는 함수

    while (*ps != NULL) {                 // ps는 포인터 배열의 요소를 가리킴
        printf("%s\n", *ps);              // 각 문자열 출력
        ps++;                             // 다음 포인터로 이동
    }
}
