#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager/Singleton.h"
#include <SDL_ttf.h>
class Renderer : public SingletonDclp<Renderer>{
public:
	bool Init();
	void CleanUp();
	SDL_Window* GetWindow();
	void SetWindow(SDL_Window* mWindow);
	SDL_Renderer* GetRenderer();
	void SetRenderer(SDL_Renderer* mRenderer);
private:
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	TTF_Font* gFont;
};