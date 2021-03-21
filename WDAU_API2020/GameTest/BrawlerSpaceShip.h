#ifndef BRAWLERSPACESHIP_H 
#define BRAWLERSPACESHIP_H 
#include"SpaceShipTower.h"
#include "FastBullet.h"

class BrawlerSpaceShip : public SpaceShipTower
{
public:
	BrawlerSpaceShip();
	virtual ~BrawlerSpaceShip(); 
	void Update(float deltaTime_) override;
	void Render() override;
	void OnDestroy() override;

	void SetPosition(float x_, float y_) override;
	void SetAngle(float newAngle_) override;

	void GetPosition(float& x, float& y) override;
	void AttackClosestEnemy(Enemy* enemy_) override;
	float GetRange() override;
private:
	CSimpleSprite* towerSprite;
	float TowerRange;
	float bulletCurrentLifeTime; //Variable that increases every Update tick to automatically delete any lingering bullets
	float createNewBulletsTick; //Variable that increases every tick that lets us know when we can instantiate more bullets
	float defaultShootingWaitTime; //Variable that determins how long a Tower should wait before shooting another bullet
	int fireRate; //How many bullets this tower can fire at a time

	std::vector<Bullet*> EnemyBullets; /* Vector of Bullet pointer objects that holds all of the Bullet objects that the
	Tower Fires */
};
#endif 
