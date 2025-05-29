#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {           // 구조체 정의 (int + double = 총 16바이트 예상, 정렬 padding 포함)
    int num;               // 학번 (4바이트)
    double grade;          // 학점 (8바이트) → padding 때문에 실제로는 int 뒤에 4바이트 정렬 공간이 생길 수 있음
};

struct profile {
    char name[20];         // 스택에 위치한 고정 크기 배열 (오버플로우 주의)
    int age;               // 4바이트 정수 (정렬 시 패딩 영향)
    double height;         // 8바이트 실수 (8바이트 정렬, 구조체 정렬 영향)
    char* intro;           // 힙을 가리키는 포인터 (이중 메모리 구조 가능)
};

struct member {
    int id;             // 4바이트 정수 (학번)
    char name[20];      // 고정 길이 문자 배열 (스택에 저장, BOF 주의)
    double grade;       // 8바이트 실수 (8바이트 정렬, 구조체 정렬 영향 있음)
};

// 구조체 정의 (double 2개 → 16바이트 예상, 정렬 영향 없음)
struct vision {     
    double left;
    double right;
};

struct vision exchange(struct vision);

// 비트 필드 구조체 정의 (총 7비트 사용)
struct children {
    unsigned int son : 2;  // 2비트 (0~3까지 표현 가능)
    unsigned int daughter : 2;  // 2비트 (0~3)
    unsigned int pet : 3;  // 3비트 (0~7)
};

int main(void) {

    // 구조체 선언과 멤버 사용

    struct student s;     // 구조체 변수 선언 (s1의 시작 주소부터 num, grade 순서로 메모리에 저장됨)

    s.num = 2;            // 구조체 멤버 접근 → 메모리 오프셋 +0에서 4바이트 정수 저장
    s.grade = 2.7;        // 구조체 멤버 접근 → 오프셋 +8에서 8바이트 double 저장 (중간 padding 고려)

    printf("학번: %d\n", s.num);
    printf("학점: %.1lf\n", s.grade);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 다양한 구조체 멤버

    struct profile mu;    // 구조체 변수 → 전체는 스택에 저장됨

    strcpy(mu.name, "천영무");  // 고정 배열 name에 문자열 복사 (스택 영역 조작)
    mu.age = 24;
    mu.height = 165.5;

    mu.intro = (char*)malloc(80);   // intro가 가리킬 힙 메모리 할당
    printf("자기 소개: ");
    gets(mu.intro);                 // [!] BOF 취약점: 힙 오버플로우 가능

    printf("이름: %s\n", mu.name);
    printf("나이: %d\n", mu.age);
    printf("키: %.1lf\n", mu.height);
    printf("자기소개: %s\n", mu.intro);
    free(mu.intro);                 // 힙 메모리 해제 (UAF 실습 시 이 지점 중요)

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 구조체 변수의 초기화와 대입 연산

     // 구조체 변수 초기화 (스택에 각 멤버가 순서대로 배치됨)
    struct member s1 = { 315, "홍길동", 2.4 },
        s2 = { 316, "이순신", 3.7 },
        s3 = { 317, "천영무", 4.4 };

    struct member max;  // 최고 학점 보유자 저장용 변수 (스택 메모리)

    // 구조체 전체 복사
    max = s1;
    if (s2.grade > max.grade) max = s2;
    if (s3.grade > max.grade) max = s3;

    // 결과 출력
    printf("학번: %d\n", max.id);
    printf("이름: %s\n", max.name);
    printf("학점: %.1lf\n", max.grade);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 구조체 변수를 함수 매개변수에 사용하기

    struct vision robot;  // 구조체 변수 선언 (스택 메모리에 저장)

    printf("시력 입력: ");
    scanf("%lf%lf", &(robot.left), &(robot.right)); // 사용자 입력 → 스택에 저장

    robot = exchange(robot);  // 구조체 복사 + 반환값 덮어쓰기 (값 전달)

    printf("바뀐 시력: %.1lf, %.1lf\n", robot.left, robot.right);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 비트 필드 구조체

    struct children my = { 1, 2, 3 };  // 비트 필드 초기화 (총합 6비트 사용됨)
    int sum;

    // 구조체 전체 크기 출력
    printf("struct children 의 크기: %d바이트\n", sizeof(my));
    // 컴파일러에 따라 최소 단위(보통 1바이트 또는 4바이트)로 정렬됨
    // 일반적으로 x86_64 기준 4바이트가 출력됨

    // 비트 필드 멤버 접근 (자동으로 마스크 & 시프트 처리됨)
    sum = my.son + my.daughter + my.pet;
    printf("자식 수: %d\n", sum);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct vision exchange(struct vision robot) { // 시력 정보 교환 함수

    double temp;

    // 구조체 내부 값 교환 (스택 프레임 내 연산)
    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot; // 구조체 값 복사되어 반환 (깊은 복사)
}
