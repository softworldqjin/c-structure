#include <stdio.h>
#include <stdlib.h>
//�ϳ��� ������Ʈ�� ���� ������ �ִ°� ���� ������

void Add();

typedef enum MY_MENU { EXIT, NEW, SEARCH, PRINT, REMOVE }MY_MENU;
//0���� 4���� #define EXIT 0 �� ����.
MY_MENU printMenu()
{
	MY_MENU input = 0;

	system("cls");
	printf("[1]New [2]Search [3]Pint [4]Remove [0]Exit	");
	scanf_s("%d%*c", &input);
	return input; //���� ��ȯ
}
int main()
{
	MY_MENU menu = 0;

	while ((menu = printMenu()) != 0) //�̺�Ʈ ����
	{	
		switch (menu)
		{
		case NEW:
			Add(); //�̺�Ʈ �ڵ鷯, �̺�Ʈ ó����
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

