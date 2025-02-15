#include "GameStateBase.h"
#include "GameStates/GSIntro.h"
#include "GSMenu.h"
#include "GSPlay.h"
#include "GSHelp.h"
#include "GSSetting.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		//GSINTRO;
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		//GSMENU
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		//GSPLAY
		break;
	case StateType::STATE_HELP:
		gs = std::make_shared<GSHelp>();
		//GSHELP
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		//GSSETTING
		break;
	case StateType::LEVEL2:
		gs = std::make_shared<Level2>();
		break;
	case StateType::LEVEL3:
		gs = std::make_shared<Level3>();
		break;
	case StateType::LEVEL4:
		gs = std::make_shared<Level4>();
		break;
	case StateType::LEVEL5:
		gs = std::make_shared<Level5>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}
