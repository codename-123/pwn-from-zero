#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 매크로 정의 (매크로명을 만드는 #define)
#define PI 3.14159            // 상수 값 정의 → 값 숨김 우회 가능
#define LIMIT 100.0           // 비교용 임계값 (임계점 우회, 조건 조작 실습 가능)
#define MSG "passed!"         // 문자열 상수 → 메시지 조작 시 주의 필요
#define ERR_PRN printf("범위를 벗어났습니다!\n")  // 간단한 명령 매크로화 → 분석 흐름 가림 가능

// 매크로 정의 (#define을 사용한 매크로 함수)
#define SUM(a, b) ((a) + (b))
#define MUL(a, b) ((a) * (b))

// 매크로 정의 (매크로 연산자 #과 ##)
// #x → 인자를 문자열로 변환 → 출력 메시지 조작 가능 (로깅 위장, 디버깅 혼란)
#define PRINT_EXPR(x) printf(#x " = %d\n", x)

// x ## y → 토큰 결합 → 변수명 동적 생성 가능 → 코드 추적/정적 분석 방해
#define NAME_CAT(x, y) (x ## y)

// 매크로 정의 (조건부 컴파일 지시자)
#define VER 7         // 버전 값 정의 → 빌드 조건 분기용
#define BIT16         // BIT16 매크로가 정의되어 있음을 의미 (값은 필요 없음)

// 매크로 정의 (#pragma 지시자)
// Sample1 구조체: 1바이트 정렬 적용 → padding 없음 → 크기 = 5
#pragma pack(push, 1)
typedef struct {
	char ch;  // 1 byte
	int in;   // 4 byte (바로 이어서 붙음)
} Sample1;

// Sample2 구조체: 기본 정렬 (4바이트 기준) → padding 포함 → 크기 = 8
#pragma pack(pop)
typedef struct {
	char ch;  // 1 byte
	// 3 byte padding
	int in;   // 4 byte
} Sample2;

// 함수 정의 (이미 정의된 매크로)
void func(void);

int main(void) {
	
	// 매크로명을 만드는 #define

	double radius, area;

	printf("반지름을 입력하세요.: ");
	scanf("%lf", &radius);	// 사용자 입력 → 조건 분기 트리거로 활용 가능

	area = PI * radius * radius;	// 계산식에 매크로 치환 적용

	if (area > LIMIT) ERR_PRN;	// 매크로 → printf()로 치환 → 흐름 분석 시 주의
	else printf("원의 면적: %2.lf (%s)\n", area, MSG);	// MSG 매크로 문자열 출력

	printf("\n\n"); //--------------------------------------------------------------------------------

	// #define을 사용한 매크로 함수
	
	int a = 10, b = 20;
	int x = 30, y = 40;
	int res;

	printf("a + b: %d\n", SUM(a, b));	// 매크로 치환 → 코드 난독화 가능
	printf("x + y: %d\n", SUM(x, y));
	res = 30 / MUL(2, 5);		// 괄호 없으면 오작동 가능 → 취약점 원인 될 수 있음
	printf("res: %d\n", res);

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 매크로 연산자 #과 ##

	int a1, a2;

	// NAME_CAT(a, 1) → a1, NAME_CAT(a, 2) → a2 로 전처리 시 치환됨
	NAME_CAT(a, 1) = 10;
	NAME_CAT(a, 2) = 20;

	// PRINT_EXPR(a1 + a2) → printf("a1 + a2 = %d\n", a1 + a2);
	PRINT_EXPR(a1 + a2);
	PRINT_EXPR(a2 - a1);

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 조건부 컴파일 지시자

	int max;

#if VER >= 6
	// 특정 버전 이상에서만 포함됨 → 빌드 분기 가능 (코드 삽입/은폐 실습 가능)
	printf("버전 %d입니다.\n", VER);
#endif	// if의 끝

#ifdef BIT16
	max = 32767;       // BIT16이 정의된 경우 → 16비트 환경 설정
#else
	max = 2147483647;  // BIT16이 정의되지 않은 경우 → 32비트 환경
#endif	// ifdef의 끝

	printf("int형 변수의 최댓값: %d\n", max);	// 분기 결과 출력

	printf("\n\n"); //--------------------------------------------------------------------------------

	// #pragma 지시자

	printf("Sample1 구조체의 크기: %d바이트\n", sizeof(Sample1));
	printf("Sample2 구조체의 크기: %d바이트\n", sizeof(Sample2));

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 이미 정의된 매크로

	// 컴파일 타임 정보 → 빌드 시점 추적에 사용 가능 (타임스탬프 위조 실습 등)
	printf("컴파일 날짜와 시간: %s, %s\n\n", __DATE__, __TIME__);

	// 코드 메타데이터 노출 → 로그/디버그 정보에 포함될 경우 정보 유출 가능
	printf("파일명: %s\n", __FILE__);          // 현재 파일명
	printf("함수명: %s\n", __FUNCTION__);      // 현재 함수명
	printf("행번호: %d\n", __LINE__);          // 현재 행 번호

// 매크로를 이용해 파일명과 라인 번호를 임의로 변경 가능 → 디버깅 회피, 혼란 유발
#line 100 "macro.c"   // 이후 __FILE__ = "macro.c", __LINE__ = 100부터 시작됨
	func();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void func(void) {

	printf("\n");
	// 위에서 바꾼 __FILE__, __LINE__ 적용됨 → 실제 코드와 위치 불일치
	printf("파일명: %s\n", __FILE__);
	printf("함수명: %s\n", __FUNCTION__);
	printf("행번호: %d\n", __LINE__);
}
