#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {

	// 한 줄씩 입출력하는 fgets와 fputs

    // fgets(char *, int, FILE *); → fgets(입력할 배열, 배열의 크기, 파일 포인터); → 파일로부터 한 줄씩 입력받음. (개행 문자 \n 포함)
    // fputs(const char *, FILE *); → fputs(출력할 문자열, 파일 포인터); → 문자열을 파일에 출력함. (개행 문자 \n은 자동으로 붙지 않음)

    FILE* ifp, * ofp;
    char str[80];     // [!] BOF 주의
    char* res;

    // 입력 파일 열기 (읽기 모드)
    // 민감 파일 읽기 또는 정보 유출 시도 가능
    ifp = fopen("D:\\old.txt", "r");
    if (ifp == NULL) {
        printf("입력 파일을 열지 못했습니다.\n");
        return 1;
    }

    // 출력 파일 열기 (쓰기 모드)
    // 정보 저장, 로그 조작 등 실전 악용 가능
    ofp = fopen("D:\\new.txt", "w");
    if (ofp == NULL) {
        printf("출력 파일을 열지 못했습니다.\n");
        return 1;
    }

    while (1) {
        // 한 줄씩 입력 (개행 문자 포함됨)
        res = fgets(str, sizeof(str), ifp);
        if (res == NULL) {
            break;  // 파일 끝 or 에러
        }

        // 개행 문자 제거
        str[strlen(str) - 1] = '\0';

        // 줄 단위 문자열 출력
        // 실전에서는 파일 내용 조작, 변형, 은닉 등에 사용 가능
        fputs(str, ofp);
        fputs(" ", ofp);  // 공백으로 줄을 연결
    }

    fclose(ifp);
    fclose(ofp);
    
    printf("\n\n"); //-----------------------------------------------------------------------------

    // 다양한 형태로 입출력 하는 fscanf, fprintf

    // fscanf(FILE *, const char *, ...); → fscanf(입력할 파일의 포인터, "%s%d%f" 등등 , ....); → 파일에서 형식에 맞춰 데이터를 읽어옴.
    // fprintf(FILE *, const char *, ...); → fprintf(출력할 파일의 포인터, "%s%d%f" 등등, ....); → 파일에서 형식에 맞춰 데이터를 저장함.


    FILE* ifp1, * ofp1;
    char name[20];
    int kor, eng, mat;
    int tot;
    double avg;
    int res1;

    // 입력 파일 열기 (읽기 모드)
    // 민감 파일 분석, 설정값 수집 등에서 활용 가능
    ifp1 = fopen("D:\\student.txt", "r");
    if (ifp1 == NULL) {
        printf("입력 파일을 열지 못했습니다.\n");
        return 1;
    }

    // 출력 파일 열기 (쓰기 모드)
    // 조작된 정보 기록, 로그 위조 등 활용 가능
    ofp1 = fopen("D:\\score.txt", "w");
    if (ofp1 == NULL) {
        printf("출력 파일을 열지 못했습니다.\n");
        return 1;
    }

    while (1) {
        // 서식 기반 입력 → 포맷 스트링 취약점이 발생할 수 있는 지점
        res1 = fscanf(ifp1, "%s%d%d%d", name, &kor, &eng, &mat);
        if (res1 == EOF) break;

        // 총점/평균 계산
        tot = kor + eng + mat;
        avg = tot / 3.0;

        // 서식 기반 출력 → 로그 포맷 위조, 데이터 은닉 등 실습 가능
        fprintf(ofp1, "%s%5d%7.1lf\n", name, tot, avg);
    }

    fclose(ifp1);
    fclose(ofp1);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // fread, fwrite 함수 & fprintf와 fwrite 함수의 차이

    // fwrite(void *ptr, size_t size, size_t nitems, FILE *stream); → fwrite(출력할 데이터의 주소, 크기, 개수, 파일 포인터); → 메모리의 이진 데이터를 그대로 파일에 기록함.
    // fread(const void *ptr, size_t size, size_t nitems, FILE *stream); → fread(데이터를 저장할 주소, 크기, 개수, 파일 포인터); → 파일에서 이진 데이터를 그대로 읽어 메모리에 저장함.

    FILE* afp, * bfp;
    int num = 10;
    int res;

    // 텍스트 모드로 출력 파일 개방
    // → 사람이 읽기 쉬운 형태로 저장됨 (문자 기반, 로그 남기기 등)
    afp = fopen("a.txt", "wt");
    fprintf(afp, "%d", num);  // num 값을 문자열로 변환하여 출력
    fclose(afp);

    // 바이너리 모드로 출력 파일 개방
    // → 메모리의 원시 바이트 그대로 기록 → 쉘코드, 구조체 덤프 등 실전용
    bfp = fopen("b.txt", "wb");
    fwrite(&num, sizeof(num), 1, bfp);  // num 값을 그대로 파일에 출력 (4바이트 이진)
    fclose(bfp);

    // 바이너리 모드로 입력 파일 개방
    // → fwrite로 저장한 raw 데이터를 그대로 다시 읽음
    bfp = fopen("b.txt", "rb");
    fread(&res, sizeof(res), 1, bfp);  // 파일의 데이터를 그대로 변수에 입력
    printf("%d", res);                 // 입력한 데이터 확인
    fclose(bfp);
}
