#include <stdio.h>

void swap_ptr(char** ppa, char** ppb);

void print_str(char** pps, int cnt);

void print_ary(int(*pa)[4]);

/* 간략 정리

int* p;        // int 하나를 가리키는 포인터
int(*p)[4];   // int 4개짜리 배열을 가리키는 포인터
int** pp;      // int*를 가리키는 포인터 (이중 포인터)

*/
int main(void) {

    // 2중 포인터 개념 (🔥매우 중요!)

    int a = 10;       // 일반 변수 → 실제 값(10)을 메모리에 저장
    int* pi;          // 포인터 선언 → 정수(int)를 가리키는 포인터
    int** ppi;        // 이중 포인터 선언 → int*를 가리킴 (즉, 포인터의 주소 저장)

    pi = &a;          // pi는 a의 주소를 저장 → pi는 "a를 가리킴"
    ppi = &pi;        // ppi는 pi의 주소를 저장 → ppi는 "pi를 가리킴"

    printf("--------------------------------------------------\n");
    printf("변수   변수값      &연산       *연산        **연산\n");
    printf("--------------------------------------------------\n");

    printf("a    %10d  %10u\n", a, &a);  // a의 값과 주소
    printf("pi   %10u  %10u  %10d\n", pi, &pi, *pi);
    // pi: a의 주소, &pi: pi 자신의 주소, *pi: a의 값

    printf("ppi  %10u  %10u  %10u %10u\n", ppi, &ppi, *ppi, **ppi);
    // ppi: pi의 주소, &ppi: ppi 자신의 주소, *ppi: pi의 값 (즉, a의 주소)

    printf("--------------------------------------------------\n");

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 2중 포인터 활용 예

    char* pa = "success";   // pa는 문자열 "success"의 주소를 가리킴
    char* pb = "failure";   // pb는 "failure"의 주소를 가리킴

    printf("pa -> %s, pb -> %s\n", pa, pb);
    swap_ptr(&pa, &pb);     // pa, pb의 주소(즉 char**)를 swap_ptr에 넘김
    printf("pa -> %s, pb -> %s\n", pa, pb);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 2중 포인터 활용 예 2

    // 문자열 주소들을 담은 포인터 배열 (즉, char*[])
    char* ptr_ary[] = { "eagle", "tiger", "lion", "squirrel" };

    int count;
    // 배열 크기 계산 (문자열 개수)
    count = sizeof(ptr_ary) / sizeof(ptr_ary[0]);

    // 포인터 배열의 시작 주소 전달 (char** 형태로)
    // → argv, 환경변수 등 실전 인자 전달과 동일 구조
    print_str(ptr_ary, count);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 배열 요소의 주소와 배열의 주소

    int ary[5];

    // ary: 배열 이름 → 첫 요소의 주소 (즉, &ary[0])
    printf("ary의 값: %u\n", ary);

    // &ary: 배열 전체의 주소 → 타입은 int(*)[5]
    printf("ary의 주소: %u\n", &ary);

    // ary + 1: 다음 int 요소 주소 → +4 바이트 이동 (int 크기만큼)
    printf("ary + 1: %u\n", ary + 1);

    // &ary + 1: 배열 전체 크기만큼 이동 → +20 바이트 이동 (int[5])
    // GDB에서 구조 해석 시 혼동 주의
    printf("&ary + 1: %u\n", &ary + 1);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 2차원 배열과 배열 포인터

    // 2차원 배열 선언 (3행 4열, 총 12개 int)
    int ary1[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };

    // 배열 포인터 선언: pa1은 int[4] 배열을 가리킴
    // → 즉, pa1은 ary1[i] 하나(=int[4])씩 접근 가능
    int(*pa1)[4];

    int i, j;

    // 배열 이름은 첫 행의 주소로 decay됨 → pa1 = &ary1[0]
    pa1 = ary1;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            // pa1[i][j]는 ary1[i][j]와 동일
            // → 실제 메모리 주소: *( *(pa1 + i) + j )
            // → 2차원 배열의 내부 메모리 구조 해석에 필수 (GDB, BOF 등)
            printf("%5d", pa1[i][j]);
        }
        printf("\n");
    }

    printf("\n\n"); //-----------------------------------------------------------------------------

    /* 2차원 배열의 값을 출력하는 함수 */
    
    int ary2[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };

    // 배열 이름 → 첫 번째 행의 주소 (int(*)[4]) 로 decay됨
    print_ary(ary2);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void swap_ptr(char** ppa, char** ppb) {

    // ppa: pa의 주소 → 즉, char*를 가리키는 포인터 (char**)
    // ppb: pb의 주소 → 마찬가지로 char**

    char* pt;  // 임시 저장용 포인터 (스왑할 때 잠시 보관)

    pt = *ppa;     // pa의 값(= "success"의 주소)을 임시 저장
    // *ppa → pa → "success"

    *ppa = *ppb;   // pa에 pb의 값(= "failure" 주소) 대입
    // 이제 pa는 "failure"를 가리킴

    *ppb = pt;     // pb에 원래 pa가 가리키던 "success" 대입
    // 이제 pb는 "success"를 가리킴

// 결과적으로 pa ↔ pb 가 서로 가리키는 문자열 주소를 바꾼 셈
}

void print_str(char** pps, int cnt) {
    int i;
    for (i = 0; i < cnt; i++) {
        // pps[i]는 각 문자열의 주소 → *pps + i
        // → 포인터 배열 구조 해석에 필수 (GDB, argv 등)
        printf("%s\n", pps[i]);
    }
}

void print_ary(int(*pa)[4]) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            // pa[i][j] = *( *(pa + i) + j )
            // → 2차원 배열의 실제 메모리 구조를 따라 접근
            // → 디버깅, 메모리 해킹 시 내부 해석에 필수
            printf("%5d", pa[i][j]);
        }
        printf("\n");
    }
}