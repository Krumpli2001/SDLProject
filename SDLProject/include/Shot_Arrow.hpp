#include "Engine.hpp"
#include "ObjectFactory.hpp"


class Shot_Arrow : public GameObject {
private:
	RigidBody* Arrow_RigidBody;
	Collider* Arrow_Collider;
	Vector2D Arrow_LastSafePosition;
	SpriteAnimation* Arrow_SpriteAnimation;

	int TargetPosX{};
	int TargetPosY{};

	double angle = 0;
	//bal=-1 jobb=1
	int irany = 0;

public:
	inline Shot_Arrow(Properties* props, int TX = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getX()+190/2, int TY = (*Engine::GetInstance()->getGameObjects())[0]->getPosition()->getY()+240/2) : GameObject(props) {
		GameObject_hp = props->Properies_hp;
		Arrow_RigidBody = new RigidBody();
		Arrow_RigidBody->setRigidBody_Gravity(GRAVITY);
		Arrow_Collider = new Collider();
		Arrow_Collider->setBuffer(0, 0, 0, 0);
		Arrow_SpriteAnimation = new SpriteAnimation();
		TargetPosX = TX;
		TargetPosY = TY;
		Arrow_SpriteAnimation->SetProps("shot_arrow", 0, 1, 1);
	}

	virtual void attacking(Uint64 dt);
	virtual void setAttacking(bool e) {}
	virtual bool isAttacking() { return true; }
	virtual Collider* getCollider() { return Arrow_Collider; }
	void Update(Uint64 dt);

	void Draw();
	void Clean();
	void reset();

	virtual void setGravity(double G) {}
	virtual double getAttacktime() { return 0; }
	int getAttackPower() { return 10; }
	virtual void setAttackPower(int power) {}

};