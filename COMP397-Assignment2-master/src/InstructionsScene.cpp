#include "InstructionsScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

InstructionsScene::InstructionsScene()
{
	InstructionsScene::start();
}

InstructionsScene::~InstructionsScene()
= default;

void InstructionsScene::draw()
{
	drawDisplayList();

}

void InstructionsScene::update()
{
	m_pBackToMenuButton->setMousePosition(m_mousePosition);


	if(m_pBackToMenuButton->ButtonClick())
	{
		return;
	}

	
	
}

void InstructionsScene::clean()
{
	std::cout << "Clean called on InstructionsScene" << std::endl;
	
	delete m_pStartLabel;
	m_pStartLabel = nullptr;
	
	delete m_pMoveLabel;
	m_pMoveLabel = nullptr;

	delete m_pBackToMenuButton;

	
	removeAllChildren();
}

void InstructionsScene::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			/*std::cout << "Mouse X: " << m_mousePosition.x << std::endl;
			std::cout << "Mouse Y: " << m_mousePosition.y << std::endl;
			std::cout << "---------------------------------------------" << std::endl;*/
			break;

		case SDL_MOUSEBUTTONDOWN:
			std::cout << "click" << std::endl;
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pBackToMenuButton->setMouseButtonClicked(true);


				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pBackToMenuButton->setMouseButtonClicked(false);


				
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

void InstructionsScene::start()
{
	m_pBackground = new Background();
	addChild(m_pBackground);
	
	const SDL_Color red = { 255, 10, 10, 255 };
	const SDL_Color orange = { 255, 215, 0, 0 };

	m_pStartLabel = new Label("Instructions", "Roddenberry", 80, orange, glm::vec2(400.0f, 80.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pControls = new Controls();
	m_pControls->setPosition(150, 200);
	addChild(m_pControls);
	
	m_pMoveLabel = new Label("MOVE", "Roddenberry", 40, orange, glm::vec2(230, 370));
	m_pMoveLabel->setParent(this);
	addChild(m_pMoveLabel);

	m_pShootLabel = new Label("FIRE PROTON TORPEDO", "Roddenberry", 40, orange, glm::vec2(510, 370));
	m_pShootLabel->setParent(this);
	addChild(m_pShootLabel);
	

	m_pBackToMenuButton = new BackToMenuButton();
	m_pBackToMenuButton->setPosition(Config::SCREEN_WIDTH * 0.5, 500);
	addChild(m_pBackToMenuButton);


	

}

glm::vec2 InstructionsScene::getMousePosition() const
{
	TheSoundManager::Instance()->load("../Assets/audio/door-01.flac", "dr", SOUND_SFX);

	return m_mousePosition;
}
