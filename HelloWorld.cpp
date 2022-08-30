//include the header file
#include "Engine.h"

//make a class that inherits from the engine
class game : public CookieConsoleEngine 
{
 	//in this part we need to overwrite 2 methods so that our program works

  	//the RunOnce() method only runs once when the program starts
	virtual void RunOnce()
	{

	}
  
  	//the Main() method runs each tick of the prorgram
	virtual void Main(float ElapsedTime)
	{
   		//here I just get the fps and write the fps at x: 10 y: 10 coordinates
    		int fps = (int)(1.0f / ElapsedTime);
		Write(10, 10, L"FPS: " + fps, GREEN, false);
    		//dont forget to render the screen or else nothing will show up
		Render();
	}
};

int main()
{
	game game;
  	//create the console window in this case im creating a 120 by 120 window with the title of "Hello World!" and resizing the font to 8 so each character will be 8 by 8
	game.ConsoleInit(120, 120, L"Hello World!", 8);
	return 0;
}
