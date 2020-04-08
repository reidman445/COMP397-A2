#include "GameManager.h"

GameManager* GameManager::s_pInstance = nullptr;


int GameManager::getScore()
{
	return m_score;
}

void GameManager::addScore(int score)
{
	m_score += score;
}

int GameManager::getEnemiesCount() const
{
	return m_enemiesCount;
}

void GameManager::addEnemiesCount()
{
	m_enemiesCount++;
}

int GameManager::getEnemiesDestroyed()
{
	return m_enemiesDestroyed;
}

void GameManager::addEnemiesDestroyed()
{
	m_enemiesDestroyed++;
}

int GameManager::getPlayerHealth()
{
	return m_playerHealth;
}

void GameManager::setPlayerHealth(int health)
{
	m_playerHealth = health;
}

void GameManager::reset()
{
	m_enemiesCount = 0;
	m_enemiesDestroyed = 0;
	m_score = 0;
	m_playerHealth = 3;
}

GameManager::GameManager(){

}

GameManager::~GameManager()
= default;


