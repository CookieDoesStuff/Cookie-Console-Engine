#include "Engine.h"

class game : public CookieConsoleEngine
{
	virtual void RunOnce()
	{

	}
	virtual void Main(float ElapsedTime)
	{
		Clear();
		Draw(50, 50, BG_GREEN);
		Fill(25, 25, 35, 35, BG_DARK_RED);
		DrawRect(10, 10, 20, 20, BG_CYAN);
		Write(ScreenWidth / 2, ScreenHeight / 2, L"background green text", GetColour(50, 50));
		Render();
	}
};

int main()
{
	game game;
	game.ConsoleInit(L"Art");
	return 0;
}
