#ifndef DWARF_H 
#define DWARF_H 
#include "Enemy.h"
#include <cmath>

class Dwarf : public Enemy
{
public: 
	Dwarf(); 
	virtual ~Dwarf(); 
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
private: 
	int EnemyMoveIndex; 
	int EnemyHealthPrintOffsetX = 25;
	int EnemyHealthPrintOffsetY = 50;
	float health; 
	float speed; 

	CSimpleSprite* enemySprite; 
};
#endif 

