#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct USERDATA
{
	int age;
	char name[30];
	char phone[30];
	struct USERDATA* next;
}USERDATA;

USERDATA* head = NULL;

void AddNode(int age, char* name, char* phone)
{
	USERDATA* newData = (USERDATA*)malloc(sizeof(USERDATA));
	newData->age = age;
	//newData->name = name // �ּҴ� R-value�̴ϱ� L-value�� �ɼ�����
	strcpy_s(newData->name, sizeof(newData->name), name); //�ٿ��ֱ��� �������� �ּ�, �ٿ��ֱ��� �������� ũ��, ������ �������� �ּ�)  
	strcpy_s(newData->phone, sizeof(newData->phone), phone); //sizeof(�迭�̸�: ù��° �ּҰ� �ȴ�.)
	newData->next = NULL;
	
	if (head == NULL)
		head = newData;
	else
	{
		newData->next = head; //�� �տ� �ְ�, �ص�� ����
		head = newData;
	}
}
int main()
{	
	AddNode(20, "hoon", "010-2222");

	while (head != NULL)
	{
		printf("[%p] %d %s %s [%p]\n", head, head->age, head->name, head->phone, head->next);
		head = head->next;
	}
}