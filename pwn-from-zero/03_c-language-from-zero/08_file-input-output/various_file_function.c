#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {

	// �� �پ� ������ϴ� fgets�� fputs

    // fgets(char *, int, FILE *); �� fgets(�Է��� �迭, �迭�� ũ��, ���� ������); �� ���Ϸκ��� �� �پ� �Է¹���. (���� ���� \n ����)
    // fputs(const char *, FILE *); �� fputs(����� ���ڿ�, ���� ������); �� ���ڿ��� ���Ͽ� �����. (���� ���� \n�� �ڵ����� ���� ����)

    FILE* ifp, * ofp;
    char str[80];     // [!] BOF ����
    char* res;

    // �Է� ���� ���� (�б� ���)
    // �ΰ� ���� �б� �Ǵ� ���� ���� �õ� ����
    ifp = fopen("D:\\old.txt", "r");
    if (ifp == NULL) {
        printf("�Է� ������ ���� ���߽��ϴ�.\n");
        return 1;
    }

    // ��� ���� ���� (���� ���)
    // ���� ����, �α� ���� �� ���� �ǿ� ����
    ofp = fopen("D:\\new.txt", "w");
    if (ofp == NULL) {
        printf("��� ������ ���� ���߽��ϴ�.\n");
        return 1;
    }

    while (1) {
        // �� �پ� �Է� (���� ���� ���Ե�)
        res = fgets(str, sizeof(str), ifp);
        if (res == NULL) {
            break;  // ���� �� or ����
        }

        // ���� ���� ����
        str[strlen(str) - 1] = '\0';

        // �� ���� ���ڿ� ���
        // ���������� ���� ���� ����, ����, ���� � ��� ����
        fputs(str, ofp);
        fputs(" ", ofp);  // �������� ���� ����
    }

    fclose(ifp);
    fclose(ofp);
    
    printf("\n\n"); //-----------------------------------------------------------------------------

    // �پ��� ���·� ����� �ϴ� fscanf, fprintf

    // fscanf(FILE *, const char *, ...); �� fscanf(�Է��� ������ ������, "%s%d%f" ��� , ....); �� ���Ͽ��� ���Ŀ� ���� �����͸� �о��.
    // fprintf(FILE *, const char *, ...); �� fprintf(����� ������ ������, "%s%d%f" ���, ....); �� ���Ͽ��� ���Ŀ� ���� �����͸� ������.


    FILE* ifp1, * ofp1;
    char name[20];
    int kor, eng, mat;
    int tot;
    double avg;
    int res1;

    // �Է� ���� ���� (�б� ���)
    // �ΰ� ���� �м�, ������ ���� ��� Ȱ�� ����
    ifp1 = fopen("D:\\student.txt", "r");
    if (ifp1 == NULL) {
        printf("�Է� ������ ���� ���߽��ϴ�.\n");
        return 1;
    }

    // ��� ���� ���� (���� ���)
    // ���۵� ���� ���, �α� ���� �� Ȱ�� ����
    ofp1 = fopen("D:\\score.txt", "w");
    if (ofp1 == NULL) {
        printf("��� ������ ���� ���߽��ϴ�.\n");
        return 1;
    }

    while (1) {
        // ���� ��� �Է� �� ���� ��Ʈ�� ������� �߻��� �� �ִ� ����
        res1 = fscanf(ifp1, "%s%d%d%d", name, &kor, &eng, &mat);
        if (res1 == EOF) break;

        // ����/��� ���
        tot = kor + eng + mat;
        avg = tot / 3.0;

        // ���� ��� ��� �� �α� ���� ����, ������ ���� �� �ǽ� ����
        fprintf(ofp1, "%s%5d%7.1lf\n", name, tot, avg);
    }

    fclose(ifp1);
    fclose(ofp1);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // fread, fwrite �Լ� & fprintf�� fwrite �Լ��� ����

    // fwrite(void *ptr, size_t size, size_t nitems, FILE *stream); �� fwrite(����� �������� �ּ�, ũ��, ����, ���� ������); �� �޸��� ���� �����͸� �״�� ���Ͽ� �����.
    // fread(const void *ptr, size_t size, size_t nitems, FILE *stream); �� fread(�����͸� ������ �ּ�, ũ��, ����, ���� ������); �� ���Ͽ��� ���� �����͸� �״�� �о� �޸𸮿� ������.

    FILE* afp, * bfp;
    int num = 10;
    int res;

    // �ؽ�Ʈ ���� ��� ���� ����
    // �� ����� �б� ���� ���·� ����� (���� ���, �α� ����� ��)
    afp = fopen("a.txt", "wt");
    fprintf(afp, "%d", num);  // num ���� ���ڿ��� ��ȯ�Ͽ� ���
    fclose(afp);

    // ���̳ʸ� ���� ��� ���� ����
    // �� �޸��� ���� ����Ʈ �״�� ��� �� ���ڵ�, ����ü ���� �� ������
    bfp = fopen("b.txt", "wb");
    fwrite(&num, sizeof(num), 1, bfp);  // num ���� �״�� ���Ͽ� ��� (4����Ʈ ����)
    fclose(bfp);

    // ���̳ʸ� ���� �Է� ���� ����
    // �� fwrite�� ������ raw �����͸� �״�� �ٽ� ����
    bfp = fopen("b.txt", "rb");
    fread(&res, sizeof(res), 1, bfp);  // ������ �����͸� �״�� ������ �Է�
    printf("%d", res);                 // �Է��� ������ Ȯ��
    fclose(bfp);
}
