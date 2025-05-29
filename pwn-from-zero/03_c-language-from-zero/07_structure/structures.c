#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {           // ����ü ���� (int + double = �� 16����Ʈ ����, ���� padding ����)
    int num;               // �й� (4����Ʈ)
    double grade;          // ���� (8����Ʈ) �� padding ������ �����δ� int �ڿ� 4����Ʈ ���� ������ ���� �� ����
};

struct profile {
    char name[20];         // ���ÿ� ��ġ�� ���� ũ�� �迭 (�����÷ο� ����)
    int age;               // 4����Ʈ ���� (���� �� �е� ����)
    double height;         // 8����Ʈ �Ǽ� (8����Ʈ ����, ����ü ���� ����)
    char* intro;           // ���� ����Ű�� ������ (���� �޸� ���� ����)
};

struct member {
    int id;             // 4����Ʈ ���� (�й�)
    char name[20];      // ���� ���� ���� �迭 (���ÿ� ����, BOF ����)
    double grade;       // 8����Ʈ �Ǽ� (8����Ʈ ����, ����ü ���� ���� ����)
};

// ����ü ���� (double 2�� �� 16����Ʈ ����, ���� ���� ����)
struct vision {     
    double left;
    double right;
};

struct vision exchange(struct vision);

// ��Ʈ �ʵ� ����ü ���� (�� 7��Ʈ ���)
struct children {
    unsigned int son : 2;  // 2��Ʈ (0~3���� ǥ�� ����)
    unsigned int daughter : 2;  // 2��Ʈ (0~3)
    unsigned int pet : 3;  // 3��Ʈ (0~7)
};

int main(void) {

    // ����ü ����� ��� ���

    struct student s;     // ����ü ���� ���� (s1�� ���� �ּҺ��� num, grade ������ �޸𸮿� �����)

    s.num = 2;            // ����ü ��� ���� �� �޸� ������ +0���� 4����Ʈ ���� ����
    s.grade = 2.7;        // ����ü ��� ���� �� ������ +8���� 8����Ʈ double ���� (�߰� padding ���)

    printf("�й�: %d\n", s.num);
    printf("����: %.1lf\n", s.grade);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // �پ��� ����ü ���

    struct profile mu;    // ����ü ���� �� ��ü�� ���ÿ� �����

    strcpy(mu.name, "õ����");  // ���� �迭 name�� ���ڿ� ���� (���� ���� ����)
    mu.age = 24;
    mu.height = 165.5;

    mu.intro = (char*)malloc(80);   // intro�� ����ų �� �޸� �Ҵ�
    printf("�ڱ� �Ұ�: ");
    gets(mu.intro);                 // [!] BOF �����: �� �����÷ο� ����

    printf("�̸�: %s\n", mu.name);
    printf("����: %d\n", mu.age);
    printf("Ű: %.1lf\n", mu.height);
    printf("�ڱ�Ұ�: %s\n", mu.intro);
    free(mu.intro);                 // �� �޸� ���� (UAF �ǽ� �� �� ���� �߿�)

    printf("\n\n"); //-----------------------------------------------------------------------------

    // ����ü ������ �ʱ�ȭ�� ���� ����

     // ����ü ���� �ʱ�ȭ (���ÿ� �� ����� ������� ��ġ��)
    struct member s1 = { 315, "ȫ�浿", 2.4 },
        s2 = { 316, "�̼���", 3.7 },
        s3 = { 317, "õ����", 4.4 };

    struct member max;  // �ְ� ���� ������ ����� ���� (���� �޸�)

    // ����ü ��ü ����
    max = s1;
    if (s2.grade > max.grade) max = s2;
    if (s3.grade > max.grade) max = s3;

    // ��� ���
    printf("�й�: %d\n", max.id);
    printf("�̸�: %s\n", max.name);
    printf("����: %.1lf\n", max.grade);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // ����ü ������ �Լ� �Ű������� ����ϱ�

    struct vision robot;  // ����ü ���� ���� (���� �޸𸮿� ����)

    printf("�÷� �Է�: ");
    scanf("%lf%lf", &(robot.left), &(robot.right)); // ����� �Է� �� ���ÿ� ����

    robot = exchange(robot);  // ����ü ���� + ��ȯ�� ����� (�� ����)

    printf("�ٲ� �÷�: %.1lf, %.1lf\n", robot.left, robot.right);

    printf("\n\n"); //-----------------------------------------------------------------------------

    // ��Ʈ �ʵ� ����ü

    struct children my = { 1, 2, 3 };  // ��Ʈ �ʵ� �ʱ�ȭ (���� 6��Ʈ ����)
    int sum;

    // ����ü ��ü ũ�� ���
    printf("struct children �� ũ��: %d����Ʈ\n", sizeof(my));
    // �����Ϸ��� ���� �ּ� ����(���� 1����Ʈ �Ǵ� 4����Ʈ)�� ���ĵ�
    // �Ϲ������� x86_64 ���� 4����Ʈ�� ��µ�

    // ��Ʈ �ʵ� ��� ���� (�ڵ����� ����ũ & ����Ʈ ó����)
    sum = my.son + my.daughter + my.pet;
    printf("�ڽ� ��: %d\n", sum);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct vision exchange(struct vision robot) { // �÷� ���� ��ȯ �Լ�

    double temp;

    // ����ü ���� �� ��ȯ (���� ������ �� ����)
    temp = robot.left;
    robot.left = robot.right;
    robot.right = temp;

    return robot; // ����ü �� ����Ǿ� ��ȯ (���� ����)
}
