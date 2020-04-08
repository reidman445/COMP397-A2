#include "BulletManager.h"

BulletManager* BulletManager::s_pInstance = nullptr;

void BulletManager::clean()
{
}

void BulletManager::update()
{
	for (auto bullet : m_pBulletPool)
	{
		if (bullet->isActive())
		{
			bullet->update();

		}
	}

}

void BulletManager::draw()
{
	for (auto bullet : m_pBulletPool)
	{
		if (bullet->isActive())
		{
			bullet->draw();

		}
	}
}

Bullet* BulletManager::getBullet()
{
	Bullet* bullet = m_pBulletPool.front();
	m_pBulletPool.pop_front();
	m_pBulletPool.push_back(bullet);
	bullet->isActive();
	return bullet;
}

BulletManager::BulletManager() : m_bulletNumber(60)
{
	m_buildBulletPool();
}

BulletManager::~BulletManager()
= default;

void BulletManager::m_buildBulletPool()
{

	m_pBulletPool = std::list<Bullet*>();

	for (int i = 0; i < m_bulletNumber; ++i)
	{
		m_pBulletPool.push_back(new Bullet());

	}


}
