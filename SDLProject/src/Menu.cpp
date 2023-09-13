#include "Menu.hpp"
#include <fstream>
#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150));
	rublikak.push_back(rublika("Quit", 0, 300, 250, 150));

	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}


	//print_map(colors);
}

void Menu::Update()
{
	int prevx = Menu::GetInstance()->cx; int prevy = Menu::GetInstance()->cy;
	Uint32 cc = SDL_GetMouseState(&Menu::GetInstance()->cx, &Menu::GetInstance()->cy);


	if (Menu::GetInstance()->cx != prevx or Menu::GetInstance()->cy != prevy) {
		Menu::GetInstance()->rublikak[Menu::highLighted].isHighlighted = false;
	}

	//continue
	if ((Menu::GetInstance()->cx >= rublikak[0].doboz.x and Menu::GetInstance()->cy > rublikak[0].doboz.y 
		and Menu::GetInstance()->cx <= rublikak[0].doboz.w + rublikak[0].doboz.x and Menu::GetInstance()->cy <= rublikak[0].doboz.h + rublikak[0].doboz.y) or rublikak[0].isHighlighted) {
		rublikak[0].color = getColor("gold");
		rublikak[0].letrehoz();
		if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
	}
	else { rublikak[0].color = getColor("white"); rublikak[0].letrehoz(); }

	//Options
	if ((Menu::GetInstance()->cx >= rublikak[1].doboz.x and Menu::GetInstance()->cy > rublikak[1].doboz.y 
		and Menu::GetInstance()->cx <= rublikak[1].doboz.w + rublikak[1].doboz.x and Menu::GetInstance()->cy <= rublikak[1].doboz.h + rublikak[1].doboz.y) or rublikak[1].isHighlighted) {
		rublikak[1].color = getColor("gold");
		rublikak[1].letrehoz();
		if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
	}
	else { rublikak[1].color = getColor("white"); rublikak[1].letrehoz(); }

	//quit
if ((Menu::GetInstance()->cx >= rublikak[2].doboz.x and Menu::GetInstance()->cy > rublikak[2].doboz.y 
		and Menu::GetInstance()->cx <= rublikak[2].doboz.w + rublikak[2].doboz.x and Menu::GetInstance()->cy <= rublikak[2].doboz.h + rublikak[2].doboz.y) or rublikak[2].isHighlighted) {
		rublikak[2].color = getColor("red");
		rublikak[2].letrehoz();
		if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
	}
	else { rublikak[2].color = getColor("white"); rublikak[2].letrehoz(); }

}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	for (int i = 0; i < rublikak.size(); i++) {
		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[i].Message, NULL, &rublikak[i].doboz);
	}

}

void Menu::Clean()
{
	for (int i = 0; i < rublikak.size(); i++)
	{
		SDL_FreeSurface(rublikak[i].surfaceMessage);
		SDL_DestroyTexture(rublikak[i].Message);
	}
	rublikak.clear();

	colors.clear();

	/*SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);*/
	std::cout << "\nText is deleted\n";
}

void Menu::fillColorMap(std::string source)
{
	std::string egysor = "";
	std::string szin = "";
	std::string szam = "";
	unsigned char r = 0; unsigned char g = 0; unsigned char b = 0;
	std::ifstream f(source);
	//int i = 0;
	int betu = 0;

	if (f.is_open()) {
		while (std::getline(f, egysor)) {
			//int i = 0;
			int betu = 0;
			while (betu < egysor.length()) {
				while (egysor[betu] != '_' or egysor[betu+1] != ' ') {
					szin += std::tolower(egysor[betu]);
					betu++;
				}
				while (egysor[betu] != ' ' and egysor[betu+1] != '(') { betu++; }

				betu++;

				if (egysor[betu] == ' ' and egysor[betu+1] == '(') {
					int vesszok = 0;
					betu += 2;
					while (vesszok <= 2) {
						if (egysor[betu] != ',' and egysor[betu] != ')') {
							szam += egysor[betu];
							betu++;
						}
						else { 
							switch (vesszok){
							case 0:
								r = std::stoi(szam);
								break;
							case 1:
								g = std::stoi(szam);
								break;
							case 2:
								b = std::stoi(szam);
								break;
							}

							szam = "";
							vesszok++;
							betu++;
						}

					}
				}
				colors[szin] = SDL_Color{ r,g,b };
				betu = egysor.length();
			}
			egysor = "";
			//std::cout << szin<<"\n";
			szin = "";
		}
		f.close();
	}
	else {
		std::cerr << "\nnem lehetett megnyitni a szines fajlt\n";
	}
}

//billentyuzethez
void Menu::setHighlighted(int i) {
	int prevHol = 0;
	Menu::GetInstance()->rublikak[Menu::highLighted].isHighlighted = true;
	
		if (i == 1) {
			prevHol = Menu::highLighted;
			Menu::highLighted -= 1;
			if (Menu::highLighted <= -1) {
				Menu::highLighted = rublikak.size() - 1;
			}
		}
		if (i == -1) {
			prevHol = Menu::highLighted;
			Menu::highLighted += 1;
			if (Menu::highLighted >= rublikak.size()) {
				Menu::highLighted = 0;
			}
		}

		Menu::GetInstance()->rublikak[Menu::highLighted].isHighlighted = true;
		Menu::GetInstance()->rublikak[prevHol].isHighlighted = false;

}