#pragma once

#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <fstream>

using namespace std;

enum COLOUR
{
	BLACK = 0x0000,
	DARK_BLUE = 0x0001,
	DARK_GREEN = 0x0002,
	DARK_CYAN = 0x0003,
	DARK_RED = 0x0004,
	DARK_MAGENTA = 0x0005,
	DARK_YELLOW = 0x0006,
	GREY = 0x0007,
	DARK_GREY = 0x0008,
	BLUE = 0x0009,
	GREEN = 0x000A,
	CYAN = 0x000B,
	RED = 0x000C,
	MAGENTA = 0x000D,
	YELLOW = 0x000E,
	WHITE = 0x000F
};

enum BlockType
{
	BlockTypeFull = 0x2588,
	BlockTypeShaded1 = 0x00002593,
	BlockTypeShaded2 = 0x2592,
	BlockTypeShaded3 = 0x2591
};

class CookieConsoleGameEngine
{
private:
	int Error(const wchar_t* Error)
	{
		wchar_t buf[256];
		wprintf(buf, L"Error: ", Error);
		return 0;
	}

public:
	int ScreenWidth;
	int ScreenHeight;
	int FontSize;
	HANDLE Console;
	CHAR_INFO* Canvas;
	SMALL_RECT r = { 0, 0, 1, 1 };

	void Render()
	{
		WriteConsoleOutput(Console, Canvas, { (short)ScreenWidth, (short)ScreenHeight }, { 0,0 }, &r);
	}

	void Clear()
	{
		for (int Y = 0; Y < ScreenHeight; Y++)
			for (int X = 0; X < ScreenWidth; X++)
			{
				Canvas[Y * ScreenWidth + X].Char.UnicodeChar = L' ';
				Canvas[Y * ScreenWidth + X].Attributes = 0x0000;
			}
	}

	void Fill(int StartX, int StartY, int EndX, int EndY, int colour, wchar_t CHAR = BlockTypeFull)
	{
		for (int Y = StartY; Y < EndY; Y++)
			for (int X = StartX; X < EndX; X++)
			{
				Canvas[Y * ScreenWidth + X].Char.UnicodeChar = CHAR;
				Canvas[Y * ScreenWidth + X].Attributes = colour;
			}
	}

	void Draw(int X, int Y, int colour, wchar_t CHAR = BlockTypeFull)
	{
		if (X > ScreenWidth)
			X = ScreenWidth;
		if (Y > ScreenHeight)
			Y = ScreenHeight;
		Canvas[Y * ScreenWidth + X].Char.UnicodeChar = CHAR;
		Canvas[Y * ScreenWidth + X].Attributes = colour;
	}

	void Write(int X, int Y, std::wstring str, int colour, bool Center = true)
	{
		if (Center)
			for (size_t i = 0; i < str.size(); i++)
			{
				Canvas[Y * ScreenWidth + X + i - (str.size() / 2)].Char.UnicodeChar = str[i];
				Canvas[Y * ScreenWidth + X + i - (str.size() / 2)].Attributes = colour;
			}
		else
			for (size_t i = 0; i < str.size(); i++)
			{
				Canvas[Y * ScreenWidth + X + i].Char.UnicodeChar = str[i];
				Canvas[Y * ScreenWidth + X + i].Attributes = colour;
			}
		
	}

	int ConsoleConstruct(int Width = 120, int Height = 30, LPCWSTR Title = L"Title", int ConsoleFontSize = 8, bool ResizeFont = true)
	{
		ScreenWidth = Width;
		ScreenHeight = Height;
		FontSize = ConsoleFontSize;
		Canvas = new CHAR_INFO[ScreenWidth * ScreenHeight];
		memset(Canvas, 0, sizeof(CHAR_INFO) * ScreenWidth * ScreenHeight);
		HWND console = GetConsoleWindow();
		Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		SetConsoleWindowInfo(Console, TRUE, &r);

		COORD coord = { (short)ScreenWidth, (short)ScreenHeight };
		if (!SetConsoleScreenBufferSize(Console, coord))
			Error(L"Could not set the console screen buffer size");

		if (!SetConsoleActiveScreenBuffer(Console))
			return Error(L"Could not activate the screen buffer");

		if (ResizeFont)
		{
			CONSOLE_FONT_INFOEX cfi;
			cfi.cbSize = sizeof(cfi);
			cfi.nFont = 0;
			cfi.dwFontSize.X = ConsoleFontSize;
			cfi.dwFontSize.Y = ConsoleFontSize;
			cfi.FontFamily = FF_DONTCARE;
			cfi.FontWeight = FW_NORMAL;

			wcscpy_s(cfi.FaceName, L"Consolas");
			if (!SetCurrentConsoleFontEx(Console, false, &cfi))
				return Error(L"Could not set the font size");
		}
		else
		{
			CONSOLE_FONT_INFOEX cfi;
			cfi.cbSize = sizeof(cfi);
			cfi.nFont = 0;
			cfi.dwFontSize.X = FontSize / 2;
			cfi.dwFontSize.Y = FontSize;
			cfi.FontFamily = FF_DONTCARE;
			cfi.FontWeight = FW_NORMAL;

			wcscpy_s(cfi.FaceName, L"Consolas");
			if (!SetCurrentConsoleFontEx(Console, false, &cfi))
				return Error(L"Could not set the font size");
		}

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(Console, &csbi))
			return Error(L"Could not get the console screen buffer info");
		if (ScreenHeight > csbi.dwMaximumWindowSize.Y)
			return Error(L"Font Height Too Big");
		if (ScreenWidth > csbi.dwMaximumWindowSize.X)
			return Error(L"Font Width is too big");

		// Set Physical Console Window Size
		r = { 0, 0, (short)ScreenWidth - 1, (short)ScreenHeight - 1 };
		if (!SetConsoleWindowInfo(Console, TRUE, &r))
			return Error(L"Could not set the console window info");

		for (int i = 0; i < ScreenWidth * ScreenHeight; i++)
			Canvas[i].Char.UnicodeChar = L' ';

		if (!SetConsoleTitleW(Title))
			return Error(L"Could not set the window title");

		return 1;
	}
};
