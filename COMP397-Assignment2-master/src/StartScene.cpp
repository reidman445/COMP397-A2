//Star Trek Side Scroller - Assignment 2 - C++ Sidescroller
//
//Author: Reid Williams
//Student #: 300973473
//Last Modified By: Reid Williams
//Date Last Modified: 2020-04-07


#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();

}

void StartScene::update()
{
	m_pStartButton->setMousePosition(m_mousePosition);
	m_pQuitButton->setMousePosition(m_mousePosition);
	m_pInstructionsButton->setMousePosition(m_mousePosition);

	if(m_pStartButton->ButtonClick())
	{
		return;
	}
	
	
	if(m_pQuitButton->ButtonClick())
	{
		return;
	}


	if (m_pInstructionsButton->ButtonClick())
	{
		return;
	}
	
	
}

void StartScene::clean()
{
	std::cout << "Clean called on StartScene" << std::endl;
	
	delete m_pStartLabel;
	m_pStartLabel = nullptr;

	delete m_pStartButton;
	delete m_pQuitButton;

	
	removeAllChildren();
}

void StartScene::handleEvents()
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
				m_pStartButton->setMouseButtonClicked(true);
				m_pQuitButton->setMouseButtonClicked(true);
				m_pInstructionsButton->setMouseButtonClicked(true);

				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(false);
				m_pQuitButton->setMouseButtonClicked(false);
				m_pInstructionsButton->setMouseButtonClicked(false);

				
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

void StartScene::start()
{

	TheSoundManager::Instance()->load("../Assets/audio/Music.mp3",
		"music", sound_type::SOUND_MUSIC);


	TheSoundManager::Instance()->load("../Assets/audio/Click.mp3",
		"click", sound_type::SOUND_SFX);
	
	TheSoundManager::Instance()->playMusic("music", 1);

	m_pBackground = new Background();
	addChild(m_pBackground);
	
	const SDL_Color red = { 255, 10, 10, 255 };
	const SDL_Color orange = { 255, 215, 0, 0 };
	m_pStartLabel = new Label("To Boldy Go...", "Roddenberry", 80, orange, glm::vec2(400.0f, 80.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);


	m_pStartButton = new StartButton();
	m_pStartButton->setPosition(Config::SCREEN_WIDTH * 0.5, 300);
	addChild(m_pStartButton);

	m_pInstructionsButton = new InstructionsButton();
	m_pInstructionsButton->setPosition(Config::SCREEN_WIDTH * 0.5, 400);
	addChild(m_pInstructionsButton);
	
	m_pQuitButton = new QuitButton();
	m_pQuitButton->setPosition(Config::SCREEN_WIDTH * 0.5, 500);
	addChild(m_pQuitButton);
	

}

glm::vec2 StartScene::getMousePosition() const
{
	TheSoundManager::Instance()->load("../Assets/audio/door-01.flac", "dr", SOUND_SFX);

	return m_mousePosition;
}
