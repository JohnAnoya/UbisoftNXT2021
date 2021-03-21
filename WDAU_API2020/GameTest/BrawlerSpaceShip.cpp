#include "stdafx.h"
#include "BrawlerSpaceShip.h"

/* INITIALIZING VARIABLES */
BrawlerSpaceShip::BrawlerSpaceShip() : SpaceShipTower() {
	towerSprite = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12); //Loading Tower Sprite
	towerSprite->SetPosition(100.0f, 100.0f); //Setting a default position 
	towerSprite->SetFrame(0); //Loading in the BasicSpaceShip using the SetFrame method
	towerSprite->SetScale(1.0f);
	TowerRange = 150.0f;
	fireRate = 1;
	bulletCurrentLifeTime = 0.0f;
	createNewBulletsTick = 0.0f; 
	defaultShootingWaitTime = 1.5f;
}

BrawlerSpaceShip::~BrawlerSpaceShip() {
	OnDestroy();
}

void BrawlerSpaceShip::Update(float deltaTime_) {
	towerSprite->Update(deltaTime_); //Call Tower Sprite's Update method
	createNewBulletsTick += 0.1f;

	if (!EnemyBullets.empty()) {//If the EnemyBullets List is NOT empty
		for (auto bullet : EnemyBullets) { //Loop through all the bullets 
			bullet->Update(deltaTime_); //Call the bullet object's Update method 

			bulletCurrentLifeTime += 0.1f;
			if (bulletCurrentLifeTime >= bullet->GetBulletLifeTime()) { //Deleting the bullet if it surpasses it's lifetime
				EnemyBullets.erase(std::remove(EnemyBullets.begin(), EnemyBullets.end(), bullet), EnemyBullets.end());
				bullet->OnDestroy();
				delete bullet;
				bullet = nullptr;

				bulletCurrentLifeTime = 0.0f; //Resetting Tick variables
				createNewBulletsTick = 0.0f;
			}
		}
	}
}

void BrawlerSpaceShip::Render() {
	towerSprite->Draw(); //Calling Tower Sprite's Draw method 

	if (!EnemyBullets.empty()) { //If EnemyBullets Vector is NOT empty
		for (auto bullet : EnemyBullets) { //I call each individual bullet's render function
			bullet->Render();
		}
	}
}

/*OnDestroy, delete the Tower Sprite and any remaining bullets*/
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

/* This Method gets called in GameTest.cpp when an enemy gets within range of the Tower */
void BrawlerSpaceShip::AttackClosestEnemy(Enemy* enemy_) {
	if (enemy_ != nullptr) {//Making sure the enemy does NOT equal NULL 

		//Ensuring that the EnemyBullets vector is NOT empty and the Tower is firing at a delay based on the Tick variable
		if (EnemyBullets.empty() && createNewBulletsTick > defaultShootingWaitTime) {
			int AmountOfBulletsToFire = fireRate;

			//Depending on the firerate using a for loop to instantiate the bullet objects accordingly 
			for (int i = 0; i < AmountOfBulletsToFire; i++) {
				FastBullet* newBullet = new FastBullet();

				float defaultPositionX, defaultPositionY;
				GetPosition(defaultPositionX, defaultPositionY); //Get the SpaceShip Tower's position; 

				newBullet->SetPosition(defaultPositionX + 50.0f, defaultPositionY); //Give the bullet a default position
				EnemyBullets.push_back(newBullet); //Push the NewBullet object pointer to the vector of Bullet pointers

				bulletCurrentLifeTime = 0.0f; //Reset the Tick variables
				createNewBulletsTick = 0.0f;
			}
		}

		else if (!EnemyBullets.empty()) { //ELSE if the EnemyBullets Vector is NOT empty 
			for (auto bullet : EnemyBullets) {//Loop through each bullet in the EnemyBullets vector 
				bulletCurrentLifeTime += 0.1f; //Increase the LifeTime tick variable

				if (bulletCurrentLifeTime > 0.1f) { //Setting the Bullet's angle & position
					bullet->SetAngle(towerSprite->GetAngle());

					float enemyPosX, enemyPosY;
					enemy_->GetPosition(enemyPosX, enemyPosY);

					float bulletPosX, bulletPosY;
					bullet->GetPosition(bulletPosX, bulletPosY);

					//Getting the Bullet's distance from the Enemy and assigning it's position accordingly 
					float positionXBulletFromEnemy = enemyPosX - bulletPosX;
					float positionYBulletFromEnemy = enemyPosY - bulletPosY;
					float distanceFromEnemy = sqrt(positionXBulletFromEnemy * positionXBulletFromEnemy
						+ positionYBulletFromEnemy * positionYBulletFromEnemy);

					bullet->SetPosition(bulletPosX + positionXBulletFromEnemy / distanceFromEnemy
						* bullet->GetBulletSpeed(), bulletPosY + positionYBulletFromEnemy / distanceFromEnemy
						* bullet->GetBulletSpeed());

					std::string bulletCurrentLifeTimeDebug = "\nCurrent Bullet Life Time: " + std::to_string(bulletCurrentLifeTime);
					OutputDebugStringA(bulletCurrentLifeTimeDebug.c_str());

					//Check if the distance variable reaches it's destination (the enemy)
					if (distanceFromEnemy < 50.0f) { //50 is an arbitrary number I use once the Bullet gets close enough
						//Damage the enemy using the SetHealth method and the Bullet's damage variable
						enemy_->SetEnemyHealth(enemy_->GetEnemyHealth() - bullet->GetBulletDamage());
						App::PlaySound(".\\TestData\\Test.wav");

						//Remove it from the Bullets vector and delete it from memory
						EnemyBullets.erase(std::remove(EnemyBullets.begin(), EnemyBullets.end(), bullet), EnemyBullets.end());
						bullet->OnDestroy();
						delete bullet;
						bullet = nullptr;

						bulletCurrentLifeTime = 0.0f; //Reset Tick variables
						createNewBulletsTick = 0.0f;
					}
				}
			}
		}
	}
}