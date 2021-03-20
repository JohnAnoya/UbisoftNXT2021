#ifndef BASICSPACESHIP_H 
#define BASICSPACESHIP_H 
#include "SpaceShipTower.h"

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

	void GetPosition(float& x, float& y) override;
	void GetClosestEnemy(float enemyPosX_, float enemyPosY_) override;
	float GetRange() override;
private: 
	CSimpleSprite* towerSprite;
	float TowerRange; 
};
#endif 

