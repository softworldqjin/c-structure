#include <stdio.h>

typedef struct USERDATA
{
	int age;
	char name[30];
	char phone[30];
	struct USERDATA* pNext; //구조체 안에서 정의 불가능 struct USERDATA* ptr = NULL;
}USERDATA;
int main()
{
	USERDATA user[4] = {
		{20, "tester1", "010-2222" },
		{21, "tester2", "010-3333"},
		{22, "tester3", "010-4444"},
		{23, "tester4", "010-5555"}
	};

	USERDATA* hptr = &user[0];
	user[0].pNext = &user[1];
	user[1].pNext = &user[2];
	user[2].pNext = &user[3];
	user[3].pNext = NULL;

	while (hptr != NULL)
	{
		printf("[%p] %d %s %s [Next: %p]\n", hptr, hptr->age, hptr->name, hptr->phone, hptr->pNext);
		hptr = hptr->pNext;
	}

}