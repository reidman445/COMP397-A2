#include "BackToMenuButton.h"
#include "Game.h"

BackToMenuButton::BackToMenuButton()
	// call super constructor
	:Button(
		"../Assets/textures/BackToMenuButton.png",
		"backToMenuButton",
		START_BUTTON, glm::vec2(Config::SCREEN_WIDTH*0.5f, Config::SCREEN_HEIGHT*0.5f)), m_isClicked(false)
{
	
}

BackToMenuButton::~BackToMenuButton()
{
}

bool BackToMenuButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if(!m_isClicked)
		{
			TheSoundManager::Instance()->playSound("click", 0);

			TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
			m_isClicked = true;
		}
		return true;
	}
	else
	{
		m_isClicked = false;
	}

	return false;
}


