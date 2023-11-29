//Készült Madsycode tutorial-ja alapján (mondjuk 30%-a)

#include <thread>

#include "Engine.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[])
{

	Engine::GetInstance()->Init();

	/*std::jthread update;
	std::jthread render;*/

	while (Engine::GetInstance()->GetIsRunning())
	{
		Engine::GetInstance()->Events();

		/*update = std::jthread([]() { Engine::GetInstance()->Update(); });
		std::cout << update.get_id() << " update\t";
		update.join();*/

		Engine::GetInstance()->Update();

		/*render = std::jthread([]() { Engine::GetInstance()->Render(); });
		std::cout << render.get_id() << "render\t";
		render.join();*/

		Engine::GetInstance()->Render();

		Timer::GetInstance()->getTick();
	}

	Engine::GetInstance()->Clean();

	std::cout << "\nVEGE\n";

	return 0;

}