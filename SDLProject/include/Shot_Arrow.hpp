#include "Engine.hpp"
#include "GameObject.hpp"
#include "ObjectFactory.hpp"


class Shot_Arrow : public GameObject {
private:
	RigidBody* Arrow_RigidBody;
	Collider* Arrow_Collider;
	Vector2D Arrow_LastSafePosition;
	SpriteAnimation* Arrow_SpriteAnimation;

	int TargetPosX{};
	int TargetPosY{};

public:
	inline Shot_Arrow(Properties* props, int TX = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX(), int TY = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY()) : GameObject(props) {
		GameObject_hp = props->Properies_hp;
		Arrow_RigidBody = new RigidBody();
		Arrow_RigidBody->setRigidBody_Gravity(GRAVITY);
		Arrow_Collider = new Collider();
		Arrow_Collider->setBuffer(0, 0, 0, 0);
		Arrow_SpriteAnimation = new SpriteAnimation();
		TargetPosX = TX;
		TargetPosY = TY;
	}

	virtual bool attacking(Uint64 dt) { return false; }
	virtual void setAttacking(bool e) {}
	virtual bool isAttacking() { return false; }
	virtual Collider* getCollider() { return Arrow_Collider; }
	virtual void Update(Uint64 dt) {}

	void Draw(double scale);
	void Clean();
	void reset();

	virtual void setGravity(double G) {}
	virtual double getAttacktime() { return 0; }
	virtual int getAttackPower() { return 10; }
	virtual void setAttackPower(int power) {}

};