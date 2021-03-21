//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <stdio.h>
//------------------------------------------------------------------------
#include "app\app.h"
#include "Dwarf.h"
#include "BalancedEnemy.h"
#include "Giant.h"
#include "BasicSpaceShip.h"
#include "BrawlerSpaceShip.h"
#include "SniperSpaceShip.h"

enum class Shop {
	NONE,
	BASICSHIP,
	SNIPERSHIP,
	BRAWLERSHIP,
	HEALTHPOTION
};

enum class GameState {
	NOTPLAYING,
	ISPLAYING,
};

struct ShopPrices {
	int BasicShipPrice; 
	int BrawlerShipPrice;
	int SniperShipPrice; 
	int HealthPotion;
};

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Game Data
//------------------------------------------------------------------------
GameState gameState; 

Dwarf* enemyDwarf;
BalancedEnemy* enemyBalanced; 
Giant* enemyGiant; 

std::vector<Enemy*> enemyList; 
std::vector<SpaceShipTower*> towerList;

std::vector<int> LineNodesSX; 
std::vector<int> LineNodesSY;
std::vector<int> LineNodesEX;
std::vector<int> LineNodesEY;

bool SpawnEnemies; 
float distanceFromNodes;
float distanceFromTowerToEnemy;

int Points; 
Shop shopSelection; 
std::string ShopSelectionText; 
ShopPrices shopPrices; 
bool isInShop; 

int Health;

int Wave;
int NextWavePointReward;  
int MinEnemiesToSpawn; 
int MaxEnemiesToSpawn;

float EnemyHealthIncreaseInterval;
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	gameState = GameState::NOTPLAYING;

	Wave = 0;
	NextWavePointReward = 0;
	MinEnemiesToSpawn = 1;
	MaxEnemiesToSpawn = 10; 
	EnemyHealthIncreaseInterval = 0.0f;

	Points = 1000;
	Health = 500;
	isInShop = false; 
	shopSelection = Shop::NONE;
	ShopSelectionText = "NONE";
	shopPrices.BasicShipPrice = 250;
	shopPrices.SniperShipPrice = 500;
	shopPrices.BrawlerShipPrice = 1000; 
	shopPrices.HealthPotion = 2000;

	LineNodesSX.push_back(1100);
	LineNodesSY.push_back(50);
	LineNodesEX.push_back(750);
	LineNodesEY.push_back(50);

	LineNodesSX.push_back(750);
	LineNodesSY.push_back(50);
	LineNodesEX.push_back(750);
	LineNodesEY.push_back(350);

	LineNodesSX.push_back(750);
	LineNodesSY.push_back(350);
	LineNodesEX.push_back(500);
	LineNodesEY.push_back(350);

	LineNodesSX.push_back(500);
	LineNodesSY.push_back(350);
	LineNodesEX.push_back(500);
	LineNodesEY.push_back(600);

	LineNodesSX.push_back(500);
	LineNodesSY.push_back(600);
	LineNodesEX.push_back(100);
	LineNodesEY.push_back(600);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	switch (gameState) {
	case GameState::NOTPLAYING: {
		if (!enemyList.empty()) {
			for (auto enemy : enemyList) {
				enemy->OnDestroy();
				delete enemy;
				enemy = nullptr;			
			}

			enemyList.clear();
		}

		if (!towerList.empty()) {
			for (auto tower : towerList) {
				tower->OnDestroy();
				delete tower;
				tower = nullptr;
			}

			towerList.clear();
		}

		if (App::IsKeyPressed('P')) {
			gameState = GameState::ISPLAYING;
			Health = 500; 
			Points = 1000; 
			Wave = 0;
			NextWavePointReward = 0;

			MinEnemiesToSpawn = 1;
			MaxEnemiesToSpawn = 10;
			EnemyHealthIncreaseInterval = 0;
		}

		break;
	}

	case GameState::ISPLAYING: {
		if (App::IsKeyPressed('M')) {
			if (!isInShop) {
				isInShop = true;
			}

			else {
				isInShop = false;
			}
		}

		if (App::IsKeyPressed('1') && isInShop) {
			shopSelection = Shop::BASICSHIP;
			ShopSelectionText = "BasicShip";
		}

		else if (App::IsKeyPressed('2') && isInShop) {
			shopSelection = Shop::SNIPERSHIP;
			ShopSelectionText = "SniperShip";
		}

		else if (App::IsKeyPressed('3') && isInShop) {
			shopSelection = Shop::BRAWLERSHIP;
			ShopSelectionText = "BrawlerShip";
		}

		else if (App::IsKeyPressed('4') && isInShop) {
			shopSelection = Shop::HEALTHPOTION;
			ShopSelectionText = "Health Potion";
		}

		if (App::IsKeyPressed(VK_LBUTTON) && isInShop && shopSelection != Shop::NONE) {
			float mousePosx, mousePosy;
			App::GetMousePos(mousePosx, mousePosy);

			switch (shopSelection) {
				case Shop::BASICSHIP: {
					if (Points >= shopPrices.BasicShipPrice) {
						BasicSpaceShip* basicTower = new BasicSpaceShip();
						basicTower->SetPosition(mousePosx, mousePosy);
						towerList.push_back(basicTower);

						Points -= shopPrices.BasicShipPrice;
					}

					break;
				}

				case Shop::SNIPERSHIP: {
					if (Points >= shopPrices.SniperShipPrice) {
						SniperSpaceShip* sniperTower = new SniperSpaceShip();
						sniperTower->SetPosition(mousePosx, mousePosy);
						towerList.push_back(sniperTower);

						Points -= shopPrices.SniperShipPrice;
					}

					break;
				}

				case Shop::BRAWLERSHIP: {
					if (Points >= shopPrices.BrawlerShipPrice) {
						BrawlerSpaceShip* brawlerTower = new BrawlerSpaceShip();
						brawlerTower->SetPosition(mousePosx, mousePosy);
						towerList.push_back(brawlerTower);

						Points -= shopPrices.BrawlerShipPrice;
					}

					break;
				}

				case Shop::HEALTHPOTION: {
					if (Points >= shopPrices.HealthPotion) {
						Points -= shopPrices.HealthPotion;
						Health += 150.0f; 
					}

					break;
				}

				default: {
					break;
				}
			}
		}

		//------------------------------------------------------------------------
		// Sample Sound.
		//------------------------------------------------------------------------
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
		{
			App::PlaySound(".\\TestData\\Test.wav");
		}

		if (!towerList.empty()) {
			for (auto tower : towerList) {
				tower->Update(deltaTime);
			}
		}

		if (!enemyList.empty()) {

			for (auto enemy : enemyList) {
				if (enemy->GetEnemyHealth() <= 0.0f) {
					Points += enemy->CollectPointsReward();
					enemyList.erase(std::remove(enemyList.begin(), enemyList.end(), enemy), enemyList.end());
					enemy->OnDestroy();
					delete enemy;
					enemy = nullptr;
				}

				else {
					enemy->Update(deltaTime);

					float enemyPosX, enemyPosY;
					enemy->GetPosition(enemyPosX, enemyPosY);

					float positionX = LineNodesEX[enemy->GetEnemyMoveIndex()] - enemyPosX;
					float positionY = LineNodesEY[enemy->GetEnemyMoveIndex()] - enemyPosY;
					distanceFromNodes = sqrt(positionX * positionX + positionY * positionY);

					enemy->SetPosition(enemyPosX + positionX / distanceFromNodes * enemy->GetEnemySpeed(), enemyPosY + positionY / distanceFromNodes * enemy->GetEnemySpeed());

					if (distanceFromNodes < 3.0f && enemy->GetEnemyMoveIndex() < 4) {
						enemy->SetEnemyMoveIndex(enemy->GetEnemyMoveIndex() + 1);
					}

					else if (distanceFromNodes < 3.0f && enemy->GetEnemyMoveIndex() == 4) {
						Health -= enemy->GetEnemyHealth();
						if (Health <= 0) {
							gameState = GameState::NOTPLAYING;
						}

						enemyList.erase(std::remove(enemyList.begin(), enemyList.end(), enemy), enemyList.end());
						enemy->OnDestroy();
						delete enemy;
						enemy = nullptr;
					}

					if (enemy != nullptr) {
						if (!towerList.empty()) {
							for (auto tower : towerList) {
								float towerPosX, towerPosY;
								tower->GetPosition(towerPosX, towerPosY);

								float positionXTowerFromEnemy = towerPosX - enemyPosX;
								float positionYTowerFromEnemy = towerPosY - enemyPosY;

								distanceFromTowerToEnemy = sqrt(positionXTowerFromEnemy * positionXTowerFromEnemy
									+ positionYTowerFromEnemy * positionYTowerFromEnemy);

								if (distanceFromTowerToEnemy < tower->GetRange()) {
									float tempSprite1PositionX, tempSprite1PositionY;
									enemy->GetPosition(tempSprite1PositionX, tempSprite1PositionY);

									float tempSprite2PositionX, tempSprite2PositionY;
									tower->GetPosition(tempSprite2PositionX, tempSprite2PositionY);

									double directionX = tempSprite1PositionX - tempSprite2PositionX;
									double directionY = tempSprite1PositionY - tempSprite2PositionY;

									float newAngle = atan2(directionX, directionY);

									tower->SetAngle(-newAngle);
									tower->AttackClosestEnemy(enemy);
								}
							}
						}
					}
				}
			}
		}

		else if (enemyList.empty()) {
			int amountOfEnemiesToSpawn = std::rand() % MaxEnemiesToSpawn + MinEnemiesToSpawn;

			Points += NextWavePointReward;
			Wave += 1;
			NextWavePointReward += 250.0f; 
			MinEnemiesToSpawn += 2;
			MaxEnemiesToSpawn += 4;
			for (int i = 0; i < amountOfEnemiesToSpawn; i++) {
				int EnemyClassToSpawn = std::rand() % 3;
				switch (EnemyClassToSpawn) {
					case 0: {
						enemyDwarf = new Dwarf();
						enemyDwarf->SetEnemyHealth(enemyDwarf->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyList.push_back(enemyDwarf);
						break;
					}

					case 1: {
						enemyBalanced = new BalancedEnemy();
						enemyBalanced ->SetEnemyHealth(enemyBalanced->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyList.push_back(enemyBalanced);
						break;
					}

					case 2: {
						enemyGiant = new Giant();
						enemyGiant->SetEnemyHealth(enemyGiant->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyList.push_back(enemyGiant);
						break;
					}

					default: {
						break;
					}
				}
			}

			EnemyHealthIncreaseInterval += 15.0f;
		}

		break;
	} 
  }
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;

	App::DrawLine(LineNodesSX[0], LineNodesSY[0], LineNodesEX[0], LineNodesEY[0], r, g, b);
	App::DrawLine(LineNodesSX[1], LineNodesSY[1], LineNodesEX[1], LineNodesEY[1], r, g, b);
	App::DrawLine(LineNodesSX[2], LineNodesSY[2], LineNodesEX[2], LineNodesEY[2], r, g, b);
	App::DrawLine(LineNodesSX[3], LineNodesSY[3], LineNodesEX[3], LineNodesEY[3], r, g, b);
	App::DrawLine(LineNodesSX[4], LineNodesSY[4], LineNodesEX[4], LineNodesEY[4], r, g, b);

	if (!towerList.empty()) {
		for (auto tower : towerList) {
			tower->Render(); 
		}
	}

	if (!enemyList.empty()) {
		for (auto enemy : enemyList) {
			enemy->Render();
		}
	}
	//------------------------------------------------------------------------

	if (gameState == GameState::ISPLAYING) {
		if (isInShop) {
			std::string ShopTitle = "SHOP";
			App::Print(700, 750, ShopTitle.c_str(), 0.0f, 1.0f, 0.0f);

			std::string ShopShipInfo1 = "1 - BasicShip (" + std::to_string(shopPrices.BasicShipPrice) + " points)";
			App::Print(700, 730, ShopShipInfo1.c_str());

			std::string ShopShipInfo2 = "2 - SniperShip (" + std::to_string(shopPrices.SniperShipPrice) + " points)";
			App::Print(700, 710, ShopShipInfo2.c_str());

			std::string ShopShipInfo3 = "3 - BrawlerShip (" + std::to_string(shopPrices.BrawlerShipPrice) + " points)";
			App::Print(700, 690, ShopShipInfo3.c_str());

			std::string ShopShipInfo4 = "4 - Health Potion (" + std::to_string(shopPrices.HealthPotion) + " points)";
			App::Print(700, 670, ShopShipInfo4.c_str());

			std::string CurrentlySelected = "Currently Selected: " + ShopSelectionText;
			App::Print(700, 630, CurrentlySelected.c_str());

			std::string UsefulInfoOne = "Use the numbers on your Keyboard to Select";
			App::Print(640, 580, UsefulInfoOne.c_str());

			std::string UsefulInfoTwo = "Left Click to Buy/Place tower or item";
			App::Print(660, 560, UsefulInfoTwo.c_str());
		}

		std::string PointsInfo = "Points: " + std::to_string(Points);
		App::Print(50, 750, PointsInfo.c_str(), r, g, b);

		std::string HealthInfo = "Health: " + std::to_string(Health);
		App::Print(495, 750, HealthInfo.c_str(), r, g, b);

		std::string WaveInfo = "Wave: " + std::to_string(Wave);
		App::Print(500, 730, WaveInfo.c_str(), r, g, b);

		App::Print(50, 200, "M - Shop");
	}

	else if (gameState == GameState::NOTPLAYING) {
		App::Print(100, 120, "P - Play");
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	if (!enemyList.empty()) {
		for (auto enemy : enemyList) {
			delete enemy; 
			enemy = nullptr; 
		}

		enemyList.clear();
	}

	if (!towerList.empty()) {
		for (auto tower : towerList) {
			delete tower; 
			tower = nullptr; 
		}

		towerList.clear();
	}
	//------------------------------------------------------------------------
}