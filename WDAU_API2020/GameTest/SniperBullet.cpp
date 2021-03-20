#include "stdafx.h"
#include "SniperBullet.h"

SniperBullet::SniperBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	bulletSprite->SetPosition(500.0f, 500.0f);
	bulletSprite->SetFrame(21);
	bulletSprite->SetScale(1.5f);

	bulletSpeed = 2.5f;
	bulletDamage = 25.0f;
	lifeTime = 25.0f;
}

SniperBullet::~SniperBullet() {
	OnDestroy();
}

void SniperBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_);
}

void SniperBullet::Render() {
	bulletSprite->Draw();
}

void SniperBullet::OnDestroy() {
	delete bulletSprite;
	bulletSprite = nullptr;
}

void SniperBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_);
}

void SniperBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

void SniperBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

float SniperBullet::GetBulletSpeed() {
	return bulletSpeed;
}

float SniperBullet::GetBulletLifeTime() {
	return lifeTime;
}

float SniperBullet::GetBulletDamage() {
	return bulletDamage;
}