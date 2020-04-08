#include "TryAgainButton.h"
#include "Game.h"

TryAgainButton::TryAgainButton()
	// call super constructor
	:Button(
		"../Assets/textures/TryAgainButton.png",
		"tryAgainButton",
		START_BUTTON, glm::vec2(Config::SCREEN_WIDTH*0.5f, Config::SCREEN_HEIGHT*0.5f)), m_isClicked(false)
{
	
}

TryAgainButton::~TryAgainButton()
{
}

bool TryAgainButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if(!m_isClicked)
		{
			TheSoundManager::Instance()->playSound("click", 0);

			TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
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


