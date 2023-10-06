#include "Menu.hpp"
#include "Input.hpp"
#include <fstream>
#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Save", 0, 300, 250, 150, colors["white"]));
	rublikak.push_back(rublika("Quit", 0, 450, 250, 150, colors["white"]));

	rublikak.push_back(rublika("Retry", 0, 0, 300, 150, colors["white"]));

	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}
}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);


	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	int code = Input::GetInstance()->getElse();

	switch(code)
	{case 3:
		setHighlighted(-1);
		SDL_Delay(200);
		break;
	case 4:
		setHighlighted(1);
		SDL_Delay(200);
		break;
	case 5:
		setEnter();
		SDL_Delay(200);
		break;
	}

	//int index = 0;

	if (Main) {
		

		if (melyik("Continue", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }

		if (melyik("Options", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) {}
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }

		if (melyik("Save", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) {}
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }

		if (melyik("Quit", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }

		if (code == SDL_SCANCODE_ESCAPE) {
			Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
			SDL_Delay(200);
		}
	}

	if (GameOver) {
		
		std::ignore = melyik("Quit", &index);
		rublikak[index].setRectLocation(0, 150);

		if (melyik("Retry", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) { Reset(); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }


		if (melyik("Quit", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }

	}

}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	if (Main) {
		for (int i = 0; i <= 3; i++) {
			SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[i].Message, NULL, &rublikak[i].doboz);
			SDL_FreeSurface(rublikak[i].surfaceMessage);
			SDL_DestroyTexture(rublikak[i].Message);
		}
	}

	//ezt szepiteni kell - csak teszt
	if (GameOver) {

		for (int i = 3; i <= 4; i++) {
			SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[i].Message, NULL, &rublikak[i].doboz);
			SDL_FreeSurface(rublikak[i].surfaceMessage);
			SDL_DestroyTexture(rublikak[i].Message);
		}
		/*int retry = 4;
		int quit = 3;

		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[retry].Message, NULL, &rublikak[retry].doboz);
		SDL_FreeSurface(rublikak[retry].surfaceMessage);
		SDL_DestroyTexture(rublikak[retry].Message);

		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[quit].Message, NULL, &rublikak[quit].doboz);
		SDL_FreeSurface(rublikak[quit].surfaceMessage);
		SDL_DestroyTexture(rublikak[quit].Message);*/
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

void Menu::Reset()
{
	Engine::GetInstance()->setResetFlag(true);
	GameOver = false;
	Main = true;
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, 450);
}



/*
#include "Menu.hpp"
#include <fstream>
#include <string>

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak.push_back(std::make_pair(std::string("Continue"), rublika("Continue", 0, 0, 500, 150)));
	rublikak.push_back(std::make_pair(std::string("Options"), rublika("Options", 0, 150, 500, 150)));
	rublikak.push_back(std::make_pair(std::string("Save"), rublika("Save", 0, 300, 250, 150)));
	rublikak.push_back(std::make_pair(std::string("Quit"), rublika("Quit", 0, 450, 250, 150)));

	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].second.letrehoz();
	}
}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);

	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].second.isHighlighted = false;
		eger = true;
	}

	if (Main) {

		int index = 0;
		//continue
		if(melyik("Continue", &index)) {
			rublikak[index].second.color = getColor("gold");
			rublikak[index].second.letrehoz();
			if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak[index].second.color = getColor("white"); rublikak[index].second.letrehoz(); }

		//Options
		if (melyik("Options", &index)) {
			rublikak[index].second.color = getColor("gold");
			rublikak[index].second.letrehoz();
			//if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak[index].second.color = getColor("white"); rublikak[index].second.letrehoz(); }

		//Save
		if (melyik("Save", &index)) {
			rublikak[index].second.color = getColor("gold");
			rublikak[index].second.letrehoz();
			//if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak[index].second.color = getColor("white"); rublikak[index].second.letrehoz(); }

		//quit
		if (melyik("Quit", &index)) {
			rublikak[index].second.color = getColor("red");
			rublikak[index].second.letrehoz();
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { rublikak[index].second.color = getColor("white"); rublikak[index].second.letrehoz(); }
	}

}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	for (int i = 0; i < rublikak.size(); i++) {
		SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), rublikak[i].second.Message, NULL, &rublikak[i].second.doboz);
		//SDL_FreeSurface(rublikak[i].second.surfaceMessage);
		//SDL_DestroyTexture(rublikak[i].second.Message);
	}

}

void Menu::Clean()
{
	if (!Engine::GetInstance()->getMenuShowing()) {
		for (int i = 0; i < rublikak.size(); i++) {
			SDL_FreeSurface(rublikak[i].second.surfaceMessage);
			SDL_DestroyTexture(rublikak[i].second.Message);
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
	int prevHol = 0;
	rublikak[highLighted].second.isHighlighted = true;
	//Menu::GetInstance()->rublikak[Menu::highLighted].isHighlighted = true;
	
		if (i == 1) {
			prevHol = highLighted;
			if (prevHol == 0) { highLighted = rublikak.size() - 1; }
			else { highLighted--; }
		}
		if (i == -1) {
			prevHol = highLighted;
			if (prevHol == rublikak.size() - 1 ) { highLighted = 0; }
			else { highLighted++; }
		}

		rublikak[highLighted].second.isHighlighted = true;
		rublikak[prevHol].second.isHighlighted = false;

}
*/