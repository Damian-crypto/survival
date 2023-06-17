#include "zeus.h"
#include "game_layer.h"

int main()
{
	auto app = new zeus::Application({ "Survival", WIDTH, HEIGHT, false, true });
	app->Init();
	app->PushLayer(new GameLayer("game_layer"));
	app->Run();
	delete app;

	return 0;
}
