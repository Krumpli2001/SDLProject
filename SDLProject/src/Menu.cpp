#include "Menu.hpp"
#include <fstream>
#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak.push_back(rublika("Continue", 0, 0, 1000, 300));
	rublikak.push_back(rublika("Quit", 0, 300, 500, 300));

	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}


	//print_map(colors);
}

void Menu::Update()
{
	int cx, cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);

	if (cx >= 0 and cy >= 0 and cx <= 1000 and cy <= 300) {
		rublikak[0].color = getColor("gold");
		rublikak[0].letrehoz();
		if (cc == 1) { Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
	}
	else { rublikak[0].color = getColor("white"); rublikak[0].letrehoz(); }

	if (cx >= 0 and cy >= 300 and cx <= 500 and cy <= 600) {
		rublikak[1].color = getColor("red");
		rublikak[1].letrehoz();
		if(cc==1)Engine::GetInstance()->Quit();
	}
	else { rublikak[1].color = getColor("white"); rublikak[1].letrehoz(); }

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
