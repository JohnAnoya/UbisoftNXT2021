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
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
Dwarf* enemyDwarf;
BalancedEnemy* enemyBalanced; 
Giant* enemyGiant; 

std::vector<Enemy*> enemyList; 
std::vector<SpaceShipTower*> towerList;

bool InEditorMode, hasNodePoint1, hasNodePoint2, CanDrawLine;
std::vector<int> LineNodesSX; 
std::vector<int> LineNodesSY;
std::vector<int> LineNodesEX;
std::vector<int> LineNodesEY;

bool SpawnEnemies; 
float distanceFromNodes;
float distanceFromTowerToEnemy;
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	InEditorMode = false; 
	CanDrawLine = false;
	hasNodePoint1 = false; 
	hasNodePoint2 = false; 

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
	if (App::IsKeyPressed('E')) {
		if (!InEditorMode) {
			InEditorMode = true;
		}

		else {
			InEditorMode = false; 
		}
	}

	if (App::IsKeyPressed(VK_LBUTTON) && InEditorMode) {
		float mousePosx, mousePosy;
		App::GetMousePos(mousePosx, mousePosy);

		BrawlerSpaceShip* newTower = new BrawlerSpaceShip(); 
		newTower->SetPosition(mousePosx, mousePosy);

		towerList.push_back(newTower);
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
					OutputDebugStringA("\nEnemy is at the end!");
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
		int amountOfEnemiesToSpawn = std::rand() % 10 + 1;
		for (int i = 0; i < amountOfEnemiesToSpawn; i++) {
			int EnemyClassToSpawn = std::rand() % 3; 
			switch (EnemyClassToSpawn) {
				default: {
					break;
				}

				case 0: {
					enemyDwarf = new Dwarf();
					enemyList.push_back(enemyDwarf);
					break;
				}

				case 1: {
					 enemyBalanced = new BalancedEnemy();
					enemyList.push_back(enemyBalanced);
					break;
				}

				case 2: {
					enemyGiant = new Giant();
					enemyList.push_back(enemyGiant);
					break;
				}
			}

			std::string amountOfSpawnedEnemies = "Spawning " + std::to_string(amountOfEnemiesToSpawn) + " Enemies" + " \nOf Class:" + std::to_string(EnemyClassToSpawn);
			OutputDebugStringA(amountOfSpawnedEnemies.c_str());
		}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;

	/*
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}
	*/
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

	std::string distanceDebugging = "Distance = " + std::to_string(distanceFromNodes);
	App::Print(0, 350, distanceDebugging.c_str());
	App::Print(100, 100, "E - Editor Mode");

	std::string distanceDebugging2 = "Tower To Enemy Distance = " + std::to_string(distanceFromTowerToEnemy);
	App::Print(0, 500, distanceDebugging2.c_str());


	float x, y;
	App::GetMousePos(x, y);
	std::string MousePos = "Mouse Position " + std::to_string(x) + ", " + std::to_string(y);
	App::Print(0, 0, MousePos.c_str());

	if (InEditorMode) {
		App::Print(650, 100, "Note: Left Click to add the first Node point!");
		App::Print(650,  50, "Right Click to add the second Node point!");
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