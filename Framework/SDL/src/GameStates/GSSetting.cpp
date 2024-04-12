#include "GSSetting.h"

GSSetting::GSSetting() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSSetting::~GSSetting()
{
}



void GSSetting::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_help.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// Unmute
	texture = ResourceManagers::GetInstance()->GetTexture("unmute.png");
	std::shared_ptr<MouseButton> btnUnmute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnUnmute->SetSize(100, 100);
	btnUnmute->Set2DPosition(SCREEN_WIDTH / 2 - 250, SCREEN_HEIDHT / 2 - 50);
	btnUnmute->SetOnClick([]() {
			// Check if the sound is currently paused
			if (Mix_PausedMusic() == 1) {
				// Resume the music to unmute it
				Mix_ResumeMusic();
			}
		});
	m_listButton.push_back(btnUnmute);

	texture = ResourceManagers::GetInstance()->GetTexture("mute.png");
	std::shared_ptr<MouseButton> btnMute = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);

	btnMute->SetSize(100, 100);
	btnMute->Set2DPosition(SCREEN_WIDTH / 2 + 150, SCREEN_HEIDHT / 2 - 50);
	btnMute->SetOnClick([]() {
		if (Mix_PlayingMusic() == 1) {
			// Pause the music to mute it
			Mix_PauseMusic();
		}
		});
	m_listButton.push_back(btnMute);

	// exit button
	texture = ResourceManagers::GetInstance()->GetTexture("close.png");
	std::shared_ptr<MouseButton> btnClose = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	//btnClose = std::make_shared<MouseButton>(texture);
	btnClose->SetSize(50, 50);
	btnClose->Set2DPosition(SCREEN_WIDTH - btnClose->GetWidth(), 10);
	btnClose->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(btnClose);

	///Set Font
	m_textColor = { 255,255,0 };
	m_textGameName = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textGameName->SetSize(300, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 250);
	m_textGameName->LoadFromRenderText("Setting");

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/nhacnen.mp3");
	m_Sound->PlaySound();

}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{
	m_Sound->StopSound();
	// button close

}

void GSSetting::Resume()
{
	m_Sound->PlaySound();
}


void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(SDL_Event& e)
{
}

void GSSetting::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	m_textGameName->Draw(renderer);
}