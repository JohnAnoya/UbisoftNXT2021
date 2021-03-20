#ifndef BASICSPACESHIP_H 
#define BASICSPACESHIP_H 
#include "SpaceShipTower.h"
#include "DefaultBullet.h"

class BasicSpaceShip : public SpaceShipTower
{
public: 
	BasicSpaceShip();
	virtual ~BasicSpaceShip();
	void Update(float deltaTime_) override;
	void Render() override;
	void OnDestroy() override;
	
	void SetPosition(float x_, float y_) override;
	void SetAngle(float newAngle_) override;

	void TowerDestroyRemainingBullets() override;

	void GetPosition(float& x, float& y) override;
	void AttackClosestEnemy(Enemy* enemy_) override;
	float GetRange() override;
private: 
	CSimpleSprite* towerSprite;
	float TowerRange; 
	float bulletCurrentLifeTime;
	float createNewBulletsTick; 
	float defaultShootingWaitTime;
	int fireRate; 
	bool isShooting; 
	
	std::vector<Bullet*> EnemyBullets; 
};
#endif 

