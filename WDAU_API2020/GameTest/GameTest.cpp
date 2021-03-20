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
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite2;

std::vector<Enemy*> enemyList; 

bool InEditorMode, hasNodePoint1, hasNodePoint2, CanDrawLine;
std::vector<int> LineNodesSX; 
std::vector<int> LineNodesSY;
std::vector<int> LineNodesEX;
std::vector<int> LineNodesEY;

bool EnemyIsMoving = false;
float distance;
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

	Dwarf* dwarfEnemy = new Dwarf();
	enemyList.push_back(dwarfEnemy);

	testSprite2 = App::CreateSprite(".\\TestData\\Ships.bmp", 2, 12);
	testSprite2->SetPosition(400.0f, 400.0f);	
	testSprite2->SetFrame(2);
	testSprite2->SetScale(1.0f);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite2->Update(deltaTime);

	if (App::IsKeyPressed('E')) {
		if (!InEditorMode) {
			InEditorMode = true;
		}

		else {
			InEditorMode = false; 
		}
	}

	if (App::IsKeyPressed(VK_LBUTTON) && InEditorMode) {
		if (!hasNodePoint1) {
			hasNodePoint1 = true; 

			float mousePosx, mousePosy;
			App::GetMousePos(mousePosx, mousePosy);


		}
	}

	if (App::IsKeyPressed(VK_RBUTTON) && InEditorMode) {
		if (hasNodePoint1 && !hasNodePoint2) {
			hasNodePoint2 = true;

			float mousePosx, mousePosy;
			App::GetMousePos(mousePosx, mousePosy);

\

			hasNodePoint1 = false; 
			hasNodePoint2 = false; 
		}
	}

	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		//testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		testSprite->SetVertex(0, testSprite->GetVertex(0) + 5.0f);
	}*/ 

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}

	if (!enemyList.empty()) {

		for (auto enemy : enemyList) {
			enemy->Update(deltaTime);


			float enemyPosX, enemyPosY;
			enemy->GetPosition(enemyPosX, enemyPosY);


			float positionX = LineNodesEX[enemy->GetEnemyMoveIndex()] - enemyPosX;
			float positionY = LineNodesEY[enemy->GetEnemyMoveIndex()] - enemyPosY;
			distance = sqrt(positionX * positionX + positionY * positionY);

			enemy->SetPosition(enemyPosX + positionX / distance * 3.0f, enemyPosY + positionY / distance * 3.0f);

			if (distance < 2.0f && enemy->GetEnemyMoveIndex() < 4) {
				enemy->SetEnemyMoveIndex(enemy->GetEnemyMoveIndex() + 1);
			}

			float tempSprite1PositionX, tempSprite1PositionY;
			enemy->GetPosition(tempSprite1PositionX, tempSprite1PositionY);

			float tempSprite2PositionX, tempSprite2PositionY;
			testSprite2->GetPosition(tempSprite2PositionX, tempSprite2PositionY);

			double directionX = tempSprite1PositionX - tempSprite2PositionX;
			double directionY = tempSprite1PositionY - tempSprite2PositionY;

			float newAngle = atan2(directionX, directionY);


			testSprite2->SetAngle(-newAngle);
		}
	}

	else if (enemyList.empty()) {
		
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

	//------------------------------------------------------------------------
	// Example Sprite Code....
	if (!enemyList.empty()) {
		for (auto enemy : enemyList) {
			enemy->Render();
		}
	}

	testSprite2->Draw();
	//------------------------------------------------------------------------

	std::string distanceDebugging = "Distance = " + std::to_string(distance);
	App::Print(0, 350, distanceDebugging.c_str());
	App::Print(100, 100, "E - Editor Mode");

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
		}
	}
	delete testSprite2;
	//------------------------------------------------------------------------
}