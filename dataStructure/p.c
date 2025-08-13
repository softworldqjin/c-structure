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


//USERDATA* head = NULL; //다음부턴 전역변수 선언 할때 g_ 써주자.
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
	//newData->name = name // 주소는 R-value이니까 L-value가 될수없음
	strcpy_s(newData->name, sizeof(newData->name), name); //붙여넣기할 데이터의 주소, 붙여넣기할 데이터의 크기, 복사할 데이터의 주소)  
	strcpy_s(newData->phone, sizeof(newData->phone), phone); //sizeof(배열이름: 첫번째 주소가 된다.)
	newData->prev = NULL;
	newData->next = NULL;

	//계속 마지막 노드를 찾아서 queue마냥 이어주면 되겠다 1 < 2 < 3 < 4
	USERDATA* lastNode = g_tail.prev; //마지막 코드에 새로운 노드 주소를 lastNode포인터에 넣어주자? 넣을필요가없는데, g_tail.prev라서
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

	//newData->next = head; //맨 앞에 넣고, 헤드로 설정, 근데 이렇게하면 3 2 1 처럼 stack구조로 노드 생성함
	//head = newData;       // 그렇다면 tail를 찾아서 거기다가 계속 갖다주면? 1 2 3 queue 구조 가능!! 위에 보자
}

void Search(const char* name)
{
	USERDATA* sPtr = &g_head;
	//while (sPtr->name != name) //Sptr->name은 배열이다. 문자열비교함수 strcmp(a,b)쓰자.
	while (sPtr->next != NULL)
	{
		if (strcmp(sPtr->name, name) == 0)
		{
			printf("%s이 있습니다.\n", name);
			return;
		}
		else
			sPtr = sPtr->next;
	}
	printf("%s이 없습니다.\n", name);

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
void printNode() //g_tail 출력하지 않도록 반복문 조건 바꿔야됨
{
	USERDATA* mPtr = &g_head; //head를 건드리지말고, 새로운 포인터에 head가 갖고있는 주소를 넣기
	mPtr = mPtr->next;
	while (mPtr != &g_tail)
	{
		printf("[%p] %d %s %s [%p]\n", mPtr, mPtr->age, mPtr->name, mPtr->phone, mPtr->next);
		mPtr = mPtr->next; //여기서 head = head->next 이면 마지막에 head에는 NULL주소를 갖음.
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

			printf("%s 삭제완료\n", currentPtr->name);
			free(currentPtr);
			return;
		}
		else
			prePtr = currentPtr;
		currentPtr = currentPtr->next;
	}
	printf("%s는 존재하지 않습니다.\n", name);
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

	//만들자
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