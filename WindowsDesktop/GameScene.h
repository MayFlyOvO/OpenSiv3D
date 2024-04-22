#pragma once

# include "BaseScene.h"

class GameScene : public BaseScene
{
public:

	GameScene(const InitData& init);

	~GameScene();

	void update() override;

	void draw() const override;

private:
	ECS::Entity m_mainCamera;

	ECS::Entity m_ground;
	ECS::Entity m_player;
	ECS::Entity m_mirror;
};
