#include "stdafx.h"
#include "Dwarf.h"

Dwarf::Dwarf() : Enemy() {
	enemySprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	enemySprite->SetPosition(1000.0f, 100.0f);
	float animationSpeed = 1.0f / 15.0f;
	enemySprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	enemySprite->SetScale(1.3f);

	EnemyMoveIndex = 0; 
	health = 55.0f; 
}

Dwarf::~Dwarf() {
	OnDestroy(); 
}

int Dwarf::GetEnemyMoveIndex() {
	return EnemyMoveIndex;
}

void Dwarf::GetPosition(float& x, float& y) {
	enemySprite->GetPosition(x, y); 
}

void Dwarf::SetEnemyMoveIndex(int newIndex_) {
	EnemyMoveIndex = newIndex_;
}

void Dwarf::SetPosition(float x_, float y_) {
	enemySprite->SetPosition(x_, y_);
}

void Dwarf::Render() {
	enemySprite->Draw(); 
}

void Dwarf::Update(float deltaTime_) {
	enemySprite->Update(deltaTime_);
	enemySprite->SetAnimation(ANIM_LEFT);
}

void Dwarf::OnDestroy() {
	delete enemySprite; 
	enemySprite = nullptr; 
}