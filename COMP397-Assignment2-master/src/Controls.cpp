#include "Controls.h"
#include "TextureManager.h"
#include "Game.h"

Controls::Controls()
{
	TheTextureManager::Instance()->load("../Assets/textures/Controls.png",
		"controls", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("Controls");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setType(GameObjectType::CONTROLS);

}

Controls::~Controls()
= default;

void Controls::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("controls", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Controls::update()
{

}

void Controls::clean()
{
}

