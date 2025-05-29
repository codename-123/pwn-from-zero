#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc. free 함수 사용을 위한 헤더 파일

int main(void) {

    // malloc, free 함수

    // malloc(메모리 크기) → malloc는 힙(heap) 영역에 지정한 크기만큼의 메모리를 "동적으로 할당"해 주는 함수 → 이 함수는 메모리의 시작 주소(포인터)를 반환하며, 실패하면 NULL을 반환함.
    // free(포인터) → free는 malloc 등으로 "할당한 힙 메모리"를 해제하는 함수. → 사용이 끝난 메모리를 명시적으로 반환하여 메모리 누수를 방지함.
    int* pi;
    double* pd;

    // int 크기만큼 메모리 할당 (힙 영역)
    pi = (int*)malloc(sizeof(int));

    // malloc 실패 시 NULL 반환 → 실전 힙 안정성 체크
    if (pi == NULL) {
        printf("#으로 메모리가 부족합니다.\n");
        exit(1);
    }

    // double 크기만큼 메모리 할당
    pd = (double*)malloc(sizeof(double));

    // 동적 메모리에 값 저장
    *pi = 10;
    *pd = 3.4;

    // 역참조하여 힙 메모리 값 출력
    printf("정수형으로 사용: %d\n", *pi);
    printf("실수형으로 사용: %lf\n", *pd);

    // 동적 할당 영역 반환
    free(pi);
    free(pd);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 동적 할당 영역을 배열처럼 쓰기 (Heap 배열)

    int* pi1;
    int i, sum = 0;
    // int 5개 크기만큼 힙에 동적 할당 (5 * 4 = 20바이트)
    pi1 = (int*)malloc(5 * sizeof(int));

    if (pi1 == NULL) {
        // malloc 실패 시 예외 처리 (heap 영역 부족 시 발생 가능)
        printf("메모리가 부족합니다!\n");
        exit(1);
    }

    printf("다섯 명의 나이를 입력하세요: ");
    for (i = 0; i < 5; i++) {
        // 힙 메모리를 배열처럼 사용 (pi1[i] = *(pi1 + i))
        scanf("%d", &pi1[i]);
        sum += pi1[i];
    }

    // 동적 힙 메모리 사용 후 평균 출력
    printf("다섯 명의 평균 나이: %.1lf\n", (sum / 5.0));

    // 사용한 힙 메모리 해제 → 미해제 시 메모리 누수 / double free 공격에 취약
    free(pi1);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 기타 동적 할당 함수


    // calloc(요소 개수, 요소 크기) → calloc은 지정한 개수만큼 메모리를 "0으로 초기화" 하여 힙에 할당 → 힙 chunk를 predictable 하게 만드는 데 사용되며, 메모리 초기화가 보장됨
    // realloc(기존 메모리 주소, 새로운 크기) → realloc은 기존 힙 메모리 크기를 재조정하는 함수이다. → 크기를 늘리거나 줄일 수 있으며, 새로운 영역이 필요하면 주소가 바뀔 수 있음. 
    // → fake chunk, chunk split/merge 등을 활용한 힙 공격에 자주 이용됨.

    // 힙 메모리를 동적으로 확장하며 입력 받는 구조

    int* pi2;
    int size = 5;     // 초기 할당 크기
    int cnt = 0;      // 현재 입력된 값 개수
    int num;
    // int i
    
    pi2 = (int*)calloc(size, sizeof(int));
    while (1) {
        printf("양수를 입력하세요 => ");
        scanf("%d", &num);
        if (num <= 0) break;
        // 힙 공간이 꽉 찼으면, 크기를 더 크게 재할당
        if (cnt == size) {
            size += 5;
            pi2 = (int*)realloc(pi2, size * sizeof(int));
        }

        // 입력받은 숫자를 동적 배열에 저장
        pi2[cnt++] = num;
    }
    // 모든 입력된 값 출력
    for (i = 0; i < cnt; i++) {
        printf("%5d", pi2[i]);
    }

    // 힙 메모리 해제 → 미해제 시 UAF, double free 취약점 발생 가능
    free(pi2);

}