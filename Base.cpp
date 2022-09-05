#include "Engine.h"

class game : public CookieConsoleEngine
{
	virtual void RunOnce()
	{

	}
	virtual void Main(float ElapsedTime)
	{

	}
};

int main()
{
	game game;
	game.ConsoleInit(L"Title");
	return 0;
}
