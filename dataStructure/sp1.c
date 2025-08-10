#include <stdio.h>
#include <conio.h>

void Add()
{
	puts("Add()");
	puts("press any key");
	_getch(); //한 글자를 입력받는데, 엔터키 누를 필요없이 반환
				// 입력한 문자가 화면에 출력되지 않음.
}