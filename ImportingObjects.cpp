#include "Engine.h"

class window : public CookieConsoleEngine
{
	Object Player;
	virtual void RunOnce()
	{
  //import the object image using the ImportObjectImage method also we assume that there is a file named Object.OBJECT_IMAGE
  //in the same directory as our source file(you can create object image files easily with Object Image Creator tool that I made)
		Player = ImportObjectImage(Player, L"Object.OBJECT_IMAGE");
    //set the x and y coordinates of the object named Player
		Player.x = 10;
		Player.y = 10;
	}
	virtual void Main(float ElapsedTime)
	{
  //implementing basic movment
		if (GetAsyncKeyState('W'))
			Player.y -= 25.0f * ElapsedTime;
		if (GetAsyncKeyState('A'))
			Player.x -= 25.0f * ElapsedTime;
		if (GetAsyncKeyState('S'))
			Player.y += 25.0f * ElapsedTime;
		if (GetAsyncKeyState('D'))
			Player.x += 25.0f * ElapsedTime;
		Clear();
    //drawing the object Player
		DrawObject(Player);
		Render();
	}
};

int main()
{
	window;
	window.ConsoleInit(L"Importing Objects From Files");
	return 0;
}
