#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int sum1(int, int);

// 함수 프로토타입 선언
void func(int (*pf)(int, int));
int sum(int a, int b);
int mul(int a, int b);
int max(int a, int b);

int main(void) {

    // 함수 포인터의 개념

    // 함수 포인터 선언: fp는 (int, int) → int 함수의 주소를 저장할 수 있음
    int (*fp)(int, int);
    int res;

    // 함수 포인터에 sum 함수 주소 대입 (sum은 함수 이름 = 주소)
    fp = sum1;

    // 함수 포인터를 통해 sum 실행 → 제어 흐름을 포인터로 조작
    // 시스템 해킹에서 흐름 탈취(RCE) 시 공격 포인트가 되는 구조
    res = fp(10, 20);

    printf("result: %d\n", res);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 함수 포인터의 활용

    int sel;

    printf("1. 덧셈  2. 곱셈  3. 큰 수 출력\n선택: ");
    scanf("%d", &sel);

    switch (sel) {
    case 1: func(sum); break;   // 함수 주소 전달
    case 2: func(mul); break;
    case 3: func(max); break;
    default: break;
    }

    printf("\n\n"); //-----------------------------------------------------------------------------

    // void 포인터 → void 포인터는 어떤 타입의 주소든 저장 가능 (범용 포인터)

    int a = 10;
    double b = 3.5;
    void* vp; // 타입이 없는 포인터 → int*, double*, char* 모두 가능

    vp = &a;
    // void*는 직접 역참조 불가 → 반드시 형변환 필요
    // int형 주소로 변환 후 역참조 → 힙/구조체 조작 시 자주 사용
    printf("a: %d\n", *(int*)vp);

    vp = &b;
    // double형 주소로 변환 후 역참조 → 메모리 분석/해킹 시 캐스팅 필요
    printf("b: %.1f\n", *(double*)vp);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// 일반 함수 정의
int sum1(int a, int b) { return (a + b); }

// 함수 포인터를 이용해 함수 실행
void func(int (*pf)(int, int)) {
    int a, b, res;

    printf("두 정수를 입력하세요: ");
    scanf("%d %d", &a, &b);

    res = pf(a, b);  // 전달된 함수 실행 (sum, mul, max 중 하나)
    printf("결과: %d\n", res);
}

// 연산 함수들
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int max(int a, int b) { return (a > b) ? a : b; }