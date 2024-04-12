#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "GameObject/Sound.h"
#include <memory>
class GSHelp :
	public GameStateBase
{
public:
	GSHelp();
	~GSHelp();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;

private:
	std::shared_ptr<Sprite2D>				m_background, obj_down, obj_left, obj_right;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::shared_ptr<Text>					m_textGameName, m_textmovement, m_textdrop, m_textcredit, m_texthao, m_textminh;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	std::shared_ptr<Sound>					m_Sound;
	std::shared_ptr<MouseButton> btnCredit;
	int score = 0;

};