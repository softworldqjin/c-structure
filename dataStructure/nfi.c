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
	fopen_s(&fp, "listData.dat", "wb"); //포인터 변수의 주소, 파일 이름, 쓰기모드
	if (fp == NULL) //안열렸으면
	{
		puts("ERROR: Failed to open listData.dat"); //자동 개행
		return 0;
	}
	
	while (head != NULL)
	{
		fwrite(head, sizeof(USERDATA), 1, fp); //쓰고 싶은 데이터가 있는 메모리 주소, 한 개 데이터의 크기, 몇개 쓸건지, 쓸 파일의 주소
		head = head->next;
	}	//fp(파일)에 다 써넣을거임.

	fclose(fp);
	return 0;
}