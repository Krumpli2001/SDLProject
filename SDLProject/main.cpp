//Készült Madsycode tutorial-ja alapján (mondjuk 30%-a)

//#include <thread>

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
		update.join();*/

		Engine::GetInstance()->Update();

		/*render = std::jthread([]() { Engine::GetInstance()->Render(); });
		render.join();*/

		Engine::GetInstance()->Render();

		Timer::GetInstance()->getTick();
	}

	Engine::GetInstance()->Clean();

	std::cout << "\nVEGE\n";

	return 0;

}