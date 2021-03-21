#include "stdafx.h"
#include "SniperBullet.h"

SniperBullet::SniperBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12); //Creating the BulletSprite
	bulletSprite->SetPosition(500.0f, 500.0f); //Setting Default Position
	bulletSprite->SetFrame(21); //Setting to Frame 21 (in the Ships.bmp picture, goes from 0-23)
	bulletSprite->SetScale(1.5f); //Set Bullet Sprite Scale

	bulletSpeed = 2.5f;
	bulletDamage = 25.0f;
	lifeTime = 25.0f;
}

SniperBullet::~SniperBullet() {
	OnDestroy();
}

void SniperBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_); //Calling Bullet Sprite's Update method 
}

void SniperBullet::Render() {
	bulletSprite->Draw(); //Calling Bullet Sprite's Draw method 
}

//Deleting Bullet Sprite from memory 
void SniperBullet::OnDestroy() {
	delete bulletSprite;
	bulletSprite = nullptr;
}

//Set Bullet Sprite Position 
void SniperBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_);
}

//Set Bullet Sprite Angle
void SniperBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

//Get Bullet Sprite Position 
void SniperBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

//Returns BulletSpeed variable 
float SniperBullet::GetBulletSpeed() {
	return bulletSpeed;
}

//Returns Bullet LifeTime variable
float SniperBullet::GetBulletLifeTime() {
	return lifeTime;
}

//Returns BulletDamage variable
float SniperBullet::GetBulletDamage() {
	return bulletDamage;
}