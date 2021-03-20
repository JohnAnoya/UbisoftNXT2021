#include "stdafx.h"
#include "BrawlerSpaceShip.h"

BrawlerSpaceShip::BrawlerSpaceShip() : SpaceShipTower() {
	towerSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	towerSprite->SetPosition(100.0f, 100.0f);
	towerSprite->SetFrame(0);
	towerSprite->SetScale(1.0f);
	TowerRange = 150.0f;
	fireRate = 1;
	bulletCurrentLifeTime = 0.0f;
	createNewBulletsTick = 0.0f; 
	defaultShootingWaitTime = 1.0f;
}

BrawlerSpaceShip::~BrawlerSpaceShip() {
	OnDestroy();
}

void BrawlerSpaceShip::Update(float deltaTime_) {
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

void BrawlerSpaceShip::Render() {
	towerSprite->Draw();

	if (!EnemyBullets.empty()) {
		for (auto bullet : EnemyBullets) {
			bullet->Render();
		}
	}
}

void BrawlerSpaceShip::OnDestroy() {
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

void BrawlerSpaceShip::SetPosition(float x_, float y_) {
	towerSprite->SetPosition(x_, y_);
}

void BrawlerSpaceShip::SetAngle(float newAngle_) {
	towerSprite->SetAngle(newAngle_);
}

void BrawlerSpaceShip::GetPosition(float& x, float& y) {
	towerSprite->GetPosition(x, y);
}

float BrawlerSpaceShip::GetRange() {
	return TowerRange;
}

void BrawlerSpaceShip::AttackClosestEnemy(Enemy* enemy_) {
	if (enemy_ != nullptr) {
		if (EnemyBullets.empty() && createNewBulletsTick > defaultShootingWaitTime) {
			int AmountOfBulletsToFire = fireRate;

			for (int i = 0; i < AmountOfBulletsToFire; i++) {
				FastBullet* newBullet = new FastBullet();

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

					std::string bulletCurrentLifeTimeDebug = "\nCurrent Bullet Life Time: " + std::to_string(bulletCurrentLifeTime);
					OutputDebugStringA(bulletCurrentLifeTimeDebug.c_str());

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