#include "stdafx.h"
#include "BasicSpaceShip.h"

BasicSpaceShip::BasicSpaceShip() : SpaceShipTower() {
	towerSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	towerSprite->SetPosition(100.0f, 100.0f);
	towerSprite->SetFrame(2);
	towerSprite->SetScale(1.0f);
	TowerRange = 200.0f; 
}

BasicSpaceShip::~BasicSpaceShip() {
	OnDestroy(); 
}

void BasicSpaceShip::Update(float deltaTime_) {
	towerSprite->Update(deltaTime_);
}

void BasicSpaceShip::Render() {
	towerSprite->Draw();
}

void BasicSpaceShip::OnDestroy() {
	delete towerSprite;
	towerSprite = nullptr; 
}

void BasicSpaceShip::SetPosition(float x_, float y_) {
	towerSprite->SetPosition(x_, y_);
}

void BasicSpaceShip::SetAngle(float newAngle_) {
	towerSprite->SetAngle(newAngle_);
}

void BasicSpaceShip::GetPosition(float& x, float& y) {
	towerSprite->GetPosition(x, y);
}

float BasicSpaceShip::GetRange() {
	return TowerRange;
}

void BasicSpaceShip::GetClosestEnemy(float enemyPosX_, float enemyPosY_) {

}