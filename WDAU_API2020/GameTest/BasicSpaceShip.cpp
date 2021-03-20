#include "stdafx.h"
#include "BasicSpaceShip.h"

BasicSpaceShip::BasicSpaceShip() : SpaceShipTower() {
	towerSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	towerSprite->SetPosition(100.0f, 100.0f);
	towerSprite->SetFrame(2);
	towerSprite->SetScale(1.0f);
	TowerRange = 200.0f; 
	fireRate = 3; 
	bulletCurrentLifeTime = 0.0f;
	createNewBulletsTick = 0.0f;
	defaultShootingWaitTime = 5.0f; 
}

BasicSpaceShip::~BasicSpaceShip() {
	OnDestroy(); 
}

void BasicSpaceShip::Update(float deltaTime_) {
	towerSprite->Update(deltaTime_);
	createNewBulletsTick += 0.1f;

	if (!EnemyBullets.empty()) {
		for (auto bullet : EnemyBullets) {
			bullet->Update(deltaTime_);
			
			bulletCurrentLifeTime += 0.1f;
			if (bulletCurrentLifeTime >= bullet->GetBulletLifeTime()) {
				EnemyBullets.erase(std::remove(EnemyBullets.begin(), EnemyBullets.end(), bullet), EnemyBullets.end());
				bullet->OnDestroy();
				delete bullet;
				bullet = nullptr;

				bulletCurrentLifeTime = 0.0f;
				createNewBulletsTick = 0.0f;
			}
		}
	}
}

void BasicSpaceShip::Render() {
	towerSprite->Draw();

	if (!EnemyBullets.empty()) {
		for (auto bullet : EnemyBullets) {
			bullet->Render();
		}
	}
}

void BasicSpaceShip::OnDestroy() {
	delete towerSprite;
	towerSprite = nullptr; 

	if (!EnemyBullets.empty()) {
		for (auto bullet : EnemyBullets) {
			delete bullet; 
			bullet = nullptr; 
		}

		EnemyBullets.clear(); 
	}
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

void BasicSpaceShip::AttackClosestEnemy(Enemy* enemy_) {
	if (enemy_ != nullptr) {
		std::string bulletCurrentLifeTimeDebug = "\nCurrent New Bullet Tick: " + std::to_string(createNewBulletsTick);
		OutputDebugStringA(bulletCurrentLifeTimeDebug.c_str());

		if (EnemyBullets.empty() && createNewBulletsTick > defaultShootingWaitTime) {
			int AmountOfBulletsToFire = std::rand() % fireRate + 1;

			for (int i = 0; i < AmountOfBulletsToFire; i++) {
				DefaultBullet* newBullet = new DefaultBullet();

				float defaultPositionX, defaultPositionY; 
				GetPosition(defaultPositionX, defaultPositionY); //Get the SpaceShip Tower's position; 
				
				newBullet->SetPosition(defaultPositionX + 50.0f, defaultPositionY);
				EnemyBullets.push_back(newBullet);

				bulletCurrentLifeTime = 0.0f;
				createNewBulletsTick = 0.0f; 
			}
		}

		else if (!EnemyBullets.empty()) {
			for (auto bullet : EnemyBullets) {
				bulletCurrentLifeTime += 0.1f;

				if (bulletCurrentLifeTime > 0.1f) {
					bullet->SetAngle(towerSprite->GetAngle());

					float enemyPosX, enemyPosY;
					enemy_->GetPosition(enemyPosX, enemyPosY);

					float bulletPosX, bulletPosY;
					bullet->GetPosition(bulletPosX, bulletPosY);

					float positionXBulletFromEnemy = enemyPosX - bulletPosX;
					float positionYBulletFromEnemy = enemyPosY - bulletPosY;
					float distanceFromEnemy = sqrt(positionXBulletFromEnemy * positionXBulletFromEnemy
						+ positionYBulletFromEnemy * positionYBulletFromEnemy);

					bullet->SetPosition(bulletPosX + positionXBulletFromEnemy / distanceFromEnemy
						* bullet->GetBulletSpeed(), bulletPosY + positionYBulletFromEnemy / distanceFromEnemy
						* bullet->GetBulletSpeed());
					
					if (distanceFromEnemy < 50.0f) {
						enemy_->SetEnemyHealth(enemy_->GetEnemyHealth() - bullet->GetBulletDamage());

						EnemyBullets.erase(std::remove(EnemyBullets.begin(), EnemyBullets.end(), bullet), EnemyBullets.end());
						bullet->OnDestroy();
						delete bullet;
						bullet = nullptr;

						bulletCurrentLifeTime = 0.0f;
						createNewBulletsTick = 0.0f;
					}
				}
			}
		}
	}
}