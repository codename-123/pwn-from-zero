#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ����ü ����: ������� ���� �޸� ������ ������ (��ü 8����Ʈ)
union student {
	int num;         // 4����Ʈ
	double grade;    // 8����Ʈ (����ü ��ü ũ��� ���� ū ��� ���� �� 8����Ʈ)
};

// ������ ����: �� �׸��� ���������� ���� �� (SPRING=0, SUMMER=1, ...)
enum season {SPRING, SUMMER, FALL, WINTER};

struct student1 { // ����ü ����
    int num;         // �й� (4����Ʈ)
    double grade;    // ���� (8����Ʈ) �� padding ���� �� ����ü ��ü 16����Ʈ ����
};

// typedef�� ���� struct student1 �� Student �� ��Ī ����
typedef struct student1 Student;

// �Լ� ����: ����ü �����͸� ���ڷ� ����
void print_data(Student* ps);

int main(void) {

	// ����ü

	union student s = { 315 };   // num�� 315 ����� (grade�� ���� ������ ����)

	printf("�й�: %d\n", s.num); // num ���� �� ���� ���

	s.grade = 4.4;               // grade�� double �� ���� �� ���� int ��(num)�� �޸𸮻󿡼� �������

	printf("����: %.1lf\n", s.grade); // grade ��� �� ����
	printf("�й�: %d\n", s.num);      // num ����� �� grade ���� �Ϻθ� int�� �ؼ��ϹǷ� �ǹ� ���� �� ���� �� ����

	printf("\n\n"); //--------------------------------------------------------------------------------

	// ������

    enum season ss;  // ������ ���� �� int������ ó���� (���� 4����Ʈ)
    char* pc;        // ���ڿ� ������ (��¿� �޽��� ����)

    ss = SPRING;     // ss�� SPRING(=0)���� �ʱ�ȭ��

    // switch-case: �������� enum ���� �������� �б�
    // ������ �� enum�� �ܼ��� ���� �񱳷� �����ϵ� �� �������� ���� ���ִ� ����
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
        pc = "unknown"; break;  // ��� ���� ���� ��� (����/������ ���鿡���� �߿�)
    }

    printf("���� ���� Ȱ�� => %s\n", pc);  // �����Ͱ� ����Ű�� ���ڿ� ���

    printf("\n\n"); //--------------------------------------------------------------------------------

    // typedef�� ����� �� ������
    
    // typedef ���п� Student�� �����ϰ� ��� ����
    Student s1 = { 315, 4.2 };

    // ����ü ������ ���� �� �Լ� ������ ���� ����ü ��� ���� ����
    print_data(&s1);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_data(Student* ps) {  // ����ü �����͸� �̿��� ������ ��� �Լ�

    // �����͸� ���� ����ü ��� ���� (s1�� �޸𸮸� ���� ����)
    printf("�й�: %d\n", ps->num);
    printf("����: %.1f\n", ps->grade);
}
	