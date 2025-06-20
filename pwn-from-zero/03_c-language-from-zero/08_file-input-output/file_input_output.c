#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {

    // 파일 읽기 개방과 폐쇄

    FILE* fp;

    // 파일 열기 시도 (읽기 전용)
    // 경로 조작 또는 민감 파일 접근 시도에 사용 가능
    fp = fopen("D:\\new.txt", "r");

    // 파일 열기 실패 (없음 또는 권한 없음)
    // 존재 여부로 정보 유출 가능
    if (fp == NULL) {
        printf("파일이 열리지 않았습니다.\n");
        return 1;
    }

    // 파일 열기 성공 → 내용 읽기 가능
    printf("파일이 열렸습니다.\n");

    // 리소스 해제
    fclose(fp);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 문자 입력 함수 fgetc

    FILE* fp1;
    int ch;

    // 민감 파일 접근 시도 가능 (예: /etc/passwd, hosts 등)
    fp1 = fopen("D:\\new.txt", "r");

    if (fp1 == NULL) {
        // 파일 존재 여부로 정보 수집 가능 (권한, 경로 유무 등)
        printf("파일이 열리지 않았습니다\n");
        return 1;
    }

    // 파일 내용 한 글자씩 읽어 출력
    // 민감 정보 출력, 파일 유출 시나리오 등에서 사용됨
    while (1) {
        ch = fgetc(fp1);
        if (ch == EOF) {    // 종료 조건 (Window: Ctrl+Z, Linux: Ctrl+D)
            break;  // 파일 끝에 도달
        }
        putchar(ch);  // 한 글자씩 화면에 출력 (또는 로그로 기록 가능)
    }

    // 리소스 해제
    fclose(fp1);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // 문자 출력 함수 fputc

    FILE* fp2;
    char str[] = "문자출력함수";
    int i;

    // 파일 생성 또는 덮어쓰기 (쓰기 모드)
    // 악성코드, 백도어가 로그 파일이나 설정 파일을 조작할 때 사용 가능
    fp2 = fopen("D:\\new.txt", "w");

    if (fp2 == NULL) {
        // 파일 생성 실패 → 경로 권한 확인, 디스크 보호 여부 등 판단 가능
        printf("파일을 만들지 못했습니다.\n");
        return 1;
    }

    i = 0;
    // 문자열을 파일에 한 글자씩 기록
    // 기록된 내용은 정보 은닉, 로그 조작 등에 활용 가능
    while (str[i] != 0) {
        fputc(str[i], fp2);
        i++;
    }
    fputc('\n', fp2);  // 개행 문자 추가

    // 파일 닫기 (쓰기 버퍼 플러시 포함)
    fclose(fp2);

    printf("\n\n"); //-----------------------------------------------------------------------------
    /*
    // 기본적으로 개방되는 표준 입출력 스트림 파일

    int ch1;

    // 표준 입력 → 표준 출력 (한 문자씩)
    // stdin, stdout은 기본 개방 상태 → 별도 fopen 없이 사용 가능
    // 키 입력 감시, 키로깅 테스트, 입력 기반 조건 흐름 분석 등에 활용 가능
    while (1) {
        ch1 = getchar();              // 키보드 입력 (stdin)
        if (ch1 == EOF) {             // 종료 조건 (Window: Ctrl+Z, Linux: Ctrl+D)
            break;
        }
        putchar(ch1);                 // 문자 출력 (stdout)
    }

    printf("\n\n"); //-----------------------------------------------------------------------------

    // stdin과 stdout을 사용한 문자 입출력

    int ch2;

    // fgetc/fputc는 getchar/putchar와 동일한 기능을 수행하지만,
    // 명시적으로 스트림을 지정할 수 있어 리다이렉션 및 로그 조작 등에 활용 가능
    while (1) {
        ch2 = fgetc(stdin);           // 표준 입력에서 문자 읽기
        if (ch2 == EOF) {
            break;
        }
        fputc(ch2, stdout);           // 표준 출력으로 문자 출력
    }
    */
    printf("\n\n"); //-----------------------------------------------------------------------------

    // 텍스트 파일과 바이너리 파일

    FILE* fo;
    int ary[10] = { 13,10,13,13,10,26,13,10,13,10 };    // 제어 문자 시퀀스 포함 (CR, LF, EOF 등)
    int res;
    // int i;

    // 바이너리 쓰기 모드로 파일 생성
    // 바이너리 모드는 OS의 자동 변환 없이 원시 바이트 그대로 기록됨
    // 제어 문자를 포함한 페이로드 저장 시 유용 (ex: 쉘코드, 파일 감염 등)
    fo = fopen("D:\\new.txt", "wb");

    for (i = 0; i < 10; i++) {
        fputc(ary[i], fo);  // 제어 문자(13,10,26 등)를 1바이트씩 기록
    }

    // 텍스트 모드로 파일 다시 열기
    // 윈도우에서는 \x1A(26) → EOF로 처리될 수 있어 읽기 제한 발생
    fo = fopen("D:\\new.txt", "rt");

    while (1) {
        res = fgetc(fo);
        if (res == EOF) break;       // 파일 끝 또는 \x1A(26)에서 종료
        printf("%4d", res);          // 파일 내용을 정수(아스키 값)로 출력
    }
    fclose(fo);
}