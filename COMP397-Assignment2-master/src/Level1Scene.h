#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Background.h"
#include "Boss.h"
#include "Scene.h"


#include "Player.h"
#include "ExplosionManager.h"
#include "BulletManager.h"
#include "Coin.h"
#include "Enemy.h"
#include "FinishLevel.h"
#include "Heart.h"
#include "Label.h"
#include "Powerup.h"


class Level1Scene : public Scene
{
public:
	Level1Scene();
	~Level1Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:

	void buildEnemies();
	void checkCollisions();

	std::vector<Coin*> m_pCoins;
	
	glm::vec2 m_mousePosition;

	Player* m_pPlayer;
	Background* m_pBackground;
	Label* m_pScoreLabel;

	std::vector<Enemy*> m_pFirstWaveEnemies;
	std::vector<Enemy*> m_pSecondWaveEnemies;
	std::vector<Enemy*> m_pThirdWaveEnemies;
	std::vector<Enemy*> m_pFourthWaveEnemies;
	std::vector<Heart*> m_pPlayerHealth;

	Boss* m_pBoss;
	bool m_bBossDestroyed;
	
	Powerup* m_pPowerup;
	FinishLevel* m_pFinishLevel;
};

#endif /* defined (__LEVEL1_SCENE__) */