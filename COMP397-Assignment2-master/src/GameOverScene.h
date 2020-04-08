#pragma once
#ifndef __GAME__OVER_SCENE__
#define __GAME__OVER_SCENE__

#include "Background.h"
#include "BackToMenuButton.h"
#include "Scene.h"
#include "Label.h"
#include "TryAgainButton.h"

class GameOverScene final : public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	glm::vec2 getMousePosition() const;

private:
	
	Background* m_pBackground;

	
	glm::vec2 m_mousePosition;

	
	Label* m_label{};
	Label* m_enemiesDestroyed;
	Label* m_score;

	TryAgainButton* m_pTryAgainButton;
	BackToMenuButton* m_pBackToMenuButton;
	
};

#endif /* defined (__GAME__OVER_SCENE__) */