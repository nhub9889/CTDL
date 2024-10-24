#include <stdio.h>
#include <conio.h>
#include "console.h"
#include <windows.h>  // Required for Windows API functions



int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

void closeConsole() {
	HWND consoleWindow = GetConsoleWindow();  // Get the handle to the console window
	if (consoleWindow != NULL) {
		DestroyWindow(consoleWindow);  // Close the console window
	}
}
//-------------------------Screen-------------------------
void clrscrA()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	COORD Home = { 0,0 };
	DWORD dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	// Xóa toàn bộ nội dung của console
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);

	// Đặt thuộc tính màu sắc về mặc định
	FillConsoleOutputAttribute(hConsoleOut, csbiInfo.wAttributes, csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy); // Màu trắng

	// Đặt lại vị trí con trỏ về (0,0)
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}


	void clrscr()
	{
		CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
		HANDLE	hConsoleOut;
		COORD	Home = { 0,0 };
		DWORD	dummy;

		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

		FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
		csbiInfo.dwCursorPosition.X = 0;
		csbiInfo.dwCursorPosition.Y = 0;
		SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
	}




//screen: goto [x,y]
void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


//screen: get [x]
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}


//screen: get [y]
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}


void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}