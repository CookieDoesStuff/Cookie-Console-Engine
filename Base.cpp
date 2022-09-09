#include "Engine.h"

class window : public CookieConsoleEngine
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
	window window;
	window.ConsoleInit(L"Title");
	return 0;
}
