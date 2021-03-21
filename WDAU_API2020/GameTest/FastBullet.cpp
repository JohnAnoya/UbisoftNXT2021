#include "stdafx.h"
#include "FastBullet.h"

FastBullet::FastBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12); //Creating the BulletSprite
	bulletSprite->SetPosition(500.0f, 500.0f); //Setting Default Position
	bulletSprite->SetFrame(11); //Setting to Frame 11 (in the Ships.bmp picture, goes from 0-23)
	bulletSprite->SetScale(0.5f); //Set Bullet Sprite Scale

	bulletSpeed = 1.0f;
	bulletDamage = 5.0f;
	lifeTime = 10.0f;
}

FastBullet::~FastBullet() {
	OnDestroy();
}

void FastBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_); //Calling Bullet Sprite's Update method 
}

void FastBullet::Render() {
	bulletSprite->Draw(); //Calling Bullet Sprite's Draw method 
}

//Deleting Bullet Sprite from memory 
void FastBullet::OnDestroy() {
	delete bulletSprite;
	bulletSprite = nullptr;
}

//Set Bullet Sprite Position 
void FastBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_);
}

//Set Bullet Sprite Angle
void FastBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

//Get Bullet Sprite Position 
void FastBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

//Returns BulletSpeed variable 
float FastBullet::GetBulletSpeed() {
	return bulletSpeed;
}

//Returns Bullet LifeTime variable
float FastBullet::GetBulletLifeTime() {
	return lifeTime;
}

//Returns BulletDamage variable
float FastBullet::GetBulletDamage() {
	return bulletDamage;
}