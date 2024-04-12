#include "GSHelp.h"
#include <memory>


GSHelp::GSHelp() : GameStateBase(StateType::STATE_HELP),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<MouseButton>>{}), m_textGameName(nullptr)
{
}


GSHelp::~GSHelp()
{
}



void GSHelp::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_help.png");

	// background
	//auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

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

	// game title
	///Set Font
	m_textColor = { 255,255,0 };
	m_textGameName = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textGameName->SetSize(300, 80);
	m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 280);
	m_textGameName->LoadFromRenderText("Help");

	// Movement 
	m_textColor = { 0, 0, 0 };
	m_textmovement = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textmovement->SetSize(200, 60);
	m_textmovement->Set2DPosition(SCREEN_WIDTH / 2 + 100, SCREEN_HEIDHT / 2 - 160);
	m_textmovement->LoadFromRenderText("Movement");

	//Drop fishing rod
	m_textColor = { 0, 0, 0 };
	m_textdrop = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textdrop->SetSize(400, 60);
	m_textdrop->Set2DPosition(SCREEN_WIDTH / 2 + 100, SCREEN_HEIDHT / 2 - 10);
	m_textdrop->LoadFromRenderText("Drop fishing rod");

	//Credit
	m_textColor = { 0, 0, 0 };
	m_textcredit = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textcredit->SetSize(105, 60);
	m_textcredit->Set2DPosition((SCREEN_WIDTH - m_textcredit->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 100);
	m_textcredit->LoadFromRenderText("Credit:");

	//LE ANH HAO
	m_textColor = { 0, 0, 0 };
	m_texthao = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_texthao->SetSize(150, 60);
	m_texthao->Set2DPosition((SCREEN_WIDTH - m_texthao->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 160);
	m_texthao->LoadFromRenderText("LE ANH HAO");

	//PHAN DO HAI MINH
	m_textColor = { 0, 0, 0 };
	m_textminh = std::make_shared<Text>("Data/font.ttf", m_textColor);
	m_textminh->SetSize(240, 60);
	m_textminh->Set2DPosition((SCREEN_WIDTH - m_textminh->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 220);
	m_textminh->LoadFromRenderText("PHAN DO HAI MINH");

	// down
	texture = ResourceManagers::GetInstance()->GetTexture("down.png");
	obj_down = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	obj_down->SetSize(70, 70);
	obj_down->Set2DPosition(SCREEN_WIDTH / 2 - 300, SCREEN_HEIDHT / 2 - 20);

	// right
	texture = ResourceManagers::GetInstance()->GetTexture("right.png");
	obj_right = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	obj_right->SetSize(70, 70);
	obj_right->Set2DPosition(SCREEN_WIDTH / 2 - 250, SCREEN_HEIDHT / 2 - 170);

	// left
	texture = ResourceManagers::GetInstance()->GetTexture("left.png");
	obj_left = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	obj_left->SetSize(70, 70);
	obj_left->Set2DPosition(SCREEN_WIDTH / 2 - 350, SCREEN_HEIDHT / 2 - 170);

	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/nhacnen.mp3");
	m_Sound->PlaySound();
}

void GSHelp::Exit()
{
}


void GSHelp::Pause()
{
	m_Sound->StopSound();
	// button close

}

void GSHelp::Resume()
{
	m_Sound->PlaySound();
}


void GSHelp::HandleEvents()
{
}

void GSHelp::HandleKeyEvents(SDL_Event& e)
{
}

void GSHelp::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSHelp::HandleMouseMoveEvents(int x, int y)
{
}

void GSHelp::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSHelp::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	m_textmovement->Draw(renderer);
	m_textdrop->Draw(renderer);
	m_textcredit->Draw(renderer);
	m_texthao->Draw(renderer);
	m_textminh->Draw(renderer);
	obj_down->Draw(renderer);
	obj_right->Draw(renderer);
	obj_left->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

	m_textGameName->Draw(renderer);
}