#include "Level1Scene.h"
#include "Game.h"
#include "GameManager.h"
#include "Util.h"

Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	m_pBackground->draw();
	BulletManager::Instance()->draw();

	drawDisplayList();
	ExplosionManager::Instance()->draw();

	for (int i = 0; i < GameManager::Instance()->getPlayerHealth(); ++i)
	{
		m_pPlayerHealth[i]->draw();
	}
	
}

void Level1Scene::update()
{

	m_pBackground->update();
	m_pFinishLevel->update();
	
	updateDisplayList();
	
	ExplosionManager::Instance()->update();
	BulletManager::Instance()->update();
	
	m_pScoreLabel->setText("Score: " + std::to_string(TheGameManager::Instance()->getScore()));



	
	checkCollisions();

	if (TheGameManager::Instance()->bossDestroyed && !m_bBossDestroyed)
	{
		m_bBossDestroyed = true;
		m_pFinishLevel->setVelocity(glm::vec2(-5, 0));
	}

	
	if (m_pPlayer->getPosition().x > m_pFinishLevel->getPosition().x)
	{
		TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
	}

	if(TheGameManager::Instance()->getPlayerHealth() == 0)
	{
		TheGame::Instance()->changeSceneState(SceneState::GAME_OVER_SCENE);

	}
	
}

void Level1Scene::clean()
{

	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
	
	SDL_Event event;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_SPACE]) {
		if (m_pPlayer->getShootTime() <= 0)
		{
			m_pPlayer->setShootTime(m_pPlayer->getShootRate());
			auto bullet = BulletManager::Instance()->getBullet();
			bullet->activate();
			bullet->setPosition(glm::vec2(m_pPlayer->getPosition().x + 15, m_pPlayer->getPosition().y + 18));
			TheSoundManager::Instance()->playSound("laser", 0);
		}
	}

	if (state[SDL_SCANCODE_S]) {
		m_pPlayer->move(DOWN);
		m_pPlayer->yBrakeDirection = EMPTY;
	}

	if (state[SDL_SCANCODE_W]) {
		m_pPlayer->move(UP);
		m_pPlayer->yBrakeDirection = EMPTY;
	}

	if (state[SDL_SCANCODE_A]) {
		m_pPlayer->move(LEFT);
		m_pPlayer->xBrakeDirection = EMPTY;
	}

	if (state[SDL_SCANCODE_D]) {
		m_pPlayer->move(RIGHT);
		m_pPlayer->xBrakeDirection = EMPTY;
	}

	if (state[SDL_SCANCODE_L] && state[SDL_SCANCODE_U] && state[SDL_SCANCODE_C]) {
		m_pPlayer->setShootRate(0.05f);
	}
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;

			}
			
			break;
		case SDL_KEYUP:
			keyReleased = event.key.keysym.sym;

			
			if (keyReleased == SDLK_w)
			{
				m_pPlayer->yBrakeDirection = UP;

			}

			if (keyReleased == SDLK_s)
			{
				m_pPlayer->yBrakeDirection = DOWN;

			}
			if (keyReleased == SDLK_a)
			{
				m_pPlayer->xBrakeDirection = LEFT;
			}

			if (keyReleased == SDLK_d)
			{
				m_pPlayer->xBrakeDirection = RIGHT;

			}

			if(keyReleased == SDLK_SPACE)
			{
				m_pPlayer->setShootTime(0);

			}
			
			break;
			
		}
	}
}

void Level1Scene::start()
{
	TheGameManager::Instance()->reset();
	
	m_pBackground = new Background();
	
	m_pPlayer = new Player();
	m_pPlayer->setPosition(glm::vec2(70.0f, Config::SCREEN_HEIGHT * 0.5f));
	addChild(m_pPlayer);

	m_pPowerup = new Powerup();
	m_pPowerup->setPosition(glm::vec2(2000, Config::SCREEN_HEIGHT * 0.5f));
	addChild(m_pPowerup);
	
	buildEnemies();
	
	TheSoundManager::Instance()->load("../Assets/audio/laser.mp3",
		"laser", sound_type::SOUND_SFX);

	TheSoundManager::Instance()->load("../Assets/audio/Coin.mp3",
		"coin", sound_type::SOUND_SFX);
	
	TheSoundManager::Instance()->load("../Assets/audio/Explosion.mp3",
		"explosion", sound_type::SOUND_SFX);
	
	TheSoundManager::Instance()->load("../Assets/audio/Powerup.mp3",
		"powerup", sound_type::SOUND_SFX);

	TheSoundManager::Instance()->load("../Assets/audio/Hit.mp3",
		"hit", sound_type::SOUND_SFX);
	
	const SDL_Color white = { 255, 255, 255, 255 };

	m_pScoreLabel = new Label("Score: 000000", "Roddenberry", 20, white, glm::vec2(20, 20), 0, false);
	addChild(m_pScoreLabel);

	m_pFinishLevel = new FinishLevel();
	m_pFinishLevel->setPosition(glm::vec2(1000,0));

	m_pBoss = new Boss();
	m_pBoss->setPosition(glm::vec2(8000, 300));
	addChild(m_pBoss);

	for (int i = 0; i < 3; i++)
	{
		auto heart = new Heart();
		heart->setPosition(glm::vec2(15 + 45*i,50));
		m_pPlayerHealth.push_back(heart);

	}

	for (int i = 0; i < 50; i++)
	{		
		auto coin = new Coin();

		if (i < 5)
		{
			coin->setPosition(glm::vec2(700 + 35 * (i % 5), 120));

		} else if (i < 10)
		{
			coin->setPosition(glm::vec2(1000 + 35 * (i % 5), 680));

		} else if (i < 15)
		{
			coin->setPosition(glm::vec2(1500 + 35 * (i % 5), 440));

		}
		else if (i < 20)
		{
			coin->setPosition(glm::vec2(1500 + 35 * (i % 5), 480));

		}
		else if (i < 25)
		{
			coin->setPosition(glm::vec2(2200 + 35 * (i % 5), 120));

		}
		else if (i < 30)
		{
			coin->setPosition(glm::vec2(2200 + 35 * (i % 5), 160));

		}

		else if (i < 35)
		{
			coin->setPosition(glm::vec2(2800 + 35 * (i % 5), 420));

		}
		else if (i < 40)
		{
			coin->setPosition(glm::vec2(2800 + 35 * (i % 5), 380));

		}

		else if (i < 45)
		{
			coin->setPosition(glm::vec2(3500 + 35 * (i % 5), 120));

		}
		else if (i < 50)
		{
			coin->setPosition(glm::vec2(3500 + 35 * (i % 5), 160));

		}
		
		m_pCoins.push_back(coin);
		addChild(coin);

	}

	
}


void Level1Scene::buildEnemies()
{
	for (size_t i = 0; i < 9; i++)
	{
		GameManager::Instance()->addEnemiesCount();
		auto enemy = new Enemy();

		switch (i)
		{
		case 0:
			enemy->setPosition(glm::vec2(1300, 60 + 60 * i));
			break;
		case 1:
			enemy->setPosition(glm::vec2(1250, 60 + 60 * i));

			break;
		case 2:
			enemy->setPosition(glm::vec2(1200, 60 + 60 * i));

			break;
		case 3:
			enemy->setPosition(glm::vec2(1150, 60 + 60 * i));

			break;
		case 4:
			enemy->setPosition(glm::vec2(1100, 60 + 60 * i));

			break;
		case 5:
			enemy->setPosition(glm::vec2(1150, 60 + 60 * i));

			break;
		case 6:
			enemy->setPosition(glm::vec2(1200, 60 + 60 * i));

			break;
		case 7:
			enemy->setPosition(glm::vec2(1250, 60 + 60 * i));

			break;
		case 8:
			enemy->setPosition(glm::vec2(1300, 60 + 60 * i));

			break;
		}
		enemy->startPosition = enemy->getPosition();

		enemy->setMovementType(FOWARD);
		m_pFirstWaveEnemies.push_back(enemy);
		addChild(enemy);

	}

	for (size_t i = 0; i < 4; i++)
	{
		GameManager::Instance()->addEnemiesCount();
		auto enemy = new Enemy();

		int sign = pow(-1, i);

		enemy->setPosition(glm::vec2(2300 + 80 * i, 150 + 40*sign));
		enemy->setMovementType(SINE);
		
		m_pSecondWaveEnemies.push_back(enemy);
		enemy->startPosition = enemy->getPosition();

		addChild(enemy);

	}

	for (size_t i = 0; i < 4; i++)
	{
		GameManager::Instance()->addEnemiesCount();
		auto enemy = new Enemy();

		int sign = pow(-1, i);

		enemy->setPosition(glm::vec2(2300 + 80 * i, 450 + 40 * sign));
		enemy->setMovementType(COSINE);

		m_pSecondWaveEnemies.push_back(enemy);
		enemy->startPosition = enemy->getPosition();

		addChild(enemy);

	}

	
	

	for (size_t i = 0; i < 7; i++)
	{
		GameManager::Instance()->addEnemiesCount();

		auto enemy = new Enemy();
		enemy->setSpeed(5);
		if (i % 2 == 0)
		{
			enemy->setMovementType(FOWARD);
			enemy->setPosition(glm::vec2(4500, 80 + 75 * i));

		}
		else
		{
			enemy->setMovementType(FOWARD);
			enemy->setMovementType(BACK_AND_FORTH);
			enemy->setPosition(glm::vec2(4400, 80 + 75 * i));

		}
		m_pThirdWaveEnemies.push_back(enemy);
		enemy->startPosition = enemy->getPosition();

		addChild(enemy);

	}

	for (size_t i = 0; i < 12; i++)
	{
		GameManager::Instance()->addEnemiesCount();

		auto enemy = new Enemy();
		if (i % 2 == 0)
		{
			enemy->setPosition(glm::vec2(5300 + 120 * (i * 0.5), 100));
			enemy->setMovementType(DOWN_DIAGONAL);
		}
		else
		{
			enemy->setPosition(glm::vec2(5300 + 120 * (i * 0.5), Config::SCREEN_HEIGHT - 100));
			enemy->setMovementType(UP_DIAGONAL);
		}
		enemy->startPosition = enemy->getPosition();

		m_pFourthWaveEnemies.push_back(enemy);
		addChild(enemy);

	}
	
}

void Level1Scene::checkCollisions()
{
	   
	for (auto bullet : BulletManager::Instance()->m_pBulletPool)
	{
		if (bullet->getPosition().x < Config::SCREEN_WIDTH)
		{
			CollisionManager::squaredRadiusCheckBullet(bullet, m_pBoss);

			for (auto enemy : m_pFirstWaveEnemies)
			{
				CollisionManager::squaredRadiusCheckBullet(bullet, enemy);

			}

			for (auto enemy : m_pSecondWaveEnemies)
			{
				CollisionManager::squaredRadiusCheckBullet(bullet, enemy);

			}
			for (auto enemy : m_pThirdWaveEnemies)
			{
				CollisionManager::squaredRadiusCheckBullet(bullet, enemy);

			}
			for (auto enemy : m_pFourthWaveEnemies)
			{
				CollisionManager::squaredRadiusCheckBullet(bullet, enemy);

			}
		}

	}

	for (auto coin : m_pCoins)
	{
		CollisionManager::squaredRadiusCheck(m_pPlayer, coin);
	}
	

	CollisionManager::squaredRadiusCheck(m_pPlayer, m_pPowerup);

	if (!m_pPlayer->invincible)
	{
		for (auto enemy : m_pFirstWaveEnemies)
		{
			CollisionManager::squaredRadiusCheck(m_pPlayer, enemy);

		}

		for (auto enemy : m_pSecondWaveEnemies)
		{
			CollisionManager::squaredRadiusCheck(m_pPlayer, enemy);

		}
		for (auto enemy : m_pThirdWaveEnemies)
		{
			CollisionManager::squaredRadiusCheck(m_pPlayer, enemy);

		}
		for (auto enemy : m_pFourthWaveEnemies)
		{
			CollisionManager::squaredRadiusCheck(m_pPlayer, enemy);

		}
	}
	
	CollisionManager::squaredRadiusCheck(m_pPlayer, m_pBoss);


}
