//Készült Madsycode tutorial-ja alapján (mondjuk 30%-a)

#include "Engine.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[])
{

	Engine::GetInstance()->Init();
	while (Engine::GetInstance()->GetIsRunning())
	{
		Engine::GetInstance()->Events();
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Render();
		Timer::GetInstance()->getTick();
	}

	Engine::GetInstance()->Clean();

	std::cout << "\nVEGE\n";

	return 0;

}