#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
#include <list>
#include <vector>

class TextureManager;
class SpriteAnimation : public BaseObject{
protected:
	Vector2			m_Vec2DPos;
	int			m_iHeight;
	int			m_iWidth;
	float			m_numFrames;
	int			m_currentFrame;
	float		m_frameTime;
	float		m_currentTime;
	int			m_spriteRow; //start 1,2,3
	int		m_frameCount; // start from 1,2,3...
	float  m_currentTicks;
	bool m_movingDown;
	float m_time;
	Uint32 m_lastUpdate;
	int			m_animSpeed;
	int m_numAction; //start from 1,2,3...
	//SDL_RendererFlip m_flip;
	//std::shared_ptr<TextureManager> m_texture;

	float m_fishSpeed;

public:
	SpriteAnimation(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float  frameTime);
	~SpriteAnimation();

	void		Init() override;
	void		Draw(SDL_Renderer* renderer) override;
	void		Update(float deltatime) override;
	void		Set2DPosition(float x, float y);
	void		SetRotation(double angle);
	void		SetFlip (SDL_RendererFlip flip);


	Vector2		Get2DPosition();
	void		SetSize(int width, int height);
	int			GetWidth();
	int			GetHeight();
	char		GetFlip();
	void		MoveLeft(float deltaTime);
	void		MoveRight(float deltaTime);
	void		MoveDown(float deltaTime);
	void		MoveUp(float deltaTime);
	void		MoveUp(float deltaTime, float speed);
};