#include <stdio.h>

int add(int x, int y); // 함수 선언

void print_char(char ch, int cnt); // 반환값이 없는 함수 선언 (return문을 생략할 수 있음.)

void print_line(void); // 반환값과 매개변수가 모두 없는 함수 선언

void fruit(int n); // 재귀함수 호출

int main(void) { // main 함수 시작

	int a = 10, b = 20;
	int res;

	res = add(a, b); // add 함수 호출
	printf("result: %d", res);

	printf("\n\n"); //--------------------------------------------------------------------------------
	
	print_char('@', 5); // 문자와 숫자를 주고 함수 호출

	printf("\n\n"); //--------------------------------------------------------------------------------

	print_line(); // 함수 호출
	printf("학번	이름	전공	학점\n");
	print_line(); // 함수 호출

	printf("\n\n"); //--------------------------------------------------------------------------------

	fruit(1); // 함수 호출

}

int add(int x, int y) { // add 함수 정의 시작
	
	int temp; // 두 정수의 합을 저장할 변수
	temp = x + y; 

	return temp; // temp 값을 반환
} 

void print_char(char ch, int cnt) { // 반환값이 없는 print_char 함수 정의 시작

	int i;

	for (i = 0; i < cnt; i++) // i는 0부터 cnt-1까지 증가, cnt번 반복
	{
		printf("%c", ch); // 매개변수 ch에 받은 문자 출력.
	}
}

void print_line(void) { // 반환값과 매개변수가 모두 없는 print_line 함수 정의 시작
	
	int i;

	for (i = 0; i < 50; i++) // 50번 반복하여 '-' 출력
	{
		printf("-");
	}
	printf("\n");
}

void fruit(int n) { // 재귀호출 frult 함수 정의 시작
	
	printf("apple\n");
	if (n == 3) return;
	fruit(n + 1); 
	// int n 변수를 받는 이유. 안받으면 while문 무한 반복 느낌. 계속 실행이 되어 n이 3이 되면 return(함수 멈춤)
}