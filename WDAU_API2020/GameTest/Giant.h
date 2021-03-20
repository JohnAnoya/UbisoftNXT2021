#ifndef GIANT_H 
#define GIANT_H 
#include "Enemy.h"
#include <cmath>

class Giant : public Enemy
{
public:
	Giant();
	virtual ~Giant();
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
	int EnemyHealthPrintOffsetY = 100;
	float health;
	float speed;

	int PointsReward;

	CSimpleSprite* enemySprite;
};
#endif 

