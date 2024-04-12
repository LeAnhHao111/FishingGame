#pragma once
#include "MouseButton.h"
#include "Timer.h"
#include "GameManager/Singleton.h"
class Game :public SingletonDclp<Game> {
public:
	bool Init();
	void Update(float deltaTime);
	void Run();
	void CleanUp();
private:
	Timer* fpsTimer;
	float m_LastTime;
	std::shared_ptr<Timer> capTimer;
};
