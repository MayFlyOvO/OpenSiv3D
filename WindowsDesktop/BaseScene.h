#pragma once

# include <Siv3D.hpp>
# include <memory>

# include "Components.h"

using App = SceneManager<String>;
using BaseScene = ECS::BaseScene<String>;


class Test : public App::Scene
{
public:
	Test(const InitData& init)
		: IScene{ init }
	{}
};
