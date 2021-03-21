#include "stdafx.h"
#include "Giant.h"

Giant::Giant() : Enemy() {
	enemySprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4); //Creating the GiantEnemySprite
	enemySprite->SetPosition(std::rand() % 1000 + 900, 100.0f); //Setting a default position
	float animationSpeed = 1.0f / 15.0f; //Initializing an animation speed variable and creating the animation
	enemySprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	enemySprite->SetScale(2.5f); //Default Enemy Sprite Size 

	EnemyMoveIndex = 0; //Default Enemy Move Index (Enemy will always start at Line Index 0!) 
	health = 200.0f; //Default health for a Giant Enemy 
	speed = 0.75f; //Default Speed for a Giant Enemy 

	PointsReward = 150; //The amount of points the user receives when killing the enemy 
}

Giant::~Giant() {
	OnDestroy();
}

//Retrieve the current MoveIndex for the enemy
int Giant::GetEnemyMoveIndex() {
	return EnemyMoveIndex;
}

//Return the Enemy's sprite position 
void Giant::GetPosition(float& x, float& y) {
	enemySprite->GetPosition(x, y);
}

//Return the Enemy's health 
float Giant::GetEnemyHealth() {
	return health;
}

//Return the Enemy's speed 
float Giant::GetEnemySpeed() {
	return speed;
}

//Return PointsReward variable (Gets Called Once Enemy gets killed by Tower)
int Giant::CollectPointsReward() {
	return PointsReward;
}

//EnemyMoveIndex Setter (Used for moving between the different Line Nodes)
void Giant::SetEnemyMoveIndex(int newIndex_) {
	EnemyMoveIndex = newIndex_;
}

//Set Enemy Sprite Position 
void Giant::SetPosition(float x_, float y_) {
	enemySprite->SetPosition(x_, y_);
}

//Set Enemy Health variable
void Giant::SetEnemyHealth(float newHealth_) {
	health = newHealth_;
}

void Giant::Render() {
	enemySprite->Draw(); //Call Enemy Sprite's Draw Method 

	float EnemyPosX, EnemyPosY; //Get the Enemy's position 
	GetPosition(EnemyPosX, EnemyPosY);

	//Create User Interface that displayed the Enemy's health using the Print Method provided with the API 
	std::string HealthText = "HEALTH: " + std::to_string(std::lroundf(health));
	App::Print(EnemyPosX - (EnemyHealthPrintOffsetX), EnemyPosY + EnemyHealthPrintOffsetY, HealthText.c_str());
}

void Giant::Update(float deltaTime_) {
	enemySprite->Update(deltaTime_); //Call the enemy sprite's update method 
	enemySprite->SetAnimation(ANIM_LEFT); //Set the enemy sprite's animation ID
}

void Giant::OnDestroy() { //OnDestroy delete the EnemySprite pointer object from memory 
	delete enemySprite;
	enemySprite = nullptr;
}