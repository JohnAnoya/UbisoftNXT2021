#ifndef ENEMY_H 
#define ENEMY_H 
#include <algorithm>
#include "app\app.h"
enum //Sprite Animation ENUM
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};

//This is an abstract parent header utilizing Polymorphism!  
class Enemy {
public: 
	Enemy() {} 
	virtual ~Enemy(){}
	virtual void Update(float deltaTime_) = 0; 
	virtual void Render() = 0; 
	virtual void OnDestroy() = 0; 

	virtual void SetPosition(float x_, float y_) = 0;
	virtual void SetEnemyMoveIndex(int newIndex_) = 0;
	virtual void SetEnemyHealth(float newHealth_) = 0;

	virtual void GetPosition(float& x, float& y) = 0;
	virtual int GetEnemyMoveIndex() = 0;
	virtual float GetEnemyHealth() = 0;
	virtual float GetEnemySpeed() = 0;

	virtual int CollectPointsReward() = 0;
};
#endif