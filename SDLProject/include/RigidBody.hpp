#pragma once

#include "Vector2D.hpp"

#define UNIT_MASS 1.0
#define GRAVITY 1
#define JOBBRA 1
#define BALRA -1
#define FEL -1
#define LE 1

class RigidBody
{
private:
	double RigidBody_Mass;
	double RigidBody_Gravity;
	Vector2D RigidBody_Force;
	Vector2D RigidBody_Friction;
	Vector2D RigidBody_Position;
	Vector2D RigidBody_Velocity;
	Vector2D RigidBody_Accelaration;
public:
	inline RigidBody() : RigidBody_Mass(UNIT_MASS), RigidBody_Gravity(GRAVITY), RigidBody_Friction(0) {}

	 inline void setRigidBody_Mass(double mass) { RigidBody_Mass = mass; }
	 inline void setRigidBody_Gravity(double gravity) { RigidBody_Gravity = gravity; }

	 inline void ApplyForce(Vector2D F) { RigidBody_Force = F; }
	 inline void ApplyForceX(double Fx) { RigidBody_Force.setX(Fx); }
	 inline void ApplyForceY(double Fy) { RigidBody_Force.setY(Fy); }
	 inline void SetForceToZero() { RigidBody_Force = Vector2D(0.0, 0.0); }

	 inline void ApplyFriction(Vector2D Fr) { RigidBody_Friction = Fr; }
	 inline void SetFrictionToZero() { RigidBody_Friction = Vector2D(0.0, 0.0); }

	 inline double getGravity() { return RigidBody_Gravity; }
	 inline double getRigidBody_Mass() { return RigidBody_Mass; }
	 inline Vector2D getRigidBody_Position() { return RigidBody_Position; }
	 inline Vector2D getRigidBody_Velocity() { return RigidBody_Velocity; }
	 inline Vector2D getRigidBody_Accelaration() { return RigidBody_Accelaration; }


	 inline void Update(Uint64 dt)
	 {
		 RigidBody_Accelaration.setX((RigidBody_Force.getX() + RigidBody_Friction.getX()) / RigidBody_Mass);
		 RigidBody_Accelaration.setY(((RigidBody_Gravity + RigidBody_Force.getY()) / RigidBody_Mass)); // szerintem ez itt rossz
		 Vector2D voltpos = RigidBody_Position;
		 RigidBody_Velocity = RigidBody_Accelaration;
		 RigidBody_Position = RigidBody_Accelaration * dt;
	 }
};