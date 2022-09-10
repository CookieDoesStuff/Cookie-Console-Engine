//slightly altered version of the originial program
//I just added support for mouse
#include <thread>
#include <fstream>
#include "Engine.h"

class window : public CookieConsoleEngine
{
	int PixelColourBuffer[256] = {0};
	//float CursorY = 0;
	//float CursorX = 0;
	//short Mode = 0;
	short CurrentCol = 16;
	//short CurrentColSelected = 0;
	virtual void RunOnce()
	{
		//initialize mouse input
		MouseInit();
		for (int i = 0; i < 256; i++)
			PixelColourBuffer[i] = BG_BLACK;
	}
	virtual void Main(float ElapsedTime)
	{
		//we dont need this part as I will add mouse input
		/*
		if (GetAsyncKeyState('C'))
			if (Mode == 0)
				Mode = 1;
			else
				Mode = 0;
		if (Mode == 0)
		{
			if (GetAsyncKeyState(VK_RIGHT))
				if (CursorX < 60)
					CursorX += 4;
			if (GetAsyncKeyState(VK_LEFT))
				if (CursorX > 0)
					CursorX -= 4;
			if (GetAsyncKeyState(VK_UP))
				if (CursorY > 0)
					CursorY -= 4;
			if (GetAsyncKeyState(VK_DOWN))
				if (CursorY < 60)
					CursorY += 4;
			if (GetAsyncKeyState(VK_RETURN))
			{
				PixelColourBuffer[(int)(CursorY / 4 * 16 + CursorX / 4)] = CurrentCol;
			}
		}
		else if (Mode == 1)
		{
			if (GetAsyncKeyState(VK_UP))
				if (CurrentColSelected > 0)
				{
					CurrentCol -= 16;
					CurrentColSelected -= 6;
				}
					
			if (GetAsyncKeyState(VK_DOWN))
				if (CurrentColSelected < ScreenHeight - 6)
				{
					CurrentCol += 16;
					CurrentColSelected += 6;
				}
		}
		*/

		if (MousePos.x < 64 && MousePos.x  > 0 && MousePos.y > 0 && MousePos.y < 64)
			if (MouseKeyPressed(MLEFT))
				PixelColourBuffer[MousePos.y / 4 * 16 + MousePos.x / 4] = CurrentCol;
		if (MousePos.x > 70 && MouseKeyPressed(MLEFT))
		{
			CurrentCol = GetColour(MousePos.x, MousePos.y);

		}
		if (GetAsyncKeyState('S'))
		{
			std::ofstream outfile("Object.OBJECT_IMAGE");
			for (int i = 0; i < 255; i++)
				outfile << PixelColourBuffer[i] << " ";
			outfile.close();
		}

		Clear();
		//Draw the ui and the colours
		for (int y = 0; y < 64; y++)
			for (int x = 0; x < 64; x++)
				Fill(x, y, x + 3, y + 3, PixelColourBuffer[y / 4 * 16 + x / 4]);
		Fill(65, 0, 70, 70, BG_WHITE);
		Fill(0, 65, 70, 70, BG_WHITE);
		int y = 0;
		for (int col = 0; col < 240; col += 16)
		{
			Fill(75, y, 80, y + 5, col);
			y += 6;
		}
		//I dont need this part either
		//Draw the cursor
		//Fill(CursorX, CursorY, CursorX + 4, CursorY + 4, BG_WHITE);
		Render();
	}
};

int main()
{
	window window;
	window.ConsoleInit(L"Object Image Creator");
	return 0;
}
