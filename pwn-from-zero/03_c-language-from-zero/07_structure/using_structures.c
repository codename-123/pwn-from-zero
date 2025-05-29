#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct score {
    int kor;  // 4바이트
    int eng;  // 4바이트
    int mat;  // 4바이트 → 총 12바이트 구조체 (x86/x64 동일)
};

struct address {
    char name[20];   // 고정 크기 배열 (스택에 저장, 오버플로우 주의)
    int age;         // 4바이트 정수 (정렬에 따라 padding 발생 가능)
    char tel[20];    // 고정 크기 배열 (전화번호)
    char addr[80];   // 고정 크기 배열 (주소, BOF 발생 시 영향 큼)
};

void print_list(struct address* lp);

struct list {
    int num;              // 데이터 필드 (4바이트)
    struct list* next;    // 포인터 필드 (8바이트 on x86_64)
};

int main(void) {

    // 구조체 포인터와 "->" 연산자

    struct score yuni = { 90, 80, 70 };  // 구조체 변수 yuni는 스택에 저장됨
    struct score* ps = &yuni;           // ps는 yuni의 주소를 가리키는 포인터 (스택에 위치)

    // 포인터를 통한 구조체 멤버 접근
    printf("국어: %d\n", (*ps).kor);    // 역참조 후 멤버 접근 (ps가 가리키는 곳의 kor)
    printf("영어: %d\n", ps->eng);      // 포인터 연산자 -> 를 통해 직접 접근
    printf("수학: %d\n", ps->mat);      // 동일하게 ps가 가리키는 구조체의 멤버에 접근

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 구조체 배열

    // 구조체 배열 초기화 (list는 스택에 연속된 구조체 5개를 저장)
    struct address list[5] = {
        {"천고무", 23, "111-1111", "천영무 다시 2번지"},
        {"천영무", 33, "222-1111", "천영무 다시 3번지"},
        {"천영길", 43, "333-1111", "천영무 다시 4번지"},
        {"천영왕", 53, "444-1111", "천영무 다시 5번지"},
        {"천영구", 63, "555-1111", "천영무 다시 6번지"}
    };

    int i;

    // 구조체 배열 순회 및 멤버 출력
    for (i = 0; i < 5; i++) {
        printf("%10s%5d%15s%20s\n", list[i].name, list[i].age, list[i].tel, list[i].addr);
        // 구조체 멤버 접근 방식은 list + i*size + offset 으로 계산됨 (포인터 연산 기반)
    }

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 구조체 배열을 처리하는 함수

    // 구조체 배열 초기화 (위랑 같음)
    struct address list2[5] = {
        {"천고무", 23, "111-1111", "천영무 다시 2번지"},
        {"천영무", 33, "222-1111", "천영무 다시 3번지"},
        {"천영길", 43, "333-1111", "천영무 다시 4번지"},
        {"천영왕", 53, "444-1111", "천영무 다시 5번지"},
        {"천영구", 63, "555-1111", "천영무 다시 6번지"}
    };

    print_list(list2);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 자기 참조 구조체 

    // 개별 구조체 노드 생성 (스택에 저장)
    struct list a = { 10, 0 }, b = { 20, 0 }, c = { 30, 0 };

    struct list* head = &a;     // head 포인터는 첫 노드 a를 가리킴
    struct list* current;

    // 노드 연결 (연결 리스트 구성)
    a.next = &b;
    b.next = &c;
    // c.next = NULL (기본값 0)

    // 단일 노드 접근 (포인터 체인 확인용)
    printf("head->num: %d\n", head->num);               // a.num
    printf("head->next->num: %d\n", head->next->num);   // b.num

    // 전체 리스트 순회 (current 포인터로 순차 접근)
    printf("list all: ");

    current = head;
    while (current != NULL) {
        printf("%d ", current->num);        // 각 노드의 num 출력
        current = current->next;            // 다음 노드로 이동
    }

    printf("\n");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_list(struct address* lp) {   // 구조체 배열 처리 함수
    int i;

    for (i = 0; i < 5; i++) {
        // 구조체 포인터를 배열처럼 순회하며 멤버 접근
        // (lp + i)는 list[i]와 동일, 메모리 기준으로는 struct 크기만큼 오프셋 이동
        printf("%10s%5d%15s%20s\n", (lp + i)->name, (lp + i)->age, (lp + i)->tel, (lp + i)->addr);
    }
}