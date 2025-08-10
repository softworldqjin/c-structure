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
	//newData->name = name // 주소는 R-value이니까 L-value가 될수없음
	strcpy_s(newData->name, sizeof(newData->name), name); //붙여넣기할 데이터의 주소, 붙여넣기할 데이터의 크기, 복사할 데이터의 주소)  
	strcpy_s(newData->phone, sizeof(newData->phone), phone); //sizeof(배열이름: 첫번째 주소가 된다.)
	newData->next = NULL;
	
	if (head == NULL)
		head = newData;
	else
	{
		newData->next = head; //맨 앞에 넣고, 해드로 설정
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