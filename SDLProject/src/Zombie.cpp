#include "Enemy.hpp"

static Registrar < Zombie > registrar("ZOMBIE");

void Zombie::AnimationState() {
	Enemy_SpriteAnimation->SetProps("zombie_idle", 0, 4, 400);
 }