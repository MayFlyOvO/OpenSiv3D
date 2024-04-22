#pragma once

# include "BaseScene.h"

class ResultScene : public BaseScene
{
public:

	ResultScene(const InitData& init);

	~ResultScene();

	void update() override;

	void draw() const override;
};
