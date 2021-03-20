#include "stdafx.h"
#include "DefaultBullet.h"

DefaultBullet::DefaultBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	bulletSprite->SetPosition(500.0f, 500.0f);
	bulletSprite->SetFrame(3);
	bulletSprite->SetScale(0.75f);

	bulletSpeed = 1.2f; 
	bulletDamage = 5.0f; 
	lifeTime = 15.0f; 
}

DefaultBullet::~DefaultBullet() {
	OnDestroy(); 
}

void DefaultBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_);
}

void DefaultBullet::Render() {
	bulletSprite->Draw(); 
}

void DefaultBullet::OnDestroy() {
	delete bulletSprite;
	bulletSprite = nullptr; 
}

void DefaultBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_); 
}

void DefaultBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

void DefaultBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

float DefaultBullet::GetBulletSpeed() {
	return bulletSpeed;
}

float DefaultBullet::GetBulletLifeTime() {
	return lifeTime;
}

float DefaultBullet::GetBulletDamage() {
	return bulletDamage;
}

