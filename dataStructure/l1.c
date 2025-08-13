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

USERDATA* head = NULL; //다음부턴 전역변수 선언 할때 g_ 써주자.

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
		USERDATA* tail = head;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newData;

		//newData->next = head; //맨 앞에 넣고, 헤드로 설정, 근데 이렇게하면 3 2 1 처럼 stack구조로 노드 생성함
		//head = newData;       // 그렇다면 tail를 찾아서 거기다가 계속 갖다주면? 1 2 3 queue 구조 가능!! 위에 보자
	}
}

void Search(const char* name)
{
	USERDATA* sPtr = head;
	//while (sPtr->name != name) //Sptr->name은 배열이다. 문자열비교함수 strcmp(a,b)쓰자.
	while (sPtr != NULL)
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
	USERDATA* mPtr = head; //head를 건드리지말고, 새로운 포인터에 head가 갖고있는 주소를 넣기
	while (mPtr != NULL)
	{
		printf("[%p] %d %s %s [%p]\n", mPtr, mPtr->age, mPtr->name, mPtr->phone, mPtr->next);
		mPtr = mPtr->next; //여기서 head = head->next 이면 마지막에 head에는 NULL주소를 갖음.
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
			if (prePtr == NULL) //앞에 노드가 NULL일 때 == 첫 노드일때 앞에가 비어있으니까 그럼
			{
				head = currentPtr->next;	
			}
			else
			{
				prePtr->next = currentPtr->next;
			}
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
int main()
{	
	InitDummyData();

	printNode();

	searchAndRemove("zzzz");

	printNode();

	//Search("hoon"); //총 4개 찾아보기
	//Search("zoon");
	//Search("aaa");
	//Search("mz");

	//DelNode();
	return 0;
}