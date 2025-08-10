#include <stdio.h>
#include <string.h>

typedef struct USERDATA
{
	int age;
	char name[30];
	char phone[30];
	struct USERDATA* next;
}USERDATA;

int main()
{
	USERDATA user[4] = {
		{10, "a1", "123-123"},
		{20, "a2", "234-234"},
		{30, "a3", "345-345"},
		{40, "a4", "456-456"}
	};
	
	USERDATA* head = &user[0];
	user[0].next = &user[1];
	user[1].next = &user[2];
	user[2].next = &user[3];
	user[3].next = NULL;

	FILE* fp = NULL;
	fopen_s(&fp, "listData.dat", "wb"); //������ ������ �ּ�, ���� �̸�, ������
	if (fp == NULL) //�ȿ�������
	{
		puts("ERROR: Failed to open listData.dat"); //�ڵ� ����
		return 0;
	}
	
	while (head != NULL)
	{
		fwrite(head, sizeof(USERDATA), 1, fp); //���� ���� �����Ͱ� �ִ� �޸� �ּ�, �� �� �������� ũ��, � ������, �� ������ �ּ�
		head = head->next;
	}	//fp(����)�� �� ���������.

	fclose(fp);
	return 0;
}