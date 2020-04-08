#include "InstructionsButton.h"
#include "Game.h"

InstructionsButton::InstructionsButton()
	// call super constructor
	:Button(
		"../Assets/textures/InstructionsButton.png",
		"instructionsButton",
		START_BUTTON, glm::vec2(Config::SCREEN_WIDTH*0.5f, Config::SCREEN_HEIGHT*0.5f)), m_isClicked(false)
{
	
}

InstructionsButton::~InstructionsButton()
{
}

bool InstructionsButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if(!m_isClicked)
		{
			TheSoundManager::Instance()->playSound("click", 0);

			TheGame::Instance()->changeSceneState(SceneState::INSTRUCTIONS_SCENE);
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


