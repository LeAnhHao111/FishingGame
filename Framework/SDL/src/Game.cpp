#include <stdio.h>
#include <string>
#include <chrono>
#include "Game.h"
#include "GameStateBase.h"
#include "GameStateMachine.h"
#include "Camera.h"
//Screen dimension constants
#include"SDL_mixer.h"
#include"KeyState.h"
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

bool Game::Init()
{
	ResourceManagers::Construct();
	GameStateMachine::Construct();
	Renderer::Construct();
	ResourceManagers::GetInstance()->Init();
	GameStateMachine::GetInstance()->Init();
	bool success = Renderer::GetInstance()->Init();
	GameStateMachine::GetInstance()->PushState(StateType::STATE_INTRO);
	GameStateMachine::GetInstance()->PerformStateChange();
	return success;
}

void Game::Run()
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	std::chrono::steady_clock::time_point lastTime, currTime;
	std::chrono::microseconds elapsed;
	float deltaTime = 0.0f;
	lastTime = std::chrono::steady_clock::now();
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{

			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (GameStateMachine::GetInstance()->HasState())
			{
				GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(e);
			}

			//Handle Touch Event
			if (GameStateMachine::GetInstance()->HasState())
			{
				GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(e);
			}

		}
		if (!GameStateMachine::GetInstance()->HasState())
		{
			quit = true;
		}
		// Handle Key States (instead of Key events)
		/*if (GameStateMachine::GetInstance()->HasState())
		{
			GameStateMachine::GetInstance()->CurrentState()->HandleKeyStates();
		}*/
		KeyState::HandleKeyState();

		currTime = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currTime - lastTime);
		deltaTime = static_cast<double>(elapsed.count()) / 1000000;
		Update(deltaTime);
		// Set updated time
		lastTime = currTime;

		//Update screen
		SDL_RenderPresent(Renderer::GetInstance()->GetRenderer());
	}
}

void Game::Update(float deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();
	if (GameStateMachine::GetInstance()->HasState())
	{
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
		//Clear screen
		SDL_SetRenderDrawColor(Renderer::GetInstance()->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Renderer::GetInstance()->GetRenderer());  // function fills the screen with the color that was last set with SDL_SetRenderDrawColor
		GameStateMachine::GetInstance()->CurrentState()->Draw(Renderer::GetInstance()->GetRenderer());
	}
}


void Game::CleanUp()
{
	ResourceManagers::GetInstance()->CleanUp();
	GameStateMachine::GetInstance()->Cleanup();
	Renderer::GetInstance()->CleanUp();
	ResourceManagers::Destruct();
	GameStateMachine::Destruct();
	Renderer::GetInstance()->Destruct();
	Camera::Destruct();
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

