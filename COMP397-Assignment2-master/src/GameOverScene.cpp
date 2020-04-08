#include "GameOverScene.h"
#include <algorithm>
#include "Game.h"
#include "GameManager.h"
#include "glm/gtx/string_cast.hpp"

GameOverScene::GameOverScene()
{
	GameOverScene::start();
}

GameOverScene::~GameOverScene()
= default;

void GameOverScene::draw()
{
	m_pBackground->draw();

	m_label->draw();
	m_score->draw();
	m_enemiesDestroyed->draw();
	
	m_pTryAgainButton->draw();
	m_pBackToMenuButton->draw();

}

void GameOverScene::update()
{
	m_pBackToMenuButton->setMousePosition(m_mousePosition);


	if (m_pBackToMenuButton->ButtonClick())
	{
		return;
	}

	m_pTryAgainButton->setMousePosition(m_mousePosition);


	if (m_pTryAgainButton->ButtonClick())
	{
		return;
	}
	
}

void GameOverScene::clean()
{

	removeAllChildren();
}

void GameOverScene::handleEvents()
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
				m_pTryAgainButton->setMouseButtonClicked(true);


				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pBackToMenuButton->setMouseButtonClicked(false);
				m_pTryAgainButton->setMouseButtonClicked(false);


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
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void GameOverScene::start()
{
	m_pBackground = new Background();
	addChild(m_pBackground);
	
	const SDL_Color red = { 255, 10, 10, 255 };
	const SDL_Color orange = { 255, 215, 0, 0 };

	m_label = new Label("GAME OVER", "Roddenberry", 80, orange, glm::vec2(400.0f, 80.0f));
	m_label->setParent(this);
	addChild(m_label);

	m_score = new Label("Score: " + std::to_string(GameManager::Instance()->getScore()), "Roddenberry", 40, orange, glm::vec2(400.0, 275.0f), 0, true);
	m_score->setParent(this);
	addChild(m_score);


	m_enemiesDestroyed = new Label("Enemies Destroyed: " + std::to_string(GameManager::Instance()->getEnemiesDestroyed()) + "/" + std::to_string(GameManager::Instance()->getEnemiesCount()), "Roddenberry", 40, orange, glm::vec2(400.0f, 325.0f), 0, true);
	m_enemiesDestroyed->setParent(this);
	addChild(m_enemiesDestroyed);

	
	m_pBackToMenuButton = new BackToMenuButton();
	m_pBackToMenuButton->setPosition(glm::vec2(520, 500));
	addChild(m_pBackToMenuButton);

	m_pTryAgainButton = new TryAgainButton();
	m_pTryAgainButton->setPosition(glm::vec2(250, 500));
	addChild(m_pTryAgainButton);

	
	
}
