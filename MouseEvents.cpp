#include "Engine.h"

class window : public CookieConsoleEngine
{
	virtual void RunOnce()
	{
		//initialize mouse input
		MouseInit();
		Clear();
	}
	virtual void Main(float ElapsedTime)
	{
		//print the mouse x and y to test mouse detection
		Write(0, 0, L"Mouse X: " + std::to_wstring(MousePos.x), WHITE, false);
		Write(0, 1, L"Mouse Y: " + std::to_wstring(MousePos.y), WHITE, false);
		//another test to see if the mouse position and clicks work
		//to check if the mouse button has been pressed I use MouseKeyPressed method from engine.h(new update)
		//you can also use GetAsyncKeyState(VK_LBUTTON) but i just like it this way, I feel its far simpler
		if (MouseKeyPressed(MLEFT))
			Fill(MousePos.x, MousePos.y, MousePos.x + 2, MousePos.y + 1, BG_CYAN);
		//as I didnt resize the font 1 character isnt 8 by 8 so I fill a square that makes the width and the height of the character equal
		Render();
	}
};

int main()
{
	window window;
	//as I will write text to the screen I dont want to resize the font to 8 by 8
	window.ConsoleInit(L"Mouse Events", 80, 40, 16, false);
	return 0;
}