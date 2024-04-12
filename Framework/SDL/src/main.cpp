#include"Game.h"
#include <stdio.h>

int main(int argc, char* args[])
{
	//Start up SDL and create window
	Game::Construct();
	Game::GetInstance()->Init();
	Game::GetInstance()->Run();
	//Free resources and close SDL
	Game::GetInstance()->CleanUp();
	Game::Destruct();
	return 0;
}