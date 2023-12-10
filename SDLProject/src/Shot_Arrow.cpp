#include "Shot_Arrow.hpp"

static Registrar < Shot_Arrow > registrararrow("ARROW");

bool Shot_Arrow::attacking(Uint64 dt)
{
	/*if (Enemy_AttackTimer == 1000) {
		Enemy_AttackTimer -= dt;*/
		GameObject_hp = 0;
		return true;
	//}
	//return false;
}

void Shot_Arrow::Update(Uint64 dt)
{
	//ehelyett a magic number kep meret helyett kell majd jobb megoldás...
	Arrow_Collider->setBox(static_cast<int>(GameObject_Transform->getX()), static_cast<int>(GameObject_Transform->getY()), 20, 100);
}

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