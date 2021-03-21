#include "stdafx.h"
#include "DefaultBullet.h"

DefaultBullet::DefaultBullet() : Bullet() {
	bulletSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12); //Creating the BulletSprite
	bulletSprite->SetPosition(500.0f, 500.0f); //Setting Default Position
	bulletSprite->SetFrame(3); //Setting to Frame 3 (in the Ships.bmp picture, goes from 0-23)
	bulletSprite->SetScale(0.75f); //Set Bullet Sprite Scale

	bulletSpeed = 1.5f; //Bullet Speed
	bulletDamage = 10.0f; //Bullet Damage 
	lifeTime = 15.0f; //Bullet LifeTime 
}

DefaultBullet::~DefaultBullet() {
	OnDestroy(); 
}

void DefaultBullet::Update(float deltaTime_) {
	bulletSprite->Update(deltaTime_); //Call Bullet Sprite's Update method 
}

void DefaultBullet::Render() {
	bulletSprite->Draw(); //Call Bullet Sprite's Draw method 
}

void DefaultBullet::OnDestroy() {
	delete bulletSprite; //Delete Bullet Sprite from memory 
	bulletSprite = nullptr; 
}

//Set Bullet Sprite Position 
void DefaultBullet::SetPosition(float x_, float y_) {
	bulletSprite->SetPosition(x_, y_); 
}

//Set Bullet Sprite Angle
void DefaultBullet::SetAngle(float newAngle_) {
	bulletSprite->SetAngle(newAngle_);
}

//Get Bullet Sprite Position 
void DefaultBullet::GetPosition(float& x, float& y) {
	bulletSprite->GetPosition(x, y);
}

//Retrieves BulletSpeed variable 
float DefaultBullet::GetBulletSpeed() {
	return bulletSpeed;
}

//Retrieves Bullet LifeTime variable
float DefaultBullet::GetBulletLifeTime() {
	return lifeTime;
}

//Retrieves BulletDamage variable
float DefaultBullet::GetBulletDamage() {
	return bulletDamage;
}

