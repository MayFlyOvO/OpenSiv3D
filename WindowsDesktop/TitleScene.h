#pragma once

# include "BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene(const InitData& init);

	~TitleScene();

	void update() override;

	void draw() const override;
};
