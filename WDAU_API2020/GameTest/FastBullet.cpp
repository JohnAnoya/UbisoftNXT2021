#include "stdafx.h"
#include "FastBullet.h"

FastBullet::FastBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	bulletSprite->SetPosition(500.0f, 500.0f);
	bulletSprite->SetFrame(11);
	bulletSprite->SetScale(0.5f);

	bulletSpeed = 2.5f;
	bulletDamage = 2.0f;
	lifeTime = 10.0f;
}

FastBullet::~FastBullet() {
	OnDestroy();
}

void FastBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_);
}

void FastBullet::Render() {
	bulletSprite->Draw();
}

void FastBullet::OnDestroy() {
	delete bulletSprite;
	bulletSprite = nullptr;
}

void FastBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_);
}

void FastBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

void FastBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

float FastBullet::GetBulletSpeed() {
	return bulletSpeed;
}

float FastBullet::GetBulletLifeTime() {
	return lifeTime;
}

float FastBullet::GetBulletDamage() {
	return bulletDamage;
}