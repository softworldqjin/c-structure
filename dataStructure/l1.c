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

USERDATA* head = NULL; //�������� �������� ���� �Ҷ� g_ ������.

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
		USERDATA* tail = head;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newData;

		//newData->next = head; //�� �տ� �ְ�, ���� ����, �ٵ� �̷����ϸ� 3 2 1 ó�� stack������ ��� ������
		//head = newData;       // �׷��ٸ� tail�� ã�Ƽ� �ű�ٰ� ��� �����ָ�? 1 2 3 queue ���� ����!! ���� ����
	}
}

void Search(const char* name)
{
	USERDATA* sPtr = head;
	//while (sPtr->name != name) //Sptr->name�� �迭�̴�. ���ڿ����Լ� strcmp(a,b)����.
	while (sPtr != NULL)
	{
		if (strcmp(sPtr->name, name) == 0)
		{
			printf("%s�� �ֽ��ϴ�.\n", name);
			return;
		}
		else
			sPtr = sPtr->next;
	}
	printf("%s�� �����ϴ�.\n", name);
	
}
void DelNode()
{
	USERDATA* pData = head;
	USERDATA* pTemp;
	while (pData != NULL)
	{
		pTemp = pData->next;
		printf("del: [%p] %d %s %s\n", pData, pData->age, pData->name, pData->phone);
		free(pData);
		pData = pTemp;
	}
	pTemp = NULL;

}
void InitDummyData()
{
	AddNode(20, "hoon", "010-2222");
	AddNode(30, "jjjj", "010-3333");
	AddNode(30, "zzzz", "010-4444");
}
void printNode()
{
	USERDATA* mPtr = head; //head�� �ǵ帮������, ���ο� �����Ϳ� head�� �����ִ� �ּҸ� �ֱ�
	while (mPtr != NULL)
	{
		printf("[%p] %d %s %s [%p]\n", mPtr, mPtr->age, mPtr->name, mPtr->phone, mPtr->next);
		mPtr = mPtr->next; //���⼭ head = head->next �̸� �������� head���� NULL�ּҸ� ����.
	}

}
void searchAndRemove(const char* name)
{
	USERDATA* currentPtr = head;
	USERDATA* prePtr = NULL;

	while (currentPtr != NULL)
	{
		if (strcmp(currentPtr->name, name) == 0)
		{
			if (prePtr == NULL) //�տ� ��尡 NULL�� �� == ù ����϶� �տ��� ��������ϱ� �׷�
			{
				head = currentPtr->next;	
			}
			else
			{
				prePtr->next = currentPtr->next;
			}
			printf("%s �����Ϸ�\n", currentPtr->name);
			free(currentPtr);
			return;
		}
		else
			prePtr = currentPtr;
			currentPtr = currentPtr->next;
	}
	printf("%s�� �������� �ʽ��ϴ�.\n", name);
}
int main()
{	
	InitDummyData();

	printNode();

	searchAndRemove("zzzz");

	printNode();

	//Search("hoon"); //�� 4�� ã�ƺ���
	//Search("zoon");
	//Search("aaa");
	//Search("mz");

	//DelNode();
	return 0;
}