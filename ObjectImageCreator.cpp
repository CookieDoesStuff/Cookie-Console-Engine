/*
I probably wont add mouse input to this(because Im too lazy) but who knows
maybe sometime(probably tomorrow)
*/

#include <thread>
#include <fstream>
#include "Engine.h"

class window : public CookieConsoleEngine
{
	int PixelColourBuffer[256];
	float CursorY = 0;
	float CursorX = 0;
	short Mode = 0;
	short CurrentCol = 0;
	short CurrentColSelected = 0;
	virtual void RunOnce()
	{
		for (int i = 0; i < 256; i++)
			PixelColourBuffer[i] = BG_BLACK;
	}
	virtual void Main(float ElapsedTime)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

		Clear();
		//Draw the ui and the colours
		for (int y = 0; y < 64; y++)
			for (int x = 0; x < 64; x++)
				Fill(x, y, x + 3, y + 3, PixelColourBuffer[y / 4 * 16 + x / 4]);
		Fill(65, 0, 70, 70, BG_WHITE);
		Fill(0,65, 70, 70, BG_WHITE);
		int y = 0;
		for (int col = 0; col < 240; col += 16)
		{
			Fill(75, y, 80, y + 5, col);
			y += 6;
			DrawRect(74, CurrentColSelected, 80, CurrentColSelected + 5, BG_WHITE);
		}
		//Draw the cursor
		Fill(CursorX, CursorY, CursorX + 4, CursorY + 4, BG_WHITE);
		Render();

		std::ofstream outfile("Object.OBJECT_IMAGE");
		for (int i = 0; i < 255; i++)
			outfile << PixelColourBuffer[i] << " ";
		outfile.close();
	}
};

int main()
{
	window window;
	window.ConsoleInit(L"Object Image Creator");
	return 0;
}
