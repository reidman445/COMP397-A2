#include "CollisionManager.h"
#include "Util.h"
#include <algorithm>


#include "Bullet.h"
#include "Enemy.h"
#include "ExplosionManager.h"
#include "Game.h"
#include "GameManager.h"
#include "Player.h"

int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}

bool CollisionManager::squaredRadiusCheckBullet(Bullet* bullet, Enemy* enemy)
{
	glm::vec2 P1 = bullet->getPosition();
	glm::vec2 P2 = enemy->getPosition();
	int halfHeights = (bullet->getHeight() + enemy->getHeight()) * 0.5f;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {


		if (!enemy->getIsColliding()) {

			enemy->setIsColliding(true);

			switch (enemy->getType()) {
			case ENEMY:
			{
				TheSoundManager::Instance()->playSound("explosion", 0);

				
				TheGameManager::Instance()->addScore(100);
				auto explosion = ExplosionManager::Instance()->getExplosion();
				explosion->activate();
				explosion->setPosition(glm::vec2(bullet->getPosition()));
				bullet->deactivate();
				enemy->destroyed = true;
				enemy->setPosition(glm::vec2(-10000, 1000));
				GameManager::Instance()->addEnemiesDestroyed();

			}
			break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
				
		return false;
	}
	else
	{
		enemy->setIsColliding(false);
		return false;
	}
}

bool CollisionManager::squaredRadiusCheckBullet(Bullet* bullet, Boss* boss)
{
	glm::vec2 P1 = bullet->getPosition();
	glm::vec2 P2 = boss->getPosition();
	int halfHeights = (bullet->getHeight() + boss->getHeight()) * 0.5f;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {


		if (!boss->getIsColliding()) {

			boss->setIsColliding(true);

			switch (boss->getType()) {
			case BOSS:
			{
			

					if (boss->getHealth() > 0)
					{
						boss->setHealth(boss->getHealth() - 1);
						auto explosion = ExplosionManager::Instance()->getExplosion();
						explosion->activate();
						explosion->setPosition(glm::vec2(bullet->getPosition()));
					} else
					{
						TheGameManager::Instance()->addScore(1000);
						auto explosion = ExplosionManager::Instance()->getExplosion();
						explosion->activate();
						explosion->setPosition(glm::vec2(bullet->getPosition()));
						auto explosion2 = ExplosionManager::Instance()->getExplosion();
						explosion2->activate();
						explosion2->setPosition(glm::vec2(boss->getPosition() + glm::vec2(50, 50) ));
						auto explosion3 = ExplosionManager::Instance()->getExplosion();
						explosion3->activate();
						explosion3->setPosition(glm::vec2(boss->getPosition() + glm::vec2(-50, 50)));
						auto explosion4 = ExplosionManager::Instance()->getExplosion();
						explosion4->activate();
						explosion4->setPosition(glm::vec2(boss->getPosition() + glm::vec2(-50, -50)));
						auto explosion5 = ExplosionManager::Instance()->getExplosion();
						explosion5->activate();
						explosion5->setPosition(glm::vec2(boss->getPosition() + glm::vec2(50, -50)));
						boss->destroyed = true;
						boss->setPosition(glm::vec2(-10000, 1000));
						TheGameManager::Instance()->bossDestroyed = true;
					}

				TheSoundManager::Instance()->playSound("explosion", 0);
				bullet->deactivate();

			}
			break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}

		return false;
	}
	else
	{
		boss->setIsColliding(false);
		return false;
	}
}





bool CollisionManager::squaredRadiusCheck(Player* player, GameObject* object2)
{
	glm::vec2 P1 = player->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (player->getHeight() + object2->getHeight()) * 0.5f;

	

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case BOSS:
			{
				std::cout << "Collision with Enemy!" << std::endl;

				TheSoundManager::Instance()->playSound("explosion", 0);
				auto explosion = ExplosionManager::Instance()->getExplosion();
				explosion->activate();
				explosion->setPosition(glm::vec2(player->getPosition()));
			}

			TheGameManager::Instance()->setPlayerHealth(TheGameManager::Instance()->getPlayerHealth() - 1);
			TheSoundManager::Instance()->playSound("hit", 0);
			player->hitFrame = TheGame::Instance()->getFrames();
			player->invincible = true;
			break;
			case ENEMY:
				{
					std::cout << "Collision with Enemy!" << std::endl;

					TheSoundManager::Instance()->playSound("explosion", 0);
					auto explosion = ExplosionManager::Instance()->getExplosion();
					explosion->activate();
					explosion->setPosition(glm::vec2(object2->getPosition()));
				}
		
				TheGameManager::Instance()->setPlayerHealth(TheGameManager::Instance()->getPlayerHealth() - 1);
				TheSoundManager::Instance()->playSound("hit", 0);
				player->hitFrame = TheGame::Instance()->getFrames();
				player->invincible = true;
				object2->setPosition(-5000, 5000);
				break;
			case POWERUP:
				player->setSpeed(player->getSpeed() + 1);
				object2->setPosition(glm::vec2(-1000, 1000));
				player->invincible = true;

				TheSoundManager::Instance()->playSound("powerup", 0);
				GameManager::Instance()->addScore(500);
				break;
			case COIN:
				GameManager::Instance()->addScore(100);
				object2->setPosition(glm::vec2(-1000, 1000));
				TheSoundManager::Instance()->playSound("coin", 0);
				
				
				break;
			case ENEMY_BULLET:
				std::cout << "Player was hit!" << std::endl;
				TheGameManager::Instance()->setPlayerHealth(TheGameManager::Instance()->getPlayerHealth() - 1);
				TheSoundManager::Instance()->playSound("thunder", 0);
				player->hitFrame = TheGame::Instance()->getFrames();

				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}
}

bool CollisionManager::AABBCheck(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	float P1width = object1->getWidth();
	float P1height = object1->getHeight();
	float P2width = object2->getWidth();
	float P2height = object2->getHeight();

	if (
		P1.x < P2.x + P2width &&
		P1.x + P1width > P2.x&&
		P1.y < P2.y + P2height &&
		P1.y + P1height > P2.y
		)
	{


		
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			//case TARGET:
			//	std::cout << "Collision with Target!" << std::endl;
			//	TheSoundManager::Instance()->playSound("yay", 0);
			//	break;
			//case OBSTACLE:
			//	std::cout << "Collision with Obstacle!" << std::endl;
			//	TheSoundManager::Instance()->playSound("thunder", 0);
			//	break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}
			

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}

bool CollisionManager::lineLineCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float x3 = line2Start.x;
	float x4 = line2End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float y3 = line2Start.y;
	float y4 = line2End.y;

	// calculate the distance to intersection point
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		return true;
	}

	return false;
}

bool CollisionManager::lineRectCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 recStart, float recWidth, float recHeight)
{
	float x1 = line1Start.x;
	float x2 = line1End.x;
	float y1 = line1Start.y;
	float y2 = line1End.y;
	float rx = recStart.x;
	float ry = recStart.y;
	float rw = recWidth;
	float rh = recHeight;

	//TODO FIX THIS

	// check if the line has hit any of the rectangle's sides
	// uses the Line/Line function below
	bool left = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx, ry + rh));
	bool right = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx + rw, ry), glm::vec2(rx + rw, ry + rh));
	bool top = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry), glm::vec2(rx + rw, ry));
	bool bottom = lineLineCheck(glm::vec2(x1, y1), glm::vec2(x2, y2), glm::vec2(rx, ry + rh), glm::vec2(rx + rw, ry + rh));

	// if ANY of the above are true, the line
	// has hit the rectangle
	if (left || right || top || bottom) {
		return true;
	}

	return false;
}

int CollisionManager::minSquaredDistanceLineLine(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End)
{
	glm::vec2 u = line1End - line1Start;
	glm::vec2 v = line2End - line2Start;
	glm::vec2 w = line1Start - line2Start;
	float a = Util::dot(u, u);         // always >= 0
	float b = Util::dot(u, v);
	float c = Util::dot(v, v);         // always >= 0
	float d = Util::dot(u, w);
	float e = Util::dot(v, w);
	float D = a * c - b * b;					// always >= 0
	float sc, tc;

	// compute the line parameters of the two closest points
	if (D < Util::EPSILON) {					// the lines are almost parallel
		sc = 0.0;
		tc = (b > c ? d / b : e / c);			// use the largest denominator
	}
	else {
		sc = (b * e - c * d) / D;
		tc = (a * e - b * d) / D;
	}

	// get the difference of the two closest points
	glm::vec2 dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

	float norm = Util::dot(dP, dP);
	return norm;
}

int CollisionManager::circleAABBsquaredDistance(glm::vec2 circleCentre, int circleRadius, glm::vec2 boxStart, int boxWidth, int boxHeight)
{
	float dx = std::max(boxStart.x - circleCentre.x, 0.0f);
	dx = std::max(dx, circleCentre.x - (boxStart.x + boxWidth));
	float dy = std::max(boxStart.y - circleCentre.y, 0.0f);
	dy = std::max(dy, circleCentre.y - (boxStart.y + boxHeight));

	return (dx * dx) + (dy * dy);
}

bool CollisionManager::circleAABBCheck(GameObject* object1, GameObject* object2)
{
	// circle
	glm::vec2 circleCentre = object1->getPosition();
	int circleRadius = std::max(object1->getWidth() * 0.5f, object1->getHeight() * 0.5f);
	// aabb
	int boxWidth = object2->getWidth();
	int halfBoxWidth = boxWidth * 0.5f;
	int boxHeight = object2->getHeight();
	int halfBoxHeight = boxHeight * 0.5f;

	glm::vec2 boxStart = object2->getPosition() - glm::vec2(boxWidth * 0.5f, boxHeight * 0.5f);

	if (circleAABBsquaredDistance(circleCentre, circleRadius, boxStart, boxWidth, boxHeight) <= (circleRadius * circleRadius))
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			glm::vec2 attackVector = object1->getPosition() - object2->getPosition();
			glm::vec2  normal = glm::vec2(0.0f, -1.0f);

			float dot = Util::dot(attackVector, normal);
			float angle = acos(dot / Util::magnitude(attackVector)) * Util::Rad2Deg;

			switch (object2->getType()) {
			//case TARGET:
			//	std::cout << "Collision with Planet!" << std::endl;
			//	TheSoundManager::Instance()->playSound("yay", 0);
			//	break;
			//case OBSTACLE:
			//	std::cout << "Collision with Mine!" << std::endl;
			//	TheSoundManager::Instance()->playSound("thunder", 0);
			//	break;
			//case SHIP:
			//	//std::cout << "Collision with Ship!" << std::endl;
			//	TheSoundManager::Instance()->playSound("thunder", 0);

			//	if ((attackVector.x > 0 && attackVector.y < 0) || (attackVector.x < 0 && attackVector.y < 0))
			//		// top right or top left
			//	{
			//		if (angle <= 45)
			//		{
			//			object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
			//		}
			//		else
			//		{
			//			object1->setVelocity(glm::vec2(-object1->getVelocity().x, object1->getVelocity().y));
			//		}
			//	}

			//	if ((attackVector.x > 0 && attackVector.y > 0) || (attackVector.x < 0 && attackVector.y > 0))
			//		// bottom right or bottom left
			//	{
			//		if (angle <= 135)
			//		{
			//			object1->setVelocity(glm::vec2(-object1->getVelocity().x, object1->getVelocity().y));
			//		}
			//		else
			//		{
			//			object1->setVelocity(glm::vec2(object1->getVelocity().x, -object1->getVelocity().y));
			//		}
			//	}

			//	break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}


CollisionManager::CollisionManager()
{

}


CollisionManager::~CollisionManager()
{
}