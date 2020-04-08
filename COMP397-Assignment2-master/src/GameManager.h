#pragma once
#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__



class GameManager
{
public:
	static GameManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameManager();
			return  s_pInstance;
		}

		return s_pInstance;
	}

	int getScore();
	void addScore(int score);

	int getEnemiesCount() const;
	void addEnemiesCount();

	int getEnemiesDestroyed();
	void addEnemiesDestroyed();

	int getPlayerHealth();
	void setPlayerHealth(int health);
	
	void reset();
	bool bossDestroyed = false;
private:

	int m_score = 0;
	int m_enemiesCount = 0;
	int m_enemiesDestroyed = 0;
	int m_playerHealth = 3;
	GameManager();
	~GameManager();


	static  GameManager* s_pInstance;

};

typedef  GameManager TheGameManager;

#endif
