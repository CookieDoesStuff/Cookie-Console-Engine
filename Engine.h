/*
Cookie's Console Engine

This engine makes it easier to draw to the screen

there is detailed documentation on the github page
*/

#pragma once

#include <iostream>
#include <Windows.h>
#include <cwchar>
#include <chrono>
#include <string>

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
	WHITE = 0x000F,
	BG_BLACK = 0x0000,
	BG_DARK_BLUE = 0x0010,
	BG_DARK_GREEN = 0x0020,
	BG_DARK_CYAN = 0x0030,
	BG_DARK_RED = 0x0040,
	BG_DARK_MAGENTA = 0x0050,
	BG_DARK_YELLOW = 0x0060,
	BG_GREY = 0x0070,
	BG_DARK_GREY = 0x0080,
	BG_BLUE = 0x0090,
	BG_GREEN = 0x00A0,
	BG_CYAN = 0x00B0,
	BG_RED = 0x00C0,
	BG_MAGENTA = 0x00D0,
	BG_YELLOW = 0x00E0,
	BG_WHITE = 0x00F0
};

enum BlockType
{
	BlockTypeFull = 0x2588,
	BlockTypeShaded1 = 0x00002593,
	BlockTypeShaded2 = 0x2592,
	BlockTypeShaded3 = 0x2591
};

class CookieConsoleEngine
{
private:
	SMALL_RECT r = { 0, 0, 1, 1 };
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
	int* Colour;
	LPCWSTR title;

	int Render()
	{
		WriteConsoleOutput(Console, Canvas, { (short)ScreenWidth, (short)ScreenHeight }, { 0,0 }, &r);
		return 1;
	}

	void Clear()
	{
		for (int y = 0; y < ScreenHeight; y++)
			for (int x = 0; x < ScreenWidth; x++)
			{
				Canvas[y * ScreenWidth + x].Char.UnicodeChar = ' ';
				Canvas[y * ScreenWidth + x].Attributes = 0x0000;
				Colour[y * ScreenWidth + x] = 0x0000;
			}
	}

	void Fill(int StartX, int StartY, int EndX, int EndY, int colour, wchar_t CHAR = BlockTypeFull)
	{
		for (int y = StartY; y < EndY; y++)
			for (int x = StartX; x < EndX; x++)
			{
				Draw(x, y, colour, CHAR);
			}
	}

	int Draw(int x, int y, int colour, wchar_t CHAR = BlockTypeFull)
	{
		if (x > ScreenWidth || x < 0 || y > ScreenHeight || y < 0)
			return 0;

		Canvas[y * ScreenWidth + x].Char.UnicodeChar = CHAR;
		Canvas[y * ScreenWidth + x].Attributes = colour;
		Colour[y * ScreenWidth + x] = colour;
		return 1;
	}

	int Write(int x, int y, std::wstring str, int colour, bool Center = true)
	{
		if (x > ScreenWidth || x < 0 || y > ScreenHeight || y < 0)
			return 0;

		if (Center)
			for (size_t i = 0; i < str.size(); i++)
			{
				Canvas[y * ScreenWidth + x + i - (str.size() / 2)].Char.UnicodeChar = str[i];
				Canvas[y * ScreenWidth + x + i - (str.size() / 2)].Attributes = colour;
				Colour[y * ScreenWidth + x] = colour;
			}
		else
			for (size_t i = 0; i < str.size(); i++)
			{
				Canvas[y * ScreenWidth + x + i].Char.UnicodeChar = str[i];
				Canvas[y * ScreenWidth + x + i].Attributes = colour;
			}
		return 1;
	}

	int GetColour(int x, int y)
	{
		return Colour[y * ScreenWidth + x];
	}

	virtual void RunOnce() = 0;
	virtual void Main(float ElapsedTime) = 0;
private:
	void MainThread()
	{
		RunOnce();
		auto tp1 = std::chrono::system_clock::now();
		auto tp2 = std::chrono::system_clock::now();
		while (1)
		{
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float ElapsedTime = elapsedTime.count();
			std::wstring fps = L" | FPS: " + std::to_wstring((int)(1.0 / ElapsedTime));
			std::wstring WstringTitle(title);
			WstringTitle += fps.c_str();
			SetConsoleTitleW(WstringTitle.c_str());
			Main(ElapsedTime);
		}
	}
public:

	int ConsoleInit(int Width = 120, int Height = 30, LPCWSTR Title = L"Title", int ConsoleFontSize = 8)
	{
		ScreenWidth = Width;
		ScreenHeight = Height;
		FontSize = ConsoleFontSize;
		Canvas = new CHAR_INFO[ScreenWidth * ScreenHeight];
		Colour = new int[ScreenWidth * ScreenHeight];
		title = Title;
		HWND console = GetConsoleWindow();
		Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

		SetConsoleWindowInfo(Console, TRUE, &r);

		COORD coord = { (short)ScreenWidth, (short)ScreenHeight };
		if (!SetConsoleScreenBufferSize(Console, coord))
			Error(L"Could not set the console screen buffer size");

		if (!SetConsoleActiveScreenBuffer(Console))
			return Error(L"Could not activate the screen buffer");

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

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(Console, &csbi))
			return Error(L"Could not get the console screen buffer info");
		if (ScreenHeight > csbi.dwMaximumWindowSize.Y)
			return Error(L"Font Height Too Big");
		if (ScreenWidth > csbi.dwMaximumWindowSize.X)
			return Error(L"Font Width is too big");

		r = { 0, 0, (short)ScreenWidth - 1, (short)ScreenHeight - 1 };
		if (!SetConsoleWindowInfo(Console, TRUE, &r))
			return Error(L"Could not set the console window info");

		for (int i = 0; i < ScreenWidth * ScreenHeight; i++)
		{
			Canvas[i].Char.UnicodeChar = L' ';
			Canvas[i].Attributes = 0x00A0;
		}

		MainThread();

		return 1;
	}
};
