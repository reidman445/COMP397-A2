#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Background.h"
#include "BackToMenuButton.h"
#include "Scene.h"
#include "Label.h"
#include "TryAgainButton.h"

class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	glm::vec2 getMousePosition() const;

private:
	glm::vec2 m_mousePosition;

	Background* m_pBackground;

	
	Label* m_label{};
	Label* m_enemiesDestroyed;
	Label* m_score;
	TryAgainButton* m_pTryAgainButton;
	BackToMenuButton* m_pBackToMenuButton;
};

#endif /* defined (__END_SCENE__) */