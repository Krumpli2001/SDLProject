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
	int prevx = cx; int prevy = cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);


	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	//continue
	if (melyik(0)) {
		rublikak[0].color = getColor("gold");
		rublikak[0].letrehoz();
		highLighted = 0;
		if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
	}
	else { rublikak[0].color = getColor("white"); rublikak[0].letrehoz(); }

	//Options
	if (melyik(1)) {
		rublikak[1].color = getColor("gold");
		rublikak[1].letrehoz();
		highLighted = 1;
		if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
	}
	else { rublikak[1].color = getColor("white"); rublikak[1].letrehoz(); }

	//quit
if (melyik(2)) {
		rublikak[2].color = getColor("red");
		rublikak[2].letrehoz();
		highLighted = 2;
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
		SDL_FreeSurface(rublikak[i].surfaceMessage);
		SDL_DestroyTexture(rublikak[i].Message);
	}

}

void Menu::Clean()
{
	if (!Engine::GetInstance()->getMenuShowing()) {
		for (int i = 0; i < rublikak.size(); i++)
		{
			SDL_FreeSurface(rublikak[i].surfaceMessage);
			SDL_DestroyTexture(rublikak[i].Message);
		}
	}
	
	rublikak.clear();

	colors.clear();

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
	eger = false;
	rublikak[highLighted].isHighlighted = true;
	
		if (i == 1) {
			prevHol = highLighted;
			highLighted -= 1;
			if (highLighted <= -1) {
				highLighted = rublikak.size() - 1;
			}
		}
		if (i == -1) {
			prevHol = highLighted;
			highLighted += 1;
			if (highLighted >= rublikak.size()) {
				highLighted = 0;
			}
		}

		rublikak[highLighted].isHighlighted = true;
		rublikak[prevHol].isHighlighted = false;

}



/*
#include "Menu.hpp"
#include <fstream>
#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak["Continue"] = rublika("Continue", 0, 0, 500, 150);
	rublikak["Options"] = rublika("Options", 0, 150, 500, 150);
	rublikak["Save"] = rublika("Save", 0, 300, 250, 150);
	rublikak["Quit"] = rublika("Quit", 0, 450, 250, 150);

	for (auto i = rublikak.begin(); i != rublikak.end(); i++) {
		i->second.letrehoz();
	}

	highLighted = rublikak.begin(); //iteratort nem elfelejteni resetelni...
	//print_map(colors);
}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);

	if (cx != prevx or cy != prevy) {
		highLighted->second.isHighlighted = false;
	}

	if (Main) {

		//continue
		if ((cx >= rublikak["Continue"].doboz.x and cy > rublikak["Continue"].doboz.y
			and cx <= rublikak["Continue"].doboz.w + rublikak["Continue"].doboz.x and cy
			<= rublikak["Continue"].doboz.h + rublikak["Continue"].doboz.y) or rublikak["Continue"].isHighlighted) {
			rublikak["Continue"].color = getColor("gold");
			rublikak["Continue"].letrehoz();
			if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak["Continue"].color = getColor("white"); rublikak["Continue"].letrehoz(); }

		//Options
		if ((cx >= rublikak["Options"].doboz.x and cy > rublikak["Options"].doboz.y
			and cx <= rublikak["Options"].doboz.w + rublikak["Options"].doboz.x and cy
			<= rublikak["Options"].doboz.h + rublikak["Options"].doboz.y) or rublikak["Options"].isHighlighted) {
			rublikak["Options"].color = getColor("gold");
			rublikak["Options"].letrehoz();
			//if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak["Options"].color = getColor("white"); rublikak["Options"].letrehoz(); }

		//Save
		if ((cx >= rublikak["Save"].doboz.x and cy > rublikak["Save"].doboz.y
			and cx <= rublikak["Save"].doboz.w + rublikak["Save"].doboz.x and cy
			<= rublikak["Save"].doboz.h + rublikak["Save"].doboz.y) or rublikak["Save"].isHighlighted) {
			rublikak["Save"].color = getColor("gold");
			rublikak["Save"].letrehoz();
			//if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak["Save"].color = getColor("white"); rublikak["Save"].letrehoz(); }

		//quit
		if ((cx >= rublikak["Quit"].doboz.x and cy > rublikak["Quit"].doboz.y
			and cx <= rublikak["Quit"].doboz.w + rublikak["Quit"].doboz.x and cy
			<= rublikak["Quit"].doboz.h + rublikak["Quit"].doboz.y) or rublikak["Quit"].isHighlighted) {
			rublikak["Quit"].color = getColor("red");
			rublikak["Quit"].letrehoz();
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { rublikak["Quit"].color = getColor("white"); rublikak["Quit"].letrehoz(); }
	}

}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	for (auto i = rublikak.begin(); i != rublikak.end(); i++) {
		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), i->second.Message, NULL, &i->second.doboz);
		SDL_FreeSurface(i->second.surfaceMessage);
		SDL_DestroyTexture(i->second.Message);
	}

}

void Menu::Clean()
{
	if (!Engine::GetInstance()->getMenuShowing()) {
		for (auto i = rublikak.begin(); i != rublikak.end(); i++) {
			SDL_FreeSurface(i->second.surfaceMessage);
			SDL_DestroyTexture(i->second.Message);
		}
	}
	
	rublikak.clear();

	colors.clear();

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
		std::cerr << "\nNem lehetett megnyitni a szines fajlt\n";
	}
}

//billentyuzethez
void Menu::setHighlighted(int i) {
	auto prevHol = rublikak.begin();
	highLighted->second.isHighlighted = true;
	//Menu::GetInstance()->rublikak[Menu::highLighted].isHighlighted = true;
	
		if (i == 1) {
			prevHol = highLighted;
			if (prevHol->first == "Continue") { highLighted = std::prev(rublikak.end()); }
			else { highLighted = std::prev(highLighted); }
		}
		if (i == -1) {
			prevHol = highLighted;
			if (prevHol->first == "Quit") { highLighted = rublikak.begin(); }
			else { highLighted = std::next(highLighted); }
		}

		highLighted->second.isHighlighted = true;
		prevHol->second.isHighlighted = false;

}
*/