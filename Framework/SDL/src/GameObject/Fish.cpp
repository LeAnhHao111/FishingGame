#include "Fish.h"
#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "Define.h"


Fish::Fish()
{
}

Fish::Fish(FishType type)
{
    switch (type)
    {
    case Fish0:
        name_fish = "Fish1";
        speed_fish = 500.0f;
        weight_fish = 1.0f;
        value_fish = 500.0f;
        m_type = type;
        break;

    case Fish1:
        name_fish = "Fish2";
        speed_fish = 100.0f;
        weight_fish = 2.0f;
        value_fish = 30.0f;
        m_type = type;
        break;

    case Fish2:
        name_fish = "Fish3";
        speed_fish = 150.0f;
        weight_fish = 3.0f;
        value_fish = 40.0f;
        m_type = type;
        break;

    case Fish3:
        name_fish = "Fish4";
        speed_fish = 200.0f;
        weight_fish = 4.0f;
        value_fish = 50.0f;
        m_type = type;
        break;

    case Fish4:
        name_fish = "Fish5";
        speed_fish = 100.0f;
        weight_fish = 8.0f;
        value_fish = 60.0f;
        m_type = type;
        break;

    case Fish5:
        name_fish = "Fish6";
        speed_fish = 250.0f;
        weight_fish = 12.0f;
        value_fish = 100.0f;
        m_type = type;
        break;

    case Fish6:
        name_fish = "Fish7";
        speed_fish = 180.0f;
        weight_fish = 4.0f;
        value_fish = 80.0f;
        m_type = type;
        break;

    case Fish7:
        name_fish = "Fish8";
        speed_fish = 120.0f;
        weight_fish = 6.0f;
        value_fish = 90.0f;
        m_type = type;
        break;
    case TRASH1:
        name_fish = "Trash1";
        speed_fish = 50.0f;
        weight_fish = 1.0f;
        value_fish = 2.0f;
        m_type = type;
        break;
    case TRASH2:
        name_fish = "Trash2";
        speed_fish = 50.0f;
        weight_fish = 1.0f;
        value_fish = 3.0f;
        m_type = type;
        break;
    case TRASH3:
        name_fish = "Trash3";
        speed_fish = 50.0f;
        weight_fish = 1.0f;
        value_fish = 1.0f;
        m_type = type;
        break;
    case TRASH4:
        name_fish = "Trash4";
        speed_fish = 30.0f;
        weight_fish = 8.0f;
        value_fish = 10.0f;
        m_type = type;
        break;
    case CHEAT:
        name_fish = "Cheat";
        speed_fish = 0.0f;
        weight_fish = 20.0f;
        value_fish = 300.0f;
        m_type = type;
        break;
    }
}

Fish::~Fish()
{
}

void Fish::Init()
{
}

void Fish::Draw(SDL_Renderer* renderer)
{
    m_fishAnimation->Draw(renderer);
}

void Fish::Update(float deltatime)
{
    m_fishAnimation->Update(deltatime);
}

void Fish::Set2DPosition(float x, float y)
{
    m_fishAnimation->Set2DPosition(x, y);
    m_position.x = x;
    m_position.y = y;

}

void Fish::SetRotation(double angle)
{
    m_fishAnimation->SetRotation(angle);
}

void Fish::SetFlip(SDL_RendererFlip flip)
{
    m_fishAnimation->SetFlip(flip);
}

float Fish::GetWeight()
{
	return weight_fish;
}

float Fish::GetValue()
{
	return value_fish;
}

void Fish::SetFishSpeed(float speed) 
{
    speed_fish = speed;
}

int Fish::GetFishType()
{
    return m_type;
}

float Fish::GetFishSpeed() const
{
    return speed_fish;
}

void Fish::SetSize(int width, int height)
{
    m_fishAnimation->SetSize(width, height);
}

int Fish::GetWidth()
{
    return m_fishAnimation->GetWidth();
}

int Fish::GetHeight()
{
    return m_fishAnimation->GetHeight();
}

char Fish::GetFlip()
{
    return m_fishAnimation->GetFlip();
}

Vector2 Fish::Get2DPosition()
{
    return Vector2(m_position.x,m_position.y);
}

void Fish::MoveFish(float deltaTime)
{
    float distanceToRightEdge = SCREEN_WIDTH - m_position.x;

    if (distanceToRightEdge > 0)
    {
        m_position.x += speed_fish * deltaTime;
        m_fishAnimation->Set2DPosition(m_position.x, m_position.y);
    }
    else
    {
        m_position.x = -25;
        m_fishAnimation->Set2DPosition(m_position.x, m_position.y);
    }

}

void Fish::MoveFish2(float deltaTime)
{
    float distanceToRightEdge = m_position.x;

    if (distanceToRightEdge > 0)
    {
        m_position.x -= speed_fish * deltaTime;
        m_fishAnimation->Set2DPosition(m_position.x, m_position.y);
    }
    else
    {
        m_position.x = SCREEN_WIDTH + 25 ; 
        m_fishAnimation->Set2DPosition(m_position.x, m_position.y);
    }
}
