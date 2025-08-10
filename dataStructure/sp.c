#include <stdio.h>
#include <stdlib.h>
//하나의 프로젝트에 여러 파일을 넣는게 분할 컴파일

void Add();

typedef enum MY_MENU { EXIT, NEW, SEARCH, PRINT, REMOVE }MY_MENU;
//0부터 4까지 #define EXIT 0 과 같다.
MY_MENU printMenu()
{
	MY_MENU input = 0;

	system("cls");
	printf("[1]New [2]Search [3]Pint [4]Remove [0]Exit	");
	scanf_s("%d%*c", &input);
	return input; //정수 반환
}
int main()
{
	MY_MENU menu = 0;

	while ((menu = printMenu()) != 0) //이벤트 루프
	{	
		switch (menu)
		{
		case NEW:
			Add(); //이벤트 핸들러, 이벤트 처리기
			break;
		case SEARCH:
			break;
		case PRINT:
			break;
		case REMOVE:
			break;
		default:
			break;
		}
	}
	puts("bye");
	return 0;
}

