#ifndef DEFAULTBULLET_H 
#define DEFAULTBULLET_H 
#include "Bullet.h"

class DefaultBullet : public Bullet
{
public: 
	DefaultBullet();
	virtual ~DefaultBullet();

	void Update(float deltaTime_) override;
	void Render() override;
	void OnDestroy() override;

	void SetPosition(float x_, float y_) override;
	void SetAngle(float newAngle_) override;

	void GetPosition(float& x, float& y) override;

	float GetBulletSpeed() override;
	float GetBulletLifeTime() override;
	float GetBulletDamage() override;
private: 
	CSimpleSprite* bulletSprite;
	float bulletSpeed; 
	float bulletDamage;
	float lifeTime;
};
#endif 
