#ifndef BULLET_H 
#define BULLET_H 
#include "app\app.h"

class Bullet {
public: 
	Bullet() {}
	virtual ~Bullet() {}
	virtual void Update(float deltaTime_) = 0; 
	virtual void Render() = 0; 
	virtual void OnDestroy() = 0; 

	virtual void SetPosition(float x_, float y_) = 0;
	virtual void SetAngle(float newAngle_) = 0;

	virtual void GetPosition(float& x, float& y) = 0; 
	virtual float GetBulletSpeed() = 0;
	virtual float GetBulletLifeTime() = 0;
	virtual float GetBulletDamage() = 0;
};

#endif 
