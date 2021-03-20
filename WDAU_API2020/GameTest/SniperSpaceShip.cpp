#include "stdafx.h"
#include "SniperSpaceShip.h"

SniperSpaceShip::SniperSpaceShip() : SpaceShipTower() {
	towerSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	towerSprite->SetPosition(100.0f, 100.0f);
	towerSprite->SetFrame(20);
	towerSprite->SetScale(0.75f);
	TowerRange = 500.0f;
	fireRate = 1;
	bulletCurrentLifeTime = 0.0f;
	createNewBulletsTick = 0.0f; 
	defaultShootingWaitTime = 30.0f;
}

SniperSpaceShip::~SniperSpaceShip() {
	OnDestroy();
}

void SniperSpaceShip::Update(float deltaTime_) {
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

void SniperSpaceShip::Render() {
	towerSprite->Draw();

	if (!EnemyBullets.empty()) {
		for (auto bullet : EnemyBullets) {
			bullet->Render();
		}
	}
}

void SniperSpaceShip::OnDestroy() {
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

void SniperSpaceShip::SetPosition(float x_, float y_) {
	towerSprite->SetPosition(x_, y_);
}

void SniperSpaceShip::SetAngle(float newAngle_) {
	towerSprite->SetAngle(newAngle_);
}

void SniperSpaceShip::GetPosition(float& x, float& y) {
	towerSprite->GetPosition(x, y);
}

float SniperSpaceShip::GetRange() {
	return TowerRange;
}

void SniperSpaceShip::AttackClosestEnemy(Enemy* enemy_) {
	if (enemy_ != nullptr) {
		std::string bulletCurrentLifeTimeDebug = "\nCurrent New Bullet Tick: " + std::to_string(createNewBulletsTick);
		OutputDebugStringA(bulletCurrentLifeTimeDebug.c_str());
		if (EnemyBullets.empty() && createNewBulletsTick > defaultShootingWaitTime) {
			int AmountOfBulletsToFire = fireRate;

			for (int i = 0; i < AmountOfBulletsToFire; i++) {
				SniperBullet* newBullet = new SniperBullet();

				float defaultPositionX, defaultPositionY;
				GetPosition(defaultPositionX, defaultPositionY); //Get the SpaceShip Tower's position; 

				newBullet->SetPosition(defaultPositionX, defaultPositionY);
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

					if (distanceFromEnemy < 150.0f) {
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