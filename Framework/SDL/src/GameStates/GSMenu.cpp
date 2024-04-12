#include "GSMenu.h"

GSMenu::GSMenu() : GameStateBase(StateType::STATE_MENU),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_sea.jpg");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// play button
	texture = ResourceManagers::GetInstance()->GetTexture("play.png");
	std::shared_ptr<MouseButton> btnPlay = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	
	btnPlay->SetSize(200, 200);
	btnPlay->Set2DPosition((SCREEN_WIDTH - btnPlay->GetWidth())/2, (SCREEN_HEIDHT - btnPlay->GetHeight()) / 2);
	btnPlay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});
	m_listButton.push_back(btnPlay);


	//Setting game
	texture = ResourceManagers::GetInstance()->GetTexture("setting.png");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2 + 100, SCREEN_HEIDHT / 2 + 100);
	btnOption->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_SETTING);
		});
	m_listButton.push_back(btnOption);

	//CREDIT game
	texture = ResourceManagers::GetInstance()->GetTexture("help.png");
	btnCredit = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnCredit->Set2DPosition((SCREEN_WIDTH - btnCredit->GetWidth()) / 2 - 100, SCREEN_HEIDHT / 2 + 100);
	btnCredit->SetSize(100, 100);
	btnCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_HELP);
		});
	m_listButton.push_back(btnCredit);

	// game title
	///Set Font
	m_textColor = { 255,99,71 };
	m_textGameName = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textGameName->SetSize(600, 100);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth())/2, SCREEN_HEIDHT / 2 - 250);
	m_textGameName->LoadFromRenderText("Fishing Game");
	
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/nhacnen.mp3");
	m_Sound->PlaySound();

}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
	m_Sound->StopSound();
	// button close
	
}

void GSMenu::Resume()
{
	m_Sound->PlaySound();
}


void GSMenu::HandleEvents()
{
}

void GSMenu::HandleKeyEvents(SDL_Event& e)
{
}

void GSMenu::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button ->HandleTouchEvent(&e))
		{
			m_Sound->StopSound();
			break;
		}
	}
}

void GSMenu::HandleMouseMoveEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{

	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);

	}
}

void GSMenu::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
	
	m_textGameName->Draw(renderer);
}
