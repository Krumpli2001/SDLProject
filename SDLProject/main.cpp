//#include <thread>

#include "Engine.hpp"

int main(int argc, char* argv[])
{
	
	Engine::GetInstance()->Init();
	auto engineInstance = Engine::GetInstance();
	auto timerInstance = Timer::GetInstance();

	/*std::jthread update;
	std::jthread render;*/

	while (engineInstance->GetIsRunning())
	{
		engineInstance->Events();

		/*update = std::jthread([]() { Engine::GetInstance()->Update(); });
		update.join();*/

		engineInstance->Update();

		/*render = std::jthread([]() { Engine::GetInstance()->Render(); });
		render.join();*/

		engineInstance->Render();

		timerInstance->getTick();
	}

	engineInstance->Clean();
	Engine::GetInstance(true);
	std::cout << "\nVEGE\n";

	return 0;

}