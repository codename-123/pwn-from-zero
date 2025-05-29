#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 공용체 정의: 멤버들이 같은 메모리 공간을 공유함 (전체 8바이트)
union student {
	int num;         // 4바이트
	double grade;    // 8바이트 (공용체 전체 크기는 가장 큰 멤버 기준 → 8바이트)
};

// 열거형 정의: 각 항목은 내부적으로 정수 값 (SPRING=0, SUMMER=1, ...)
enum season {SPRING, SUMMER, FALL, WINTER};

struct student1 { // 구조체 정의
    int num;         // 학번 (4바이트)
    double grade;    // 학점 (8바이트) → padding 포함 시 구조체 전체 16바이트 예상
};

// typedef를 통해 struct student1 → Student 로 별칭 정의
typedef struct student1 Student;

// 함수 선언: 구조체 포인터를 인자로 받음
void print_data(Student* ps);

int main(void) {

	// 공용체

	union student s = { 315 };   // num에 315 저장됨 (grade는 아직 사용되지 않음)

	printf("학번: %d\n", s.num); // num 접근 → 정상 출력

	s.grade = 4.4;               // grade에 double 값 저장 → 기존 int 값(num)은 메모리상에서 덮어써짐

	printf("학점: %.1lf\n", s.grade); // grade 출력 → 정상
	printf("학번: %d\n", s.num);      // num 재출력 → grade 값의 일부를 int로 해석하므로 의미 없는 값 나올 수 있음

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 열거형

    enum season ss;  // 열거형 변수 → int형으로 처리됨 (보통 4바이트)
    char* pc;        // 문자열 포인터 (출력용 메시지 저장)

    ss = SPRING;     // ss는 SPRING(=0)으로 초기화됨

    // switch-case: 정수형인 enum 값을 기준으로 분기
    // 리버싱 시 enum은 단순한 숫자 비교로 컴파일됨 → 가독성만 좋게 해주는 역할
    switch (ss) {
    case SPRING:
        pc = "inline"; break;
    case SUMMER:
        pc = "swimming"; break;
    case FALL:
        pc = "trip"; break;
    case WINTER:
        pc = "skiing"; break;
    default:
        pc = "unknown"; break;  // 모든 값에 대한 대비 (보안/안정성 측면에서도 중요)
    }

    printf("나의 레저 활동 => %s\n", pc);  // 포인터가 가리키는 문자열 출력

    printf("\n\n"); //--------------------------------------------------------------------------------

    // typedef를 사용한 형 재정의
    
    // typedef 덕분에 Student로 간결하게 사용 가능
    Student s1 = { 315, 4.2 };

    // 구조체 포인터 전달 → 함수 내에서 직접 구조체 멤버 접근 가능
    print_data(&s1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_data(Student* ps) {  // 구조체 포인터를 이용한 데이터 출력 함수

    // 포인터를 통한 구조체 멤버 접근 (s1의 메모리를 직접 참조)
    printf("학번: %d\n", ps->num);
    printf("학점: %.1f\n", ps->grade);
}
	