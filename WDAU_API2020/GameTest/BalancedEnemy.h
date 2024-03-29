#ifndef BALANCEDENEMY_H 
#define BALANCEDENEMY_H 
#include "Enemy.h"
#include <cmath>

//Inheriting from the Enemy class 
class BalancedEnemy : public Enemy
{
public:
	BalancedEnemy();
	virtual ~BalancedEnemy();
	void Render() override;
	void Update(float deltaTime_) override;
	void OnDestroy() override;

	void SetPosition(float x_, float y_) override; 
	void SetEnemyMoveIndex(int newIndex_) override;
	void SetEnemyHealth(float newHealth_) override;

	void GetPosition(float& x, float& y) override;
	int GetEnemyMoveIndex() override;
	float GetEnemyHealth() override;
	float GetEnemySpeed() override;

	int CollectPointsReward() override;
private:
	int EnemyMoveIndex;
	int EnemyHealthPrintOffsetX = 25;
	int EnemyHealthPrintOffsetY = 65;
	float health;
	float speed;

	int PointsReward; 

	CSimpleSprite* enemySprite;
};
#endif 

