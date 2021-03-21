#include "stdafx.h"
#include "BalancedEnemy.h"

/*INITIALIZING VARIABLES*/
BalancedEnemy::BalancedEnemy() : Enemy() {
	enemySprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4); //Creating the BalancedEnemySprite
	enemySprite->SetPosition(0.0f, 0.0f); //Setting a default position 
	float animationSpeed = 1.0f / 15.0f; //Initializing an animation speed variable and creating the animation
	enemySprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	enemySprite->SetScale(1.7f); //Default Enemy Sprite Size 

	EnemyMoveIndex = 0; //Default Enemy Move Index (Enemy will always start at Line Index 0!) 
	health = 100.0f; //Default health for a Balanced Enemy 
	speed = 1.35f; //Default Speed for a Balanced Enemy 

	PointsReward = 75; //The amount of points the user receives when killing the enemy 
}

BalancedEnemy::~BalancedEnemy() {
	OnDestroy(); 
}

//Retrieve the current MoveIndex for the enemy
int BalancedEnemy::GetEnemyMoveIndex() {
	return EnemyMoveIndex;
}

//Return the Enemy's sprite position 
void BalancedEnemy::GetPosition(float& x, float& y) {
	enemySprite->GetPosition(x, y);
}

//Return the Enemy's health 
float BalancedEnemy::GetEnemyHealth() {
	return health;
}

//Return the Enemy's speed 
float BalancedEnemy::GetEnemySpeed() {
	return speed;
}

//Return PointsReward variable (Gets Called Once Enemy gets killed by Tower)
int BalancedEnemy::CollectPointsReward() {
	return PointsReward;
}

//EnemyMoveIndex Setter (Used for moving between the different Line Nodes)
void BalancedEnemy::SetEnemyMoveIndex(int newIndex_) {
	EnemyMoveIndex = newIndex_;
}

//Set Enemy Sprite Position 
void BalancedEnemy::SetPosition(float x_, float y_) {
	enemySprite->SetPosition(x_, y_);
}

//Set Enemy Health variable
void BalancedEnemy::SetEnemyHealth(float newHealth_) {
	health = newHealth_;
}

void BalancedEnemy::Render() {
	enemySprite->Draw(); //Call Enemy Sprite's Draw Method 

	float EnemyPosX, EnemyPosY; //Get the Enemy's position 
	GetPosition(EnemyPosX, EnemyPosY);

	//Create User Interface that displayed the Enemy's health using the Print Method provided with the API 
	std::string HealthText = "HEALTH: " + std::to_string(std::lroundf(health));
	App::Print(EnemyPosX - (EnemyHealthPrintOffsetX), EnemyPosY + EnemyHealthPrintOffsetY, HealthText.c_str());
}

void BalancedEnemy::Update(float deltaTime_) {
	enemySprite->Update(deltaTime_); //Call the enemy sprite's update method 
	enemySprite->SetAnimation(ANIM_LEFT); //Set the enemy sprite's animation ID
}


void BalancedEnemy::OnDestroy() {//OnDestroy delete the EnemySprite pointer object from memory 
	delete enemySprite;
	enemySprite = nullptr;
}