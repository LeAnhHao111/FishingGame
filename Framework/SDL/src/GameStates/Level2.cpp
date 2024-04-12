#include "Level2.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "BaseObject.h"
#include "SDL.h"
#include <cstdlib>
#include <vector>
#include "Fish.h"




Level2::Level2()
{
}

Level2::~Level2()
{
}

// Check va cham
bool Level2::CheckCollision(std::shared_ptr<SpriteAnimation> sprite1, std::shared_ptr<Fish> sprite2)
{
	float sprite1Left = sprite1->Get2DPosition().x - (sprite1->GetWidth() / 2.0f);
	float sprite1Right = sprite1->Get2DPosition().x + (sprite1->GetWidth() / 2.0f);
	float sprite1Top = sprite1->Get2DPosition().y - (sprite1->GetHeight() / 2.0f);
	float sprite1Bottom = sprite1->Get2DPosition().y + (sprite1->GetHeight() / 2.0f);

	float sprite2Left = sprite2->Get2DPosition().x - (sprite2->GetWidth() / 2.0f);
	float sprite2Right = sprite2->Get2DPosition().x + (sprite2->GetWidth() / 2.0f);
	float sprite2Top = sprite2->Get2DPosition().y - (sprite2->GetHeight() / 2.0f);
	float sprite2Bottom = sprite2->Get2DPosition().y + (sprite2->GetHeight() / 2.0f);

	if (sprite1Right >= sprite2Left && sprite1Left <= sprite2Right && sprite1Bottom >= sprite2Top && sprite1Top <= sprite2Bottom)
	{
		return true;
	}

	return false;
}

void Level2::CheckHookCollision()
{
	for (auto it = m_fish.begin(); it != m_fish.end(); )
	{
		auto fish = *it;
		if (CheckCollision(obj_hook, fish))
		{
			fish->SetFlip(SDL_FLIP_NONE);
			fish->Set2DPosition(obj_hook->Get2DPosition().x, obj_hook->Get2DPosition().y);
			break;

		}
		else
		{
			++it;
		}
	}
}



void Level2::Init()
{

	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_sea2.jpg");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("close.png");
	buttonclose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonclose->SetSize(50, 50);
	buttonclose->Set2DPosition(SCREEN_WIDTH - 50, 10);
	buttonclose->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(buttonclose);

	// button continue
	texture = ResourceManagers::GetInstance()->GetTexture("bt_next.png");
	buttonnext = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonnext->SetSize(50, 50);
	buttonnext->Set2DPosition((SCREEN_WIDTH - buttonnext->GetWidth()) / 2, (SCREEN_HEIDHT - buttonnext->GetHeight()) / 2 + 50);
	buttonnext->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PushState(StateType::LEVEL3);
		});

	texture = ResourceManagers::GetInstance()->GetTexture("bt_replay.png");
	buttonreplay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonreplay->SetSize(50, 50);
	buttonreplay->Set2DPosition((SCREEN_WIDTH - buttonreplay->GetWidth()) / 2 - 75, (SCREEN_HEIDHT - buttonreplay->GetHeight()) / 2 + 50);
	buttonreplay->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PushState(StateType::STATE_PLAY);
		});

	texture = ResourceManagers::GetInstance()->GetTexture("bt_home.png");
	buttonhome = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	buttonhome->SetSize(50, 50);
	buttonhome->Set2DPosition((SCREEN_WIDTH - buttonhome->GetWidth()) / 2 + 75, (SCREEN_HEIDHT - buttonhome->GetHeight()) / 2 + 50);
	buttonhome->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});

	// Animation 


	texture = ResourceManagers::GetInstance()->GetTexture("Fisherman_fish.png");
	obj_actor = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	obj_actor->SetFlip(SDL_FLIP_HORIZONTAL);
	obj_actor->SetSize(64, 64);
	obj_actor->Set2DPosition(538, 48);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj_actor);


	texture = ResourceManagers::GetInstance()->GetTexture("hook.png");
	obj_hook = std::make_shared<SpriteAnimation>(texture, 1, 5, 1, 0.2f);
	obj_hook->SetSize(15, 15);
	obj_hook->Set2DPosition(538, 108);
	//Camera::GetInstance()->SetTarget(obj);

	texture = ResourceManagers::GetInstance()->GetTexture("Boat.png");
	obj_boat = std::make_shared<SpriteAnimation>(texture, 1, 1, 1, 0.0f);
	obj_boat->SetSize(100, 25);
	obj_boat->Set2DPosition(538, 90);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj_boat);

	//Fish
	for (int i = 1; i <= 28; i++) {

		m_pos.x = rand() % (1100 - 50 + 1) + 50;
		m_pos.y = rand() % (600 - 200 + 1) + 200;

		switch (i % 6)
		{
		case 0:
		{
			auto fish0 = std::make_shared<Fish>(Fish1);
			texture = ResourceManagers::GetInstance()->GetTexture("fish2.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
			fish0->SetSize(32, 24);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			m_fish.push_back(fish0);
			break;
		}
		case 1:
		{
			auto fish0 = std::make_shared<Fish>(Fish2);
			texture = ResourceManagers::GetInstance()->GetTexture("fish3.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
			fish0->SetSize(40, 24);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			fish0->m_fishAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
			m_fish.push_back(fish0);
			break;
		}
		case 2:
		{
			auto fish0 = std::make_shared<Fish>(Fish3);
			texture = ResourceManagers::GetInstance()->GetTexture("fish4.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
			fish0->SetSize(52, 24);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			m_fish.push_back(fish0);
			break;
		}
		case 3:
		{
			auto fish0 = std::make_shared<Fish>(Fish4);
			texture = ResourceManagers::GetInstance()->GetTexture("fish5.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 2, 1, 0.2f);
			fish0->SetSize(56, 48);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			fish0->m_fishAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
			m_fish.push_back(fish0);
			break;
		}
		case 4:
		{
			auto fish0 = std::make_shared<Fish>(TRASH1);
			texture = ResourceManagers::GetInstance()->GetTexture("trash1.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
			fish0->SetSize(40, 40);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			m_fish.push_back(fish0);
			break;
		}
		case 5:
		{
			auto fish0 = std::make_shared<Fish>(TRASH3);
			texture = ResourceManagers::GetInstance()->GetTexture("trash3.png");
			fish0->m_fishAnimation = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
			fish0->SetSize(40, 40);
			fish0->Set2DPosition(m_pos.x, m_pos.y);
			fish0->m_fishAnimation->SetFlip(SDL_FLIP_HORIZONTAL);
			m_fish.push_back(fish0);
			break;
		}
		default:
			break;
		}
	}

	m_KeyPress = 0;

	//Text
	m_textColor = { 255, 255, 255 };
	m_textScore = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textScore->SetSize(112, 16);
	m_textScore->Set2DPosition(5, 10);
	m_textScore->LoadFromRenderText("Score:  ");

	m_textColor = { 255, 255, 255 };
	m_textMission = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textMission->SetSize(176, 16);
	m_textMission->Set2DPosition(5, 36);
	m_textMission->LoadFromRenderText("Mission: 850");

	m_textColor = { 255, 255, 255 };
	m_textLevel = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textLevel->SetSize(96, 16);
	m_textLevel->Set2DPosition(5, 62);
	m_textLevel->LoadFromRenderText("Level: 2");

	m_textColor = { 255, 255, 255 };
	m_textTime = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textTime->SetSize(120, 16);
	m_textTime->Set2DPosition((SCREEN_WIDTH - m_textTime->GetWidth()) / 2, 10);

	m_textColor = { 255, 255, 0 };
	m_textend = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textend->SetSize(400, 50);
	m_textend->Set2DPosition((SCREEN_WIDTH - m_textend->GetWidth()) / 2, (SCREEN_HEIDHT - m_textend->GetHeight()) / 2);

	m_currentPlayerState = PlayerState2::IDLE2;

	m_Soundsongbien = std::make_shared<Sound>();
	m_Soundsongbien->LoadSound("Data/Sounds/songbien.mp3");
	m_Soundsongbien->PlaySound();
	m_Soundstart.PlaySfx(sfxIndex1, 0);

	m_currentFishWeight = 0.0f;
	m_currentFishValue = 0.0f;
	m_biteDepth = 0.0f;

}


void Level2::Exit()
{
}


void Level2::Pause()
{

}
void Level2::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void Level2::HandleEvents()
{
}

void Level2::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN)// && e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			printf("MOVE LEFT");
			m_KeyPress |= 1;
			break;
		case SDLK_DOWN:
			printf("MOVE BACK");
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP)//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}


void Level2::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void Level2::HandleMouseMoveEvents(int x, int y)
{
}

void Level2::Update(float deltaTime)
{
	KeyState::HandleKeyState();

	// button update
	for (auto& it : m_listButton)
	{
		it->Update(deltaTime);
	}

	// animation update
	for (auto& it : m_listAnimation)
	{
		if (m_KeyPress == 1)
		{

			//	it->MoveLeft(deltaTime);
		}
		it->Update(deltaTime);
	}

	// update fish animation
	for (auto& it : m_fish)
	{
		it->Update(deltaTime);

		char flip = it->GetFlip();

		if (flip == SDL_FLIP_NONE && !it->bite)
		{
			it->MoveFish(deltaTime);
		}
		else if (flip == SDL_FLIP_HORIZONTAL && !it->bite)
		{
			it->MoveFish2(deltaTime);
		}
		if (it->bite)
		{
			it->Set2DPosition(obj_hook->Get2DPosition().x - 10.0f, obj_hook->Get2DPosition().y);
		}
	}

	// update hook animation
	obj_hook->Update(deltaTime);

	switch (m_KeyPress)
	{
	case 1: // left 
		if (m_currentPlayerState & (PlayerState2::IDLE2 | MOVE_RIGHT2))
		{
			m_currentPlayerState = PlayerState2::MOVE_LEFT2;
		}
		break;
	case 1 << 1: // down
		if (m_currentPlayerState & (PlayerState2::IDLE2 | PlayerState2::MOVE_LEFT2 | PlayerState2::MOVE_RIGHT2))
		{
			m_currentPlayerState = PlayerState2::CAST2;
		}
		break;
	case 1 << 2: // right
		if (m_currentPlayerState & (PlayerState2::IDLE2 | MOVE_LEFT2))
		{
			m_currentPlayerState = PlayerState2::MOVE_RIGHT2;
		}
		break;
	case 1 << 3: // up

		break;
	default:
		break;
	}

	// not moving & reel or cast -> idle
	if (!(m_KeyPress & 0b101) && // none of left and right are pressed
		!(m_currentPlayerState & (PlayerState2::CAST2 | REEL2))) // not casting or reeling
	{
		m_currentPlayerState = PlayerState2::IDLE2;
	}

	// perform action
	switch (m_currentPlayerState)
	{
	case PlayerState2::IDLE2:
		break;
	case PlayerState2::MOVE_LEFT2:
		obj_boat->MoveLeft(deltaTime);
		obj_actor->MoveLeft(deltaTime);
		obj_hook->MoveLeft(deltaTime);
		break;
	case PlayerState2::MOVE_RIGHT2:
		obj_boat->MoveRight(deltaTime);
		obj_actor->MoveRight(deltaTime);
		obj_hook->MoveRight(deltaTime);
		break;
	case PlayerState2::CAST2:
		obj_hook->MoveDown(deltaTime);
		m_Soundkeocan.PlaySfx(sfxIndex, 0);

		// reach bottom
		if (obj_hook->Get2DPosition().y >= 600.0f)
		{
			m_currentPlayerState = PlayerState2::REEL2;
			break;
		}

		for (auto& this_fish : m_fish)
		{
			// collide with fish
			if (CheckCollision(obj_hook, this_fish))
			{
				this_fish->bite = true;
				m_currentPlayerState = PlayerState2::REEL2;
				m_currentFishWeight = this_fish->GetWeight();
				m_currentFishValue = this_fish->GetValue();
				m_biteDepth = this_fish->Get2DPosition().y;
				break;
			}
		}
		break;
	case PlayerState2::REEL2:
	{
		float speed = 500.0f;
		float reel_speed_multiplier = 1.0f;
		float value_multiplier = 1.0f;
		reel_speed_multiplier = (m_currentFishWeight >= 3 && m_currentFishWeight <= 7) ? 0.7f : reel_speed_multiplier;
		reel_speed_multiplier = m_currentFishWeight >= 7 ? 0.4f : reel_speed_multiplier;
		obj_hook->MoveUp(deltaTime, speed * reel_speed_multiplier);
		m_Soundkeocan.PlaySfx(sfxIndex, 0);

		// reel to boat
		if (obj_hook->Get2DPosition().y <= 108)
		{
			auto hook_pos = obj_hook->Get2DPosition();
			obj_hook->Set2DPosition(hook_pos.x, 108);

			// remove caught fish
			for (auto it = m_fish.begin(); it != m_fish.end(); /* No increment here */) {
				if ((*it)->bite) {
					// set bonus score multiplier
					value_multiplier = (m_biteDepth >= 300 && m_biteDepth <= 500) ? 1.5f : value_multiplier;
					value_multiplier = (m_biteDepth >= 500 && m_biteDepth <= 600) ? 2.0f : value_multiplier;
					value_multiplier = m_biteDepth >= 600 ? 3.0f : value_multiplier;

					// increase score
					if (!m_isMissionCompleted)
					{
						m_score += (*it)->GetValue() * value_multiplier;
					}
					// Remove the fish from the list
					it = m_fish.erase(it);
					m_currentFishWeight = 0.0f;
					m_currentFishValue = 0.0f;
					m_biteDepth = 0.0f;
				}
				else {
					// If the fish doesn't have 'bite', increment the iterator
					++it;
				}
			}

			m_currentPlayerState = PlayerState2::IDLE2;
		}
	}
	break;
	default:
		break;
	}

	m_textScore->LoadFromRenderText("Score: " + std::to_string(m_score));
	bool isHooked = false;

	// level timer


	if (m_time <= 0)
	{
		m_time -= deltaTime;

	}
	else
	{
		m_time -= deltaTime;
		int minutes = static_cast<int>(m_time) / 60;
		int seconds = static_cast<int>(m_time) % 60;
		if (m_time < 10.0) {
			std::string timeString = "Time:" + std::to_string(minutes) + ":0" + std::to_string(seconds);
			m_textTime->LoadFromRenderText(timeString);
		}
		else
		{
			std::string timeString = "Time:" + std::to_string(minutes) + ":" + std::to_string(seconds);
			m_textTime->LoadFromRenderText(timeString);
		}
	}


	if (m_score >= 850 && !m_isMissionCompleted)
	{
		m_isMissionCompleted = true;
		m_textend->LoadFromRenderText("Mission Complete!");
		m_listButton.push_back(buttonnext);
		m_Soundsongbien->StopSound();
		m_Soundwin.PlaySfx(sfxIndexwin, 0);

	}





	if (m_time <= 0 && !m_isMissionCompleted)
	{
		m_isMissionCompleted = true;
		m_textend->LoadFromRenderText("Time Out. You failed the mission.");
		m_listButton.push_back(buttonreplay);
		m_listButton.push_back(buttonhome);
		m_Soundsongbien->StopSound();
		m_Soundlose.PlaySfx(sfxIndex3, 0);

	}


	//Update position of camera
	//Camera::GetInstance()->Update(deltaTime);
	//obj->Update(deltaTime);
}

void Level2::Draw(SDL_Renderer* renderer)
{

	m_background->Draw(renderer);
	m_textScore->Draw(renderer);
	m_textMission->Draw(renderer);
	m_textLevel->Draw(renderer);
	m_textTime->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_fish)
	{
		it->Draw(renderer);
	}

	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}

	obj_hook->Draw(renderer);
	float startX = obj_hook->Get2DPosition().x + 7;
	float startY = obj_hook->Get2DPosition().y + 2;

	float endX = obj_boat->Get2DPosition().x + 7;
	float endY = 111;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
	m_textend->Draw(renderer);


}