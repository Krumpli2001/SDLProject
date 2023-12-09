#include "Shot_Arrow.hpp"

static Registrar < Shot_Arrow > registrararrow("ARROW");

void Shot_Arrow::Draw(double scale)
{
	Arrow_SpriteAnimation->Draw(GameObject_Transform->getX(), GameObject_Transform->getY(), GameObject_Width, GameObject_Height, GameObject_Flip, scale);
}

void Shot_Arrow::Clean()
{
	TextureManager::GetInstance()->Drop(GameObject_TextureID);
}

void Shot_Arrow::reset()
{
	GameObject_hp = 0;
}