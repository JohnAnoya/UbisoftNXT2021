//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <stdio.h>
/*-------------------------USER CREATED HEADER FILES-------------------------------*/
#include "app\app.h"
#include "Dwarf.h"
#include "BalancedEnemy.h"
#include "Giant.h"
#include "BasicSpaceShip.h"
#include "BrawlerSpaceShip.h"
#include "SniperSpaceShip.h"
/*-------------------------USER CREATED HEADER FILES-------------------------------*/

/*-------------------------SHOP ENUM CLASS FOR PURCHASING TOWERS/ITEMS-------------------------------*/
enum class Shop {
	NONE, //NONE ENUM - No item/tower selected as a default value 
	BASICSHIP, //BASICSHIP ENUM - Referencing the Polymorphic child class of the abstract parent class (SpaceShipTower.h) 
	SNIPERSHIP, //SNIPERSHIP ENUM - Referencing the Polymorphic child class of the abstract parent class (SpaceShipTower.h)
	BRAWLERSHIP, //BRAWLERSHIP ENUM - Referencing the Polymorphic child class of the abstract parent class (SpaceShipTower.h)
	HEALTHPOTION //HEALTHPOTION ENUM - Health Potion ENUM that the player can purchase for additional health
};


/*-------------------------SHOP PRICES ENUM (Used in coherence with the Shop Enum Class)-------------------------------*/
struct ShopPrices {
	int BasicShipPrice; //Price for buying a BasicShip Tower (Referencing: BasicShip.cpp/h)
	int SniperShipPrice; //Price for buying a SniperShip Tower (Referencing: SniperShip.cpp/h)
	int BrawlerShipPrice; //Price for buying a BrawlerShip Tower (Referencing: BrawlerShip.cpp/h)
	int HealthPotion; //Price for buying a Health Potion to increase health
};

/*-------------------------GAME STATE ENUM CLASS FOR SWITCHING BETWEEN GAME STATES-------------------------------*/
enum class GameState {
	NOTPLAYING, //NOTPLAYING ENUM - Player is currently NOT playing the Tower Defense Game 
	ISPLAYING, //ISPLAYING ENUM - Player is currently playing the Tower Defense Game
};

/*------------------------------------------------------------------------*/
/*                              GAME DATA                                */
/*----------------------------------------------------------------------*/
GameState gameState; //GameState enum class object to be able to switch between statees 

Dwarf* enemyDwarf; //Pointer Object of type enemy Dwarf (child class of Enemy.h)
BalancedEnemy* enemyBalanced; //Pointer Object of type enemy Balanced (child class of Enemy.h)
Giant* enemyGiant; //Pointer Object of type enemy Giant (child class of Enemy.h)

std::vector<Enemy*> enemyList; //Vector list of Enemy pointer objects containing all the enemies within the scene
std::vector<SpaceShipTower*> towerList; //Vector list of Tower pointer objects containing all the enemies within the scene

/* Vectors of integers used for drawing lines (e.g. App::DrawLine(sx, sy, ex, ey)) */
std::vector<int> LineNodesSX; //Contains all of the SX integers for drawing lines
std::vector<int> LineNodesSY; //Contains all of the SY integers for drawing lines
std::vector<int> LineNodesEX; //Contains all of the EX integers for drawing lines
std::vector<int> LineNodesEY; //Contains all of the EY integers for drawing lines

//The distance from the enemies to the Line Nodes above
float distanceFromNodes; //Used for checking if an enemy is close to the currentNode (If so, proceed to the next node)
float distanceFromTowerToEnemy; //Used for checking if an enemy is close to a tower

int Points; //Total Points user has
Shop shopSelection; //Shop Selection enum class object for determining what objects in the shop is being selected
std::string ShopSelectionText; //Shop Selection Text used to show the user what they currently have selected
ShopPrices shopPrices; //Shop Prices enum object used to declare prices for objects;
bool isInShop; //isInShop Boolean check to see if the User is currently browsing the Shop

int Health; //Health variable representing the user's health (NOT related to enemy health)

int Wave; //Current wave in the Tower Defense Game
int NextWavePointReward; //Wave Reward Interval (User gets a certain amount of points after each wave) 
int MaxEnemiesToSpawn; //Amount of enemies to spawn per wave (this integer increases every wave)
//I use both of these variables alongside std::rand() to choose a rough estimate of how many enemies to spawn

float EnemyHealthIncreaseInterval; //variable 
/*------------------------------------------------------------------------*/
/*                              GAME DATA                                */
/*----------------------------------------------------------------------*/


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/*INITIALIZING ALL OF THE VARIABLES DECLARED ABOVE*/
	gameState = GameState::NOTPLAYING; //Initializing gameState Object
	Wave = 0; 
	NextWavePointReward = 0;
	MaxEnemiesToSpawn = 2; 
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

	/*Initializing FIRST Line To Draw*/
	LineNodesSX.push_back(650);
	LineNodesSY.push_back(0);
	LineNodesEX.push_back(950);
	LineNodesEY.push_back(100);

	/*Initializing SECOND Line To Draw*/
	LineNodesSX.push_back(950);
	LineNodesSY.push_back(100);
	LineNodesEX.push_back(500);
	LineNodesEY.push_back(750);

	/*Initializing THIRD Line To Draw*/
	LineNodesSX.push_back(500);
	LineNodesSY.push_back(750);
	LineNodesEX.push_back(50);
	LineNodesEY.push_back(100);

	/*Initializing FOURTH Line To Draw*/
	LineNodesSX.push_back(50);
	LineNodesSY.push_back(100);
	LineNodesEX.push_back(350);
	LineNodesEY.push_back(0);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//Switch Case Statement to determine what Game State the user is in
	switch (gameState) {
	case GameState::NOTPLAYING: { //If the user is not Playing
		if (!enemyList.empty()) { //Loop through the EnemyList Vector and destroy any previous lingering enemies
			for (auto enemy : enemyList) {
				enemy->OnDestroy(); //Call the OnDestroy method which deletes the sprite
				delete enemy; //Free it from memory 
				enemy = nullptr;			
			}

			enemyList.clear();
		}

		//Loop through the TowerList Vector and destroy any previously remaining Towers from last game
		if (!towerList.empty()) { 
			for (auto tower : towerList) {
				tower->OnDestroy(); //Call the OnDestroy method which deletes the sprite
				delete tower; //Free it from memory 
				tower = nullptr;
			}

			towerList.clear();
		}

		//If the user presses P on their keyboard while in this state, switch the state to ISPLAYING
		if (App::IsKeyPressed('P')) {
			gameState = GameState::ISPLAYING;

			/*Resetting these variable values that may have been changed in a previous game*/
			Health = 500; 
			Points = 1000; 
			Wave = 0;
			NextWavePointReward = 0;

			MaxEnemiesToSpawn = 2;
			EnemyHealthIncreaseInterval = 0;
			/*Resetting these variable values that may have been changed in a previous game*/
		}

		break; //Break from the switch case 
	}

	//OTHERWISE if the player is in the ISPLAYING state, begin the gameplay loop 
	case GameState::ISPLAYING: {
		if (App::IsKeyPressed('M')) { //If the user presses the "M" key modify the isInShop bool to true or false
			if (!isInShop) {
				isInShop = true; //Open Shop
			}

			else {
				isInShop = false; //Close shop
			}
		}

		/* SHOP TOWER/ITEM SELECTION KEYBINDS */
		if (App::IsKeyPressed('1') && isInShop) { //If the user presses 1 on the keyboard, select the BASICSHIP
			shopSelection = Shop::BASICSHIP;
			ShopSelectionText = "BasicShip";
		}

		else if (App::IsKeyPressed('2') && isInShop) { //If the user presses 2 on the keyboard, select the SNIPERSHIP
			shopSelection = Shop::SNIPERSHIP;
			ShopSelectionText = "SniperShip";
		}

		else if (App::IsKeyPressed('3') && isInShop) { //If the user presses 3 on the keyboard, select the BRAWLERSHIP
			shopSelection = Shop::BRAWLERSHIP;
			ShopSelectionText = "BrawlerShip";
		}

		else if (App::IsKeyPressed('4') && isInShop) { //If the user presses 4 on the keyboard, select the HEALTHPOTION
			shopSelection = Shop::HEALTHPOTION;
			ShopSelectionText = "Health Potion";
		}

		//If the player left clicks and they have an item in the shop selected (hence the shopSelection != Shop::NONE)
		if (App::IsKeyPressed(VK_LBUTTON) && isInShop && shopSelection != Shop::NONE) {
			float mousePosx, mousePosy; //Retrieve the mouse position 
			App::GetMousePos(mousePosx, mousePosy); 

			//Another switch case to make purchases depending on what the User has selected
			switch (shopSelection) {
				case Shop::BASICSHIP: { //If BasicShip is selected and the user has enough points
					if (Points >= shopPrices.BasicShipPrice) { //Using the shopPrices object enum created above
						BasicSpaceShip* basicTower = new BasicSpaceShip(); //Instantiate a new BasicSpaceShip object
						basicTower->SetPosition(mousePosx, mousePosy); //Set the position equal to the user's mouse POS
						towerList.push_back(basicTower); //Add the tower object to the TowerList vector

						Points -= shopPrices.BasicShipPrice; //Deduct the appropriate amount from the user's total points
					}

					break; //break from the switch case
				}

				case Shop::SNIPERSHIP: { //If SniperShip is selected and the user has enough points
					if (Points >= shopPrices.SniperShipPrice) { //Using the shopPrices object enum created above
						SniperSpaceShip* sniperTower = new SniperSpaceShip(); //Instantiate a new SniperSpaceShip object
						sniperTower->SetPosition(mousePosx, mousePosy); //Set the position equal to the user's mouse POS
						towerList.push_back(sniperTower); //Add the tower object to the TowerList vector

						Points -= shopPrices.SniperShipPrice; //Deduct the appropriate amount from the user's total points
					}

					break; 
				}

				case Shop::BRAWLERSHIP: { //If BrawlerShip is selected and the user has enough points
					if (Points >= shopPrices.BrawlerShipPrice) { //Using the shopPrices object enum created above
						BrawlerSpaceShip* brawlerTower = new BrawlerSpaceShip(); //Instantiate a new BrawlerSpaceShip object
						brawlerTower->SetPosition(mousePosx, mousePosy); //Set the position equal to the user's mouse POS
						towerList.push_back(brawlerTower); //Add the tower object to the TowerList vector

						Points -= shopPrices.BrawlerShipPrice;//Deduct the appropriate amount from the user's total points
					}

					break;
				}

				case Shop::HEALTHPOTION: { //If HealthPotion is selected and the user has enough points
					if (Points >= shopPrices.HealthPotion) { //Using the shopPrices object enum created above
						Points -= shopPrices.HealthPotion; //Deduct the appropriate amount from the user's total points
						Health += 150.0f; //Increase the user's health 
					}

					break;
				}

				default: {
					break;
				}
			}
		}		

		if (!towerList.empty()) { //If the TowerList vector is not empty 
			for (auto tower : towerList) { //Loop through the vector
				tower->Update(deltaTime); //Call the tower object's Update method (making sure the tower is being update)
			}
		}

		if (!enemyList.empty()) { //Otherwise If the EnemyList vector is not empty
			for (auto enemy : enemyList) {//Loop through the vector 
				if (enemy->GetEnemyHealth() <= 0.0f) {//Check if the enemy has been killed
					Points += enemy->CollectPointsReward(); //If so, collect the points associated with killing the enemy
					enemyList.erase(std::remove(enemyList.begin(), enemyList.end(), enemy), enemyList.end());
					enemy->OnDestroy();//Delete it from the vector, and free it from memory 
					delete enemy;
					enemy = nullptr;
				}

				else {//If the enemy is NOT dead 
					enemy->Update(deltaTime); //Call its Update Method

					float enemyPosX, enemyPosY;//Retrieve its Position 
					enemy->GetPosition(enemyPosX, enemyPosY);

					/*ASSIGN THE ENEMY POSITION USING THE CURRENT LINE NODE POSITION SUBTRACTED BY ITS OWN POSITION*/
					//The GetEnemyModeIndex will allow the enemy to traverse to each Line Node
					//Using LineNodesEX and LineNodesEY vectors only because they consist of the line's end positions
					float positionX = LineNodesEX[enemy->GetEnemyMoveIndex()] - enemyPosX; 
					float positionY = LineNodesEY[enemy->GetEnemyMoveIndex()] - enemyPosY;
					distanceFromNodes = sqrt(positionX * positionX + positionY * positionY);//Get the distance from the Nodes

					//Set the enemy position using the variables above alongside the Enemy Speed
					enemy->SetPosition(enemyPosX + positionX / distanceFromNodes * enemy->GetEnemySpeed(), enemyPosY + positionY / distanceFromNodes * enemy->GetEnemySpeed());

					//Once the enemy reaches the end point of the current node increase the index 
					//Doing this will allow the enemy to progress to the next line node
					if (distanceFromNodes < 3.0f && enemy->GetEnemyMoveIndex() < 3) {
						enemy->SetEnemyMoveIndex(enemy->GetEnemyMoveIndex() + 1);
					}

					//Otherwise if the enemy reaches the end without dying
					else if (distanceFromNodes < 3.0f && enemy->GetEnemyMoveIndex() == 3) {
						Health -= enemy->GetEnemyHealth(); //Subtract from the user's health with the enemy's remaining health
						if (Health <= 0) { //If the user's health <= 0 then they lost 
							gameState = GameState::NOTPLAYING; //switch the game state to NOTPLAYING
						}

						//Delete the enemy from the vector/memory since they reached the end
						enemyList.erase(std::remove(enemyList.begin(), enemyList.end(), enemy), enemyList.end());
						enemy->OnDestroy();
						delete enemy;
						enemy = nullptr;
					}

					if (enemy != nullptr) { //If the enemy object does not equal NULL 
						if (!towerList.empty()) { //and the TowerList is not empty 
							for (auto tower : towerList) {//Looping through the TowerList
								float towerPosX, towerPosY;
								tower->GetPosition(towerPosX, towerPosY);//Retrieve the tower object's position

								//Getting the position from the Tower object to the enemy object
								float positionXTowerFromEnemy = towerPosX - enemyPosX;
								float positionYTowerFromEnemy = towerPosY - enemyPosY;

								//Retrieving the distance 
								distanceFromTowerToEnemy = sqrt(positionXTowerFromEnemy * positionXTowerFromEnemy
									+ positionYTowerFromEnemy * positionYTowerFromEnemy);

								//If the enemy is within the Tower's Range 
								//Rotate the Tower based on the little bit of trignometry done below
								if (distanceFromTowerToEnemy < tower->GetRange()) {
									float tempSprite1PositionX, tempSprite1PositionY;
									enemy->GetPosition(tempSprite1PositionX, tempSprite1PositionY);

									float tempSprite2PositionX, tempSprite2PositionY;
									tower->GetPosition(tempSprite2PositionX, tempSprite2PositionY);

									double directionX = tempSprite1PositionX - tempSprite2PositionX;
									double directionY = tempSprite1PositionY - tempSprite2PositionY;

									float newAngle = atan2(directionX, directionY);

									tower->SetAngle(-newAngle); //Set the Tower object's new rotation
									tower->AttackClosestEnemy(enemy); //Attack the enemy 
								}
							}
						}
					}
				}
			}
		}

		//ELSE if the EnemyList is empty, use std::rand() to instantiate a set of enemies between the Min/Max variables 
		else if (enemyList.empty()) {
			int amountOfEnemiesToSpawn = MaxEnemiesToSpawn;
			
			Points += NextWavePointReward; //Increase the Player's points after completing a wave
			Wave += 1; //Increase the wave
			NextWavePointReward += 250.0f; //Reward variable increased (given to the Player after the end of each wave)
			MaxEnemiesToSpawn += 2; //Increase the MaxEnemiesToSpawn variable so more & more enemies spawn later on
			for (int i = 0; i < amountOfEnemiesToSpawn; i++) {//For Loop to create as many enemies as the variable chose
				int EnemyClassToSpawn = std::rand() % 3; //int Variable that picks a number from (0-2)

				//This done to 'Randomize' which type of enemy to spawn
				//I put randomize is quotations because std::rand is not truly random 
				//(a pseudonumber generator would be more ideal)
				//Switch Case dependant on what the variable above chose to spawn in
				switch (EnemyClassToSpawn) { 
					case 0: { //If the EnemyClassToSpawn Variable equals 0, Spawn a Dwarf Enemy
						enemyDwarf = new Dwarf();
						//Set the EnemyHealth in addition with the HealthIncreaseInterval(enemy health increases per wave)
						enemyDwarf->SetEnemyHealth(enemyDwarf->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyDwarf->SetPosition(rand() % (LineNodesSX[0] - (LineNodesSX[0] - 150) + 1)
							+ (LineNodesSX[0] - 150), LineNodesSY[0]);
						enemyList.push_back(enemyDwarf); //Push the enemy object into the EnemyList vector 
						break;
					}

					case 1: { //If the EnemyClassToSpawn Variable equals 1, Spawn a Balanced Enemy
						enemyBalanced = new BalancedEnemy();
						//Set the EnemyHealth in addition with the HealthIncreaseInterval(enemy health increases per wave)
						enemyBalanced->SetEnemyHealth(enemyBalanced->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyBalanced->SetPosition(rand() % (LineNodesSX[0] - (LineNodesSX[0] - 150) + 1) 
							+ (LineNodesSX[0] - 150), LineNodesSY[0]); //'Randomize' the position so the enemies don't spawn on top of eachother! 
						enemyList.push_back(enemyBalanced); //Push the enemy object into the EnemyList vector 
						break;
					}

					case 2: { //If the EnemyClassToSpawn Variable equals 2, Spawn a Giant Enemy
						enemyGiant = new Giant();
						//Set the EnemyHealth in addition with the HealthIncreaseInterval(enemy health increases per wave)
						enemyGiant->SetEnemyHealth(enemyGiant->GetEnemyHealth() + EnemyHealthIncreaseInterval);
						enemyGiant->SetPosition(rand() % (LineNodesSX[0] - (LineNodesSX[0] - 150) + 1)
							+ (LineNodesSX[0] - 150), LineNodesSY[0]);
						enemyList.push_back(enemyGiant); //Push the enemy object into the EnemyList vector 
						break;
					}

					default: {
						break;
					}
				}
			}

			EnemyHealthIncreaseInterval += 10.0f; //Increase the EnemyHealthIncreaseInterval AFTER the wave
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

	/* MANUALLY DRAWING MY LINES */
	/*Preferably I would have liked to use a for loop, but I wasn't able to get the results I wanted 
	 with a single DrawLine call (e.g. it would connect all the lines together and make a giant mess)*/
	App::DrawLine(LineNodesSX[0], LineNodesSY[0], LineNodesEX[0], LineNodesEY[0], r, g, b);
	App::DrawLine(LineNodesSX[1], LineNodesSY[1], LineNodesEX[1], LineNodesEY[1], r, g, b);
	App::DrawLine(LineNodesSX[2], LineNodesSY[2], LineNodesEX[2], LineNodesEY[2], r, g, b);
	App::DrawLine(LineNodesSX[3], LineNodesSY[3], LineNodesEX[3], LineNodesEY[3], r, g, b);
	//Maybe a nested for loop instead...? oh well :C

	//If the TowerList Vector is NOT empty 
	if (!towerList.empty()) {
		for (auto tower : towerList) {//Loop through the TowerList vector 
			tower->Render(); //Call each individual tower object's render method 
		}
	}

	//If the EnemyList Vector is NOT empty 
	if (!enemyList.empty()) {
		for (auto enemy : enemyList) {//Loop through the EnemyList vector
			enemy->Render(); //Call each individual enemy object's render method 
		}
	}
	
	/* USER INTERFACE PRINTING */
	if (gameState == GameState::ISPLAYING) { //If the User is in a ISPLAYING game state
		if (isInShop) { //and is in the shop ... show the game's User Interface
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

	//Otherwise if the user is in a NOTPLAYING game state, only show the P - Play User Interface 
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
	//Looping through the EnemyList/TowerList to ensure everything is being deleted from memory!
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
}