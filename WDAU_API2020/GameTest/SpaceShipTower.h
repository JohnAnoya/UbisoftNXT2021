#ifndef SPACESHIPTOWER_H 
#define SPACESHIPTOWER_H 
#include "app\app.h"
#include "Enemy.h"

class SpaceShipTower {
public: 
	SpaceShipTower() {}
	virtual ~SpaceShipTower() {}
	virtual void Update(float deltaTime_) = 0;
	virtual void Render() = 0;
	virtual void OnDestroy() = 0;

	virtual void SetPosition(float x_, float y_) = 0;
	virtual void SetAngle(float newAngle_) = 0;

	virtual void TowerDestroyRemainingBullets() = 0;

	virtual void GetPosition(float& x, float& y) = 0;
	virtual void AttackClosestEnemy(Enemy* enemy_) = 0;
	virtual float GetRange() = 0; 
};
#endif 
