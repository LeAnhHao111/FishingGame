#pragma once
#include "BaseObject.h"
#include <SDL_render.h>
#include <vector>
#include <memory>
#include <string>
#include "SpriteAnimation.h"

class TextureManager;
enum FishType
{
    Fish0,
    Fish1,
    Fish2,
    Fish3,
    Fish4,
    Fish5,
    Fish6, 
    Fish7,
    TRASH1,
    TRASH2,
    TRASH3,
    TRASH4,
    CHEAT,
};

class Fish : public BaseObject
{
private:

    Vector2			m_Vec2DPos;

    
    std::string name_fish;
    float weight_fish;
    float value_fish;
    float speed_fish;
    FishType m_type;
    


public:
    Fish();
    Fish(FishType type);
    ~Fish(); 

    std::shared_ptr <SpriteAnimation> m_fishAnimation;
    
    void		Init();
    void		Draw(SDL_Renderer* renderer) ;
    void		Update(float deltatime) ;
    void		Set2DPosition(float x, float y);
    void		SetRotation(double angle);
    void		SetFlip(SDL_RendererFlip flip);

    Vector2		Get2DPosition();
    void		SetSize(int width, int height);
    int			GetWidth();
    int			GetHeight();
    char	    GetFlip();

    // Getter methods
    float   GetWeight();
    float   GetValue();
   // void    SetFishType(FishType type);

    int     GetFishType();
    float   GetFishSpeed() const;
    void    SetFishSpeed(float speed);
    void    MoveFish(float deltaTime);
    void    MoveFish2(float deltaTime);
    
public:
    bool bite = false;
};


