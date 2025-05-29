#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>	// strcpy 함수를 사용하기 위해 인클루드함

char* my_strcpy(char* pd, char* ps); // strcpy 함수 직접 구현
int my_strlen(char* ps);			 // strlen 함수 직접 구현
char* my_strcat(char* pd, char* ps); // strcat 함수 직접 구현
int my_strcmp(char* pa, char* pb);	 // strcmp 함수 직접 구현

int main(void) {

	// strcpy(char *dest, const char *src) → strcpy(복사받을 곳, 복사할 문자열) → strcpy 함수는 문자열을 복사할 때, 널문자('\0')까지 전부 복사해주는 함수이다.
	// 단, 크기 제한 없이 복사하므로 "버퍼 오버플로우"에 취약하다.

	// 문자열을 대입하는 strcpy 함수 (🔥🔥매우 중요!)
	 
	// str1, str2는 크기가 정해진 배열 (스택 상에 존재)
	char str1[80] = "strawberry";
	char str2[80] = "apple";

	// ps1은 문자열 리터럴 "banana"를 가리키는 포인터
	char* ps1 = "banana";

	// ps2는 str2의 주소를 가리킴 (str2와 같은 문자열을 참조함)
	char* ps2 = str2;

	printf("최초 문자열: %s\n", str1);

	// 문자열 복사 (str2 → str1)
	strcpy(str1, str2);
	// → "apple"을 str1에 덮어씀 (정상 복사)
	// → null 문자('\0')까지 포함해 복사됨

	printf("바뀐 문자열: %s\n", str1);

	// 문자열 리터럴을 복사 (ps1 → str1)
	strcpy(str1, ps1);
	// → "banana" 복사. 문자열 리터럴도 포인터로 전달되면 복사 가능
	// 크기 초과가 아니라면 문제 없음

	printf("바뀐 문자열: %s\n", str1);

	// 문자열 포인터를 복사 (ps2 → str1)
	strcpy(str1, ps2);
	// → ps2는 str2를 가리키므로 결국 str2의 문자열이 str1에 복사됨

	printf("바뀐 문자열: %s\n", str1);

	// 문자열 리터럴 직접 복사 ("banana" → str1)
	strcpy(str1, "banana");
	// → 문자열 리터럴도 문제없이 복사됨 (동일한 결과)

	printf("바뀐 문자열: %s\n", str1);

	printf("\n\n"); //--------------------------------------------------------------------------------

	// strcpy 함수 구현 방법

	char str[80] = "strawberry";

	printf("바꾸기 전 문자열: %s\n", str);

	// 문자열 리터럴 "apple"을 str에 복사
	my_strcpy(str, "apple");
	// → 내부에서 포인터 연산으로 문자를 하나씩 복사함
	// → 널문자('\0')까지 복사해야 끝남

	printf("바꾼 후 문자열: %s\n", str);

	// 함수의 리턴값도 char* 이므로, printf 안에 바로 쓸 수 있음
	printf("다른 문자열 대입: %s\n", my_strcpy(str, "kiwi"));

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 원하는 개수의 문자만을 복사하는 strncpy 함수

	// strncpy(char *dest, const char *src, size_t n); → strncpy(복사할 곳, 복사할 내용, 최대 길이); → strcpy와 다르게 문자열을 복사할 때 문자의 수를 지정할 수 있음

	char frult[20] = "mango tree";

	strncpy(frult, "apple-fie", 5); // "apple-fie"에서 5글자 → "apple"
	frult[5] = '\0';                // 문자열 종료 처리 (필수) → null을 사용하지 않으면 frult 안의 "apple" + 그 뒤에 남아있던 " tree"도 같이 출력됨

	printf("%s\n", frult);			// 출력: apple

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 문자열 길이를 계산하는 strlen 함수

	char frult1[80], frult2[80];
	char* resp;

	printf("2개의 과일 입력: ");
	scanf("%s %s", frult1, frult2);
	// → 두 개의 문자열을 공백 기준으로 입력 받음 (각각 frult1, frult2에 저장)

	// → strlen은 문자열의 길이를 '\0'까지 세서 리턴함
	// → 더 긴 쪽을 resp 포인터가 가리키게 설정
	if (strlen(frult1) > strlen(frult2)) {
		resp = frult1;
	}
	else {
		resp = frult2;
	}

	printf("이름이 긴 과일은: %s\n", resp);
	printf("sizeof: %d, strlen: %d\n\n", sizeof(resp), strlen(resp));

	printf("함수로 만든 문자열 길이: %d", my_strlen("googoo"));

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 문자열을 붙이는 strcat, strncat 함수

	// strcat(char *dest, const char *src); → strcat(붙일 위치, 붙일 문자열); → strcat은 문자열 끝에 다른 문자열을 이어붙이는 함수이다.
	// 하지만 문자열의 길이를 제한하지 않기 때문에, 복사 대상 배열의 크기를 초과하면 "버퍼 오버플로우"가 발생할 수 있다.

	// strncat(char *dest, const char *src, size_t n); → strncat(붙일 위치, 붙일 문자열, 최대 붙일 길이); → strncat은 strcat과 같지만, 붙일 문자열의 길이를 제한할 수 있다.
	// 하지만 종료 널문자('\0')가 n길이 이상인 경우 붙지 않을 수 있으므로 주의 필요!

	char str3[80] = "straw";

	strcat(str3, "berry");
	// "straw" 뒤에 "berry" 붙이기 → 결과: "strawberry"
	// 정상 동작이지만, "straw"가 너무 길었다면 BOF 가능성 있음
	printf("%s\n", str3);
	strncat(str3, "piece", 3);
	// "strawberry" 뒤에 "pie"만 붙임 → 결과: "strawberrypie"
	// n 길이 제한은 있지만, 종료 처리까지 고려해야 진짜 안전
	printf("%s\n\n", str3);

	printf("함수로 만든 문자열 붙이기 %s", my_strcat(str3, "system"));

	printf("\n\n"); //--------------------------------------------------------------------------------

	// 문자열을 비교하는 strcmp, strncmp 함수

	// strcmp(const char* s1, const char* s2) → strcmp(문자열1, 문자열2); → strcmp는 두 문자열을 왼쪽부터 한 글자씩 비교함, 같으면 0, s1 > s2면 양수, s1 < s2면 음수를 반환함.
	// 주의: 대소문자도 구분함 ('A' < 'a')

	// strncmp(const char* s1, const char* s2, size_t n) → strncmp(문자열1, 문자열2, 비교할 글자 수); → strncmp는 최대 n글자까지만 비교하며, 그 외는 무시함.
	// 로그인 체크, 리버싱 흐름 제어에서 자주 등장함.


	char car1[80] = "buscar";
	char car2[80] = "bustruck";

	printf("사전에 나중에 나오는 차 이름: ");
	if (strcmp(car1, car2) > 0) {
		// car1 > car2 (사전 순으로 뒤에 있는 문자) 왼쪽부터 비교
		// bus bus 같음. c vs t 다름 → c = ASCII(99) vs t = ASCII(116) → 99 - 116 = -17 음수이므로 else가 실행됨.
		printf("%s\n", car1);
	}
	else {
		printf("%s\n", car2);
	}

	printf("앞에서 3개의 문자를 비교하면 ");
	if (strncmp(str1, str2, 3) == 0) {
		// 앞 3글자 "bus" == "bus" → 같음
		printf("같다.\n\n");
	}
	else {
		printf("다르다.\n\n");
	}

	// strcmp는 로그인/인증 우회, strcmp 결과값 조건 분기 우회 등에서 자주 등장함
	// → if (strcmp(input, "admin") == 0) → 여기에 페이로드 유도 가능

	// strncmp는 부분 문자열 검사에 사용되며,
	// → 의도치 않게 짧은 입력만으로 통과할 수 있는 "논리 우회 취약점"을 만들 수 있음
	// → 예: strncmp(input, "admin", 3) == 0 → "admxxx" 도 통과 가능

	printf("함수를 이용한 문자열 비교: %d", my_strcmp(car1, car2));

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

char* my_strcpy(char* pd, char* ps) { // strcpy와 동일한 구조로 문자열 복사 수행
	char* po = pd; // 원래 시작 주소 저장 (리턴용)

	// 1, 문자열 끝날 때까지 한 글자씩 복사
	while (*ps != '\0') {
		*pd = *ps;
		pd++;
		ps++;
	}
	*pd = '\0';	// 2, 마지막에 널문자 붙여서 문자열 종료 표시

	// 만약 마지막 '\0'을 안 붙이면?
	// → *pd = { 'a', 'p', 'p' , 'l' , 'e' , ? , ? , ? , ? , ?... }

	return po;	// 복사된 시작 주소 반환
}

int my_strlen(char* ps) {
	int cnt = 0;

	// 1, 널문자('\0')를 만날 때까지 반복하며 문자 수 세기
	while (*ps != '\0') {
		cnt++;
		ps++;  // 2, 다음 문자로 포인터 이동
	}

	return cnt;  // 전체 문자 개수 리턴
}

char* my_strcat(char* pd, char* ps) {
	char* po = pd;  // 시작 주소 저장 (리턴용)

	// 1, pd 포인터를 기존 문자열 끝('\0')으로 이동
	while (*pd != '\0') {
		pd++;
	}

	// 2, ps의 문자를 하나씩 pd 뒤에 복사
	while (*ps != '\0') {
		*pd = *ps;
		pd++;
		ps++;
	}

	*pd = '\0';  // 마지막에 널문자 붙여 문자열 종료

	return po;   // 결과 문자열의 시작 주소 반환
}

int my_strcmp(char* pa, char* pb) {

	// 1, 문자 하나씩 비교하며 같으면 계속 진행
	while ((*pa == *pb) && (*pa != '\0')) {
		pa++;
		pb++;
	}

	// 2, 다른 문자를 만나면 그 크기 차이로 결과 반환
	if (*pa > *pb) return 1;
	else if (*pa < *pb) return -1;
	else return 0;	// 두 포인터가 모두 '\0' → 문자열 완전히 같음

	// 같으면 0, pa > pb면 1, pa < pb면 -1 반환
}