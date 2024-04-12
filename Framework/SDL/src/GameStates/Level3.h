#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "BaseObject.h"
#include <vector>
#include <memory>
#include <GameObject/Text.h>
#include "Fish.h"

enum PlayerState3
{
	IDLE3 = 0x1,
	MOVE_LEFT3 = 0x2,
	MOVE_RIGHT3 = 0x4,
	CAST3 = 0x8,
	REEL3 = 0x10
};

class Sprite2D;
class SpriteAnimation;

class Level3 :
	public GameStateBase
{
public:
	Level3();
	~Level3();

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
	bool    CheckCollision(std::shared_ptr<SpriteAnimation> sprite1, std::shared_ptr<Fish> sprite2);
	void    CheckHookCollision();
	int		m_KeyPress;
	Vector2 m_pos;
	bool	isHookMovingUp;
	bool isHooked;


private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::list<std::shared_ptr<Fish>> m_fish;
	std::list<std::shared_ptr<Fish>> getFishList() { return m_fish; }
	std::shared_ptr<SpriteAnimation> obj_boat;
	std::shared_ptr<SpriteAnimation> obj_actor;
	std::shared_ptr<SpriteAnimation> obj_fish1, obj_fish2, obj_fish3, obj_fish4, obj_fish5, obj_fish6, obj_fish7, obj_fish8;
	std::shared_ptr<SpriteAnimation> obj_hook;
	std::shared_ptr<MouseButton> buttonnext, buttonreplay, buttonclose, buttonhome;
	std::shared_ptr<Text>		m_textend, m_textTime, m_textScore, m_textMission, m_textLevel;
	SDL_Color m_textColor;
	TTF_Font* m_Font;
	std::shared_ptr<Sound>		 m_Soundsongbien;
	Sound m_Soundkeocan, m_Soundstart, m_Soundwin, m_Soundlose;
	unsigned int sfxIndex = m_Soundkeocan.LoadSfx("Data/Sounds/keocan.mp3");
	unsigned int sfxIndex1 = m_Soundstart.LoadSfx("Data/Sounds/gamestart.mp3");
	unsigned int sfxIndexwin = m_Soundwin.LoadSfx("Data/Sounds/end.mp3");
	unsigned int sfxIndex3 = m_Soundlose.LoadSfx("Data/Sounds/lose.mp3");

	float	m_time = 60.0;
	bool	m_isBoatMoving = false;
	float	m_timeHook;
	float	time = 0.0f;
	float	m_Velocity = 10.0f;
	int		m_score = 0;
	bool	m_isMissionCompleted = false;
	int		m_scoreGoal = 1000;
	int		m_currentPlayerState;
	float	m_currentFishWeight;
	float	m_currentFishValue;
	float	m_biteDepth;
};

