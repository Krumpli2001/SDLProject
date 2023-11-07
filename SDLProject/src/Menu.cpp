#include "Menu.hpp"
#include "Input.hpp"
#include <fstream>
#include <string>

//enum almenu {Main, GameOver, Title};

Menu* Menu::Menu_Instance = nullptr;

void Menu::MenuInit() {
	fillColorMap("assets/colors.txt");

	rublikak.push_back(rublika("Continue", 0, 0, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Options", 0, 150, 500, 150, colors["white"]));
	rublikak.push_back(rublika("Save", 0, 300, 250, 150, colors["white"]));
	rublikak.push_back(rublika("Title screen", 0, 450, 600, 150, colors["white"]));
	rublikak.push_back(rublika("Quit", 0, 600, 250, 150, colors["white"]));

	rublikak.push_back(rublika("Retry", 0, 0, 300, 150, colors["white"]));

	rublikak.push_back(rublika("Load", 0, 0, 250, 150, colors["white"]));
	rublikak.push_back(rublika("Generate", 0, 150, 500, 150, colors["white"]));

	for (int i = 0; i < rublikak.size(); i++) {
		rublikak[i].letrehoz();
	}
	menuScale = Engine::GetInstance()->getScale();
}

void Menu::Update()
{
	int prevx = cx; int prevy = cy;
	Uint32 cc = SDL_GetMouseState(&cx, &cy);

	SDL_RenderSetScale(Engine::GetInstance()->getRenderer(), 1.0f, 1.0f);


	if (cx != prevx or cy != prevy) {
		rublikak[highLighted].isHighlighted = false;
		eger = true;
	}

	options.clear();
	int code = Input::GetInstance()->getElse();

	if (Main) {
		

		if (melyik("Continue", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) { enter = false; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);

		getIndex("Options", &index);
		rublikak[index].setRectLocation(0, 150);
		if (melyik("Options", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) {}
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);


		if (melyik("Save", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) {}
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);

		getIndex("Quit", &index);
		rublikak[index].setRectLocation(0, 600);
		if (melyik("Quit", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) {	/*Main = false; Title = true;*/ Engine::GetInstance()->Quit();  }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);

		getIndex("Title screen", &index);
		rublikak[index].setRectLocation(0, 450);
		if (melyik("Title screen", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) {
				Main = false; Title = true; return; /*Engine::GetInstance()->Quit();*/
			}
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);


		if (code == SDL_SCANCODE_ESCAPE) {
			Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing());
			SDL_Delay(200);
		}
	}

	if (GameOver) {
		
		melyik("Quit", &index);
		rublikak[index].setRectLocation(0, 150);

		if (melyik("Retry", &index)) {
			RUpdate("gold", index);
			if (cc == 1 or enter) { Reset(); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);


		if (melyik("Quit", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { rublikak[index].color = getColor("white"); rublikak[index].letrehoz(); }
		options.push_back(index);

	}

	if (Title) {

		if (melyik("Load", &index)) {
			RUpdate("green", index);
			if (cc == 1 or enter) { Title = false; Main = true; Engine::GetInstance()->setMenuShowing(!Engine::GetInstance()->getMenuShowing()); }
		}
		else { doelse("white", index); }
		options.push_back(index);

		if (melyik("Generate", &index)) {
			RUpdate("green", index);
			if (cc == 1 or enter) {}
		}
		else { doelse("white", index); }
		options.push_back(index);

		getIndex("Options", &index);
		rublikak[index].setRectLocation(0, 300);
		if (melyik("Options", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) {}
		}
		else { doelse("white", index); }
		options.push_back(index);

		melyik("Quit", &index);
		rublikak[index].setRectLocation(0, 450);
		if (melyik("Quit", &index)) {
			RUpdate("red", index);
			if (cc == 1 or enter) { Engine::GetInstance()->Quit(); }
		}
		else { doelse("white", index); }
		options.push_back(index);
	}


	switch (code)
	{
	case 3:
		setHighlighted(-1);
		SDL_Delay(100);
		break;
	case 4:
		setHighlighted(1);
		SDL_Delay(100);
		break;
	case 5:
		setEnter();
		SDL_Delay(100);
		break;
	}

}

void Menu::Draw()
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->getRenderer());

	if (Main and !Engine::GetInstance()->getResetFlag()) {
		for (int i = 0; i < options.size(); i++) {
			SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[options[i]].Message, NULL, &rublikak[options[i]].doboz);
			SDL_FreeSurface(rublikak[options[i]].surfaceMessage);
			SDL_DestroyTexture(rublikak[options[i]].Message);
		}
	}

	//ezt szepiteni kell - csak teszt
	if (GameOver) {

		for (int i = 0; i <options.size(); i++) {
			SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[options[i]].Message, NULL, &rublikak[options[i]].doboz);
			SDL_FreeSurface(rublikak[options[i]].surfaceMessage);
			SDL_DestroyTexture(rublikak[options[i]].Message);
		}
		/*int retry = 4;
		int quit = 3;

		SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[retry].Message, NULL, &rublikak[retry].doboz);
		SDL_FreeSurface(rublikak[retry].surfaceMessage);
		SDL_DestroyTexture(rublikak[retry].Message);

		SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[quit].Message, NULL, &rublikak[quit].doboz);
		SDL_FreeSurface(rublikak[quit].surfaceMessage);
		SDL_DestroyTexture(rublikak[quit].Message);*/
	}

	if (Title) {
		for (int i = 0; i < options.size(); i++) {
			SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[options[i]].Message, NULL, &rublikak[options[i]].doboz);
			SDL_FreeSurface(rublikak[options[i]].surfaceMessage);
			SDL_DestroyTexture(rublikak[options[i]].Message);
		}
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
	//if (highLighted > options.size() - 1) { highLighted = options.size() - 1; }
	//if (highLighted < 0) { highLighted = 0; }
	int index=0;
	for(int j = 0; j<options.size();j++){if(options[j]==highLighted){ index = j; } }
	int prevHol = index;

	//int prevHol = 0;
	eger = false;
	rublikak[options[index]].isHighlighted = true;
	
		if (i == 1) {
			prevHol = index;
			index -= 1;
			if (index <= -1) {
				index = options.size() - 1;
			}
		}
		if (i == -1) {
			prevHol = index;
			index += 1;
			if (index >= options.size()) {
				index = 0;
			}
		}

		rublikak[options[index]].isHighlighted = true;
		rublikak[options[prevHol]].isHighlighted = false;
		highLighted = options[index];
}

void Menu::Reset()
{
	Engine::GetInstance()->setResetFlag(true);
	GameOver = false;
	Main = true;
	std::ignore = melyik("Quit", &index);
	rublikak[index].setRectLocation(0, 450);
}

void Menu::doelse(std::string str, int index) {
	rublikak[index].color = getColor(str);
	rublikak[index].letrehoz();
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
	SDL_SetRenderDrawColor(Engine::GetInstance()->getRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::GetInstance()->getRenderer());

	for (int i = 0; i < rublikak.size(); i++) {
		SDL_RenderCopy(Engine::GetInstance()->getRenderer(), rublikak[i].second.Message, NULL, &rublikak[i].second.doboz);
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