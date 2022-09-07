#include "Engine.h"

class game : public CookieConsoleEngine
{
  //declare the Player object
	Object Player;
	virtual void RunOnce()
	{
    //set the Player x and y to the middle of the screen
		Player.x = ScreenWidth / 2;
		Player.y = ScreenHeight / 2;
		int newline = 0;
    //make the object image a 16 by 16 cube
		for (int i = 0; i < 255; i++)
		{
			newline++;
			if (newline == 16)
			{
				newline = 0;
				Player.Image[i] = IMAGE_NEW_LINE;
			}
			else
				Player.Image[i] = BG_GREEN;
		}
		Player.Image[256] = IMAGE_END;
	}
	virtual void Main(float ElapsedTime)
	{
    //move the player
		if (GetAsyncKeyState('W'))
			Player.y -= 25.0f * ElapsedTime;
		if (GetAsyncKeyState('A'))
			Player.x -= 25.0f * ElapsedTime;
		if (GetAsyncKeyState('S'))
			Player.y += 25.0f * ElapsedTime;
		if (GetAsyncKeyState('D'))
			Player.x += 25.0f * ElapsedTime;
		Clear();
    //with the DrawObject(Object); method draw the object
		DrawObject(Player);
    //and render the screen
		Render();
	}
};

int main()
{
	game game;
	game.ConsoleInit(L"Objects");
	return 0;
}
