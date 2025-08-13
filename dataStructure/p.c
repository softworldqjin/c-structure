#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct USERDATA
{
	int age;
	char name[30];
	char phone[30];
	struct USERDATA* prev;
	struct USERDATA* next;
}USERDATA;


//USERDATA* head = NULL; //�������� �������� ���� �Ҷ� g_ ������.
USERDATA g_head = { 0, "dummy_node" };
USERDATA g_tail = { 0, "tail_node" };

void ConnectHeadTail()
{
	g_head.next = &g_tail;
	g_tail.prev = &g_head;
}

void AddNode(int age, char* name, char* phone)
{
	USERDATA* newData = (USERDATA*)malloc(sizeof(USERDATA));
	newData->age = age;
	//newData->name = name // �ּҴ� R-value�̴ϱ� L-value�� �ɼ�����
	strcpy_s(newData->name, sizeof(newData->name), name); //�ٿ��ֱ��� �������� �ּ�, �ٿ��ֱ��� �������� ũ��, ������ �������� �ּ�)  
	strcpy_s(newData->phone, sizeof(newData->phone), phone); //sizeof(�迭�̸�: ù��° �ּҰ� �ȴ�.)
	newData->prev = NULL;
	newData->next = NULL;

	//��� ������ ��带 ã�Ƽ� queue���� �̾��ָ� �ǰڴ� 1 < 2 < 3 < 4
	USERDATA* lastNode = g_tail.prev; //������ �ڵ忡 ���ο� ��� �ּҸ� lastNode�����Ϳ� �־�����? �����ʿ䰡���µ�, g_tail.prev��
	lastNode->next = newData;
	newData->prev = lastNode;

	newData->next = &g_tail;
	g_tail.prev = newData;

	/*USERDATA* tail = &g_head;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	tail->next = newData;*/

	//newData->next = head; //�� �տ� �ְ�, ���� ����, �ٵ� �̷����ϸ� 3 2 1 ó�� stack������ ��� ������
	//head = newData;       // �׷��ٸ� tail�� ã�Ƽ� �ű�ٰ� ��� �����ָ�? 1 2 3 queue ���� ����!! ���� ����
}

void Search(const char* name)
{
	USERDATA* sPtr = &g_head;
	//while (sPtr->name != name) //Sptr->name�� �迭�̴�. ���ڿ����Լ� strcmp(a,b)����.
	while (sPtr->next != NULL)
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
	USERDATA* pData = &g_head;
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
	AddNode(20, "zoon", "010-3333");
	AddNode(20, "koon", "010-3333");
}
void printNode() //g_tail ������� �ʵ��� �ݺ��� ���� �ٲ�ߵ�
{
	USERDATA* mPtr = &g_head; //head�� �ǵ帮������, ���ο� �����Ϳ� head�� �����ִ� �ּҸ� �ֱ�
	mPtr = mPtr->next;
	while (mPtr != &g_tail)
	{
		printf("[%p] %d %s %s [%p]\n", mPtr, mPtr->age, mPtr->name, mPtr->phone, mPtr->next);
		mPtr = mPtr->next; //���⼭ head = head->next �̸� �������� head���� NULL�ּҸ� ����.
	}

}
void searchAndRemove(const char* name)
{
	USERDATA* currentPtr = &g_head;
	currentPtr = currentPtr->next;
	USERDATA* prePtr = &g_head;

	while (currentPtr != NULL)
	{
		if (strcmp(currentPtr->name, name) == 0)
		{
			prePtr->next = currentPtr->next;

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

USERDATA* Pop()
{
	USERDATA* pPop = g_head.next;
	g_head.next = pPop->next;
	pPop->next->prev = pPop;

	return pPop;
}
void Push(USERDATA* pPush)
{
	USERDATA* newData = (USERDATA*)malloc(sizeof(USERDATA));
	memcpy(newData, pPush, sizeof(USERDATA));

	//������
	USERDATA* lastNode = g_head.next;

	g_head.next = newData;
	newData->prev = &g_head;

	newData->next = lastNode;
	lastNode->prev = newData;

}

int main()
{
	USERDATA user1 = { 10, "james", "010-2222" };
	USERDATA user2 = { 20, "mk", "010-3333" };
	ConnectHeadTail();
	Push(&user1);
	Push(&user2);
	
	printNode();

	for (int i = 0; i < 2; ++i)
	{
		USERDATA* pPop = Pop();
		printf("%d %s %s\n", pPop->age, pPop->name, pPop->phone);
		free(pPop);
	}

	return 0;
}