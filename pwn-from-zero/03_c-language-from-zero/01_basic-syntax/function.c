#include <stdio.h>

int add(int x, int y); // �Լ� ����

void print_char(char ch, int cnt); // ��ȯ���� ���� �Լ� ���� (return���� ������ �� ����.)

void print_line(void); // ��ȯ���� �Ű������� ��� ���� �Լ� ����

void fruit(int n); // ����Լ� ȣ��

int main(void) { // main �Լ� ����

	int a = 10, b = 20;
	int res;

	res = add(a, b); // add �Լ� ȣ��
	printf("result: %d", res);

	printf("\n\n"); //--------------------------------------------------------------------------------
	
	print_char('@', 5); // ���ڿ� ���ڸ� �ְ� �Լ� ȣ��

	printf("\n\n"); //--------------------------------------------------------------------------------

	print_line(); // �Լ� ȣ��
	printf("�й�	�̸�	����	����\n");
	print_line(); // �Լ� ȣ��

	printf("\n\n"); //--------------------------------------------------------------------------------

	fruit(1); // �Լ� ȣ��

}

int add(int x, int y) { // add �Լ� ���� ����
	
	int temp; // �� ������ ���� ������ ����
	temp = x + y; 

	return temp; // temp ���� ��ȯ
} 

void print_char(char ch, int cnt) { // ��ȯ���� ���� print_char �Լ� ���� ����

	int i;

	for (i = 0; i < cnt; i++) // i�� 0���� cnt-1���� ����, cnt�� �ݺ�
	{
		printf("%c", ch); // �Ű����� ch�� ���� ���� ���.
	}
}

void print_line(void) { // ��ȯ���� �Ű������� ��� ���� print_line �Լ� ���� ����
	
	int i;

	for (i = 0; i < 50; i++) // 50�� �ݺ��Ͽ� '-' ���
	{
		printf("-");
	}
	printf("\n");
}

void fruit(int n) { // ���ȣ�� frult �Լ� ���� ����
	
	printf("apple\n");
	if (n == 3) return;
	fruit(n + 1); 
	// int n ������ �޴� ����. �ȹ����� while�� ���� �ݺ� ����. ��� ������ �Ǿ� n�� 3�� �Ǹ� return(�Լ� ����)
}