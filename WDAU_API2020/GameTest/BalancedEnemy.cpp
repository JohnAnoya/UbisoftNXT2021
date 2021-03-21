#include "stdafx.h"
#include "BalancedEnemy.h"

BalancedEnemy::BalancedEnemy() : Enemy() {
	enemySprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	enemySprite->SetPosition(std::rand() % 1000 + 900, 100.0f);
	float animationSpeed = 1.0f / 15.0f;
	enemySprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	enemySprite->SetScale(1.7f);

	EnemyMoveIndex = 0;
	health = 100.0f;
	speed = 1.35f;

	PointsReward = 75;
}

BalancedEnemy::~BalancedEnemy() {
	OnDestroy();
}

int BalancedEnemy::GetEnemyMoveIndex() {
	return EnemyMoveIndex;
}

void BalancedEnemy::GetPosition(float& x, float& y) {
	enemySprite->GetPosition(x, y);
}

float BalancedEnemy::GetEnemyHealth() {
	return health;
}

float BalancedEnemy::GetEnemySpeed() {
	return speed;
}

int BalancedEnemy::CollectPointsReward() {
	return PointsReward;
}

void BalancedEnemy::SetEnemyMoveIndex(int newIndex_) {
	EnemyMoveIndex = newIndex_;
}

void BalancedEnemy::SetPosition(float x_, float y_) {
	enemySprite->SetPosition(x_, y_);
}

void BalancedEnemy::SetEnemyHealth(float newHealth_) {
	health = newHealth_;
}

void BalancedEnemy::Render() {
	enemySprite->Draw();

	float EnemyPosX, EnemyPosY;
	GetPosition(EnemyPosX, EnemyPosY);

	std::string HealthText = "HEALTH: " + std::to_string(std::lroundf(health));
	App::Print(EnemyPosX - (EnemyHealthPrintOffsetX), EnemyPosY + EnemyHealthPrintOffsetY, HealthText.c_str());
}

void BalancedEnemy::Update(float deltaTime_) {
	enemySprite->Update(deltaTime_);
	enemySprite->SetAnimation(ANIM_LEFT);
}

void BalancedEnemy::OnDestroy() {
	delete enemySprite;
	enemySprite = nullptr;
}