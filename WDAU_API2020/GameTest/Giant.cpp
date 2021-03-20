#include "stdafx.h"
#include "Giant.h"

Giant::Giant() : Enemy() {
	enemySprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	enemySprite->SetPosition(std::rand() % 1000 + 900, 100.0f);
	float animationSpeed = 1.0f / 15.0f;
	enemySprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	enemySprite->SetScale(2.5f);

	EnemyMoveIndex = 0;
	health = 200.0f;
	speed = 0.75f;

	PointsReward = 500;
}

Giant::~Giant() {
	OnDestroy();
}

int Giant::GetEnemyMoveIndex() {
	return EnemyMoveIndex;
}

void Giant::GetPosition(float& x, float& y) {
	enemySprite->GetPosition(x, y);
}

float Giant::GetEnemyHealth() {
	return health;
}

float Giant::GetEnemySpeed() {
	return speed;
}

int Giant::CollectPointsReward() {
	return PointsReward;
}

void Giant::SetEnemyMoveIndex(int newIndex_) {
	EnemyMoveIndex = newIndex_;
}

void Giant::SetPosition(float x_, float y_) {
	enemySprite->SetPosition(x_, y_);
}

void Giant::SetEnemyHealth(float newHealth_) {
	health = newHealth_;
}

void Giant::Render() {
	enemySprite->Draw();

	float EnemyPosX, EnemyPosY;
	GetPosition(EnemyPosX, EnemyPosY);

	std::string HealthText = "HEALTH: " + std::to_string(std::lroundf(health));
	App::Print(EnemyPosX - (EnemyHealthPrintOffsetX), EnemyPosY + EnemyHealthPrintOffsetY, HealthText.c_str());
}

void Giant::Update(float deltaTime_) {
	enemySprite->Update(deltaTime_);
	enemySprite->SetAnimation(ANIM_LEFT);
}

void Giant::OnDestroy() {
	delete enemySprite;
	enemySprite = nullptr;
}