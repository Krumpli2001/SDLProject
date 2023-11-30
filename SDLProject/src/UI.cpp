#include "UI.hpp"

void UI::Update()
{
	scale = Engine::GetInstance()->getScale();
	if (FpsShowing) {
		FPSCounter::GetInstance()->Update();
	}

	php = (*Engine::GetInstance()->getGameObjects())[0]->getHP();
	mphp = (*Engine::GetInstance()->getGameObjects())[0]->getMaxHP();
	std::string str = std::to_string(php) + " / " + std::to_string(mphp);
	surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
	Message = SDL_CreateTextureFromSurface(Engine::GetInstance()->getRenderer(), surfaceMessage);
	Message_rect = { static_cast<int>((*Engine::GetInstance()->getWindow_W() - 150) * 1/scale), 0, static_cast<int>(100 * (1 / scale)), static_cast<int>(20 * (1 / scale)) };
}

void UI::Draw()
{
	if (FpsShowing) {
		FPSCounter::GetInstance()->Draw();
	}

	
	if (php > 0) {

		int szivekSzama = std::ceil(static_cast<double>(mphp) / 20.0 * (static_cast<double>(php) / static_cast<double>(mphp)));
		//std::cout << szivekSzama << "\n";
		int kezdopixel /*for now*/ = 40;
		double heartmeret = 40.0;

		for (int i = szivekSzama; i > 0; i--) {

			//php % 20.0 / 20;

			int x = i == 1 ? (*Engine::GetInstance()->getWindow_W() - kezdopixel + heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp)))) * (1.0 / scale) : ((*Engine::GetInstance()->getWindow_W() - kezdopixel) / scale);
			int w = i==1 ? heartmeret * (static_cast<double>(php) / static_cast<double>(mphp)) * (1.0 / scale) : heartmeret * (1.0 / scale);
			int srcx = i == 1 ? heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp))) : 0;

			TextureManager::GetInstance()->Draw("heart",
				/*x*/ //(*Engine::GetInstance()->getWindow_W() - kezdopixel + heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp)))) * (1.0 / scale),
				x,
				/*y*/ 20 * (1.0/scale),
				/*w*/ //heartmeret * (static_cast<double>(php) / static_cast<double>(mphp)) * (1.0 / scale),
				 w,
				/*h*/ heartmeret * (1.0 / scale),
				/*srcx*/ //heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp))),
				 srcx,
				/*srcy*/ 0,
				true,
				SDL_FLIP_NONE,
				1);
			kezdopixel += 40;
		}

		//TextureManager::GetInstance()->Draw("heart", (*Engine::GetInstance()->getWindow_W() - 200 + 40.0 * (1.0 - (php / 100.0))) * (1 / scale), 40, 40.0 * (php / 100.0) * (1 / scale), 40 * (1 / scale), 40.0 * (1.0 - (php / 100.0)), 0, true, SDL_FLIP_NONE, 1);
		
		//std::cout << (*Engine::GetInstance()->getWindow_W() - kezdopixel + heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp)))) * (1.0 / scale) << "\t" << heartmeret << "\t" << heartmeret * (static_cast<double>(php) / static_cast<double>(mphp)) * (1.0 / scale) << "\t" << heartmeret * (1.0 / scale) << "\t" << heartmeret * (1.0 - (static_cast<double>(php) / static_cast<double>(mphp))) << "\t" << 0 << "\n";
		//std::cout << (*Engine::GetInstance()->getWindow_W() - 200 + 40.0 * (1.0 - (php / 100.0))) * (1 / scale) <<"\t" << 40 << "\t" << 40.0 * (php / 100.0) * (1 / scale) << "\t" << 40 * (1 / scale) << "\t" << 40.0 * (1.0 - (php / 100.0))<< "\t" << 0<<"\n";

		//std::cout << 40.0 * (100.0 / php) << "\t"<< php << "\n";
	}

	SDL_RenderCopy(Engine::GetInstance()->getRenderer(), Message, NULL, &Message_rect);
	Clean();
	surfaceMessage = nullptr;
	Message = nullptr;
}

void UI::Clean()
{
	FPSCounter::GetInstance()->Clean();
	if (surfaceMessage) { SDL_FreeSurface(surfaceMessage); }
	if (Message) { SDL_DestroyTexture(Message); }
}
