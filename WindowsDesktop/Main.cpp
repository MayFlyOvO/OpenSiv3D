# include <Siv3D.hpp> // Siv3D v0.6.14

# include "Scenes.h"

static void SystemInit()
{
	Window::SetTitle(U"Siv3D Mini Game");
	Window::Resize(1280, 720);
}

void Main()
{
	SystemInit();

	App manager;
	{
		//manager.add<TitleScene>(U"Title");
		manager.add<GameScene>(U"Game");
		//manager.add<ResultScene>(U"Result");

#ifdef _DEBUG
		manager.init(U"Game");
#endif // _DEBUG
	}


	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
