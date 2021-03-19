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
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Eample data....
//------------------------------------------------------------------------
CSimpleSprite *testSprite;
CSimpleSprite *testSprite2;

bool InEditorMode, hasNodePoint1, hasNodePoint2, CanDrawLine;
std::vector<int> LineNodes; 

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
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

	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(2.0f);

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
	testSprite->Update(deltaTime);
	testSprite2->Update(deltaTime);

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);

	}

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

			LineNodes.push_back(mousePosx); 
			LineNodes.push_back(mousePosy);
		}
	}

	if (App::IsKeyPressed(VK_RBUTTON) && InEditorMode) {
		if (hasNodePoint1 && !hasNodePoint2) {
			hasNodePoint2 = true;

			float mousePosx, mousePosy;
			App::GetMousePos(mousePosx, mousePosy);

			LineNodes.push_back(mousePosx);
			LineNodes.push_back(mousePosy);

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

	float tempSprite1PositionX, tempSprite1PositionY;
	testSprite->GetPosition(tempSprite1PositionX, tempSprite1PositionY);

	float tempSprite2PositionX, tempSprite2PositionY;
	testSprite2->GetPosition(tempSprite2PositionX, tempSprite2PositionY);

	double directionX = tempSprite1PositionX - tempSprite2PositionX;
	double directionY = tempSprite1PositionY - tempSprite2PositionY;

	float newAngle = atan2(directionX, directionY);
	

	testSprite2->SetAngle(-newAngle);
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
	App::DrawLine(1, 1, 600, 600, r, g, b);

	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Draw();
	testSprite2->Draw();
	//------------------------------------------------------------------------


	for (int i = 0; i < LineNodes.size(); i++) {		
		if (LineNodes.size() > 6) {
			App::DrawLine(LineNodes[0], LineNodes[1], LineNodes[2], LineNodes[3], r, g, b);
			App::DrawLine(LineNodes[4], LineNodes[5], LineNodes[6], LineNodes[7], r, g, b);
		}
	}


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
	delete testSprite;
	delete testSprite2;
	//------------------------------------------------------------------------
}