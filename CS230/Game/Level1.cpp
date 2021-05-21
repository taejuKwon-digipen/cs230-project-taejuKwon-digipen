/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author:Taeju Kwon
Creation date: 19/4/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level1.h"
#include "Ball.h"
#include "Hero.h"
#include "Bunny.h"
#include "Exit.h"
#include "Floor.h"
#include "Fonts.h"
#include "Score.h"
#include "TreeStump.h"
#include "..\Engine/Camera.h"
#include "Timer.h"
#include "Gravity.h"

Level1::Level1() : levelReload(CS230::InputKey::Keyboard::R), MainMenu(CS230::InputKey::Keyboard::Escape), lives(3), heroPtr(nullptr), Show(CS230::InputKey::Keyboard::Tilde)
{
}

void Level1::Load() {


	objectPtr = new CS230::GameObjectManager();
	timePtr = new Timer(60);
	scorePtr = new Score(0, Fonts::Font1);
	gravPtr = new Gravity(2000);
	background = new Background();
	
	std::string liveString = "Lives:" + std::to_string(lives);
	livesTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(liveString, 0xFFFFFFFF, true);

	AddGSComponent(objectPtr);
	AddGSComponent(timePtr);
	AddGSComponent(scorePtr);
	AddGSComponent(gravPtr);
	AddGSComponent(background);

	objectPtr->Add(new Ball({ 600, Level1::floor }));
	objectPtr->Add(new Ball({ 2700, Level1::floor }));
	objectPtr->Add(new Ball({ 4800, Level1::floor }));
	objectPtr->Add(new Bunny({ 1000, Level1::floor }));
	objectPtr->Add(new Bunny({ 2000, Level1::floor }));
	objectPtr->Add(new Bunny({ 3200, Level1::floor }));
	objectPtr->Add(new Bunny({ 3800, Level1::floor }));
	objectPtr->Add(new TreeStump({ 300, Level1::floor }, 3));
	objectPtr->Add(new TreeStump({ 1200, Level1::floor }, 2));
	objectPtr->Add(new TreeStump({ 2200, Level1::floor }, 1));
	objectPtr->Add(new TreeStump({ 2800, Level1::floor }, 5));
	objectPtr->Add(new TreeStump({ 5100, Level1::floor }, 5));
	objectPtr->Add(new Floor({ {0, 0}, {1471, static_cast<int>(Level1::floor)} }));
	objectPtr->Add(new Floor({ {1602, 0}, {4262, static_cast<int>(Level1::floor)} }));
	objectPtr->Add(new Floor({ {4551, 0}, {5760, static_cast<int>(Level1::floor)} }));
	objectPtr->Add(new Exit({ {5550, static_cast<int>(Level1::floor)}, {5760, 683} }));

	heroPtr = new Hero({ 100, Level1::floor - 1 });
	objectPtr->Add(heroPtr);
	
	background->Add("assets/clouds.png", 4);
	background->Add("assets/mountains.png", 2);
	background->Add("assets/foreground.png", 1);

	CS230::Camera* cameraPtr = new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } });
	AddGSComponent(cameraPtr);
	cameraPtr->SetExtent({ { 0,0 }, { background->Size() - Engine::GetWindow().GetSize() } });

#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif

}

void Level1::Update(double dt) {
	GetGSComponent<CS230::Camera>()->Update(heroPtr->GetPosition());
	objectPtr->Update(dt);
	timePtr->Update(dt);
	scorePtr->Update(dt);
	
	if (timePtr->hasEnded() == true )
	{
		lives--;
		if (lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}

	if (heroPtr->IsDead() == true)
	{
		lives--;
		if (lives == 0)
		{
			lives = 3;
			Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
		}
		else
		{
			Engine::GetGameStateManager().ReloadState();
		}
	}

	if (MainMenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
	GetGSComponent<ShowCollision>()->Update(dt);
#endif
}

void Level1::Unload() {
	ClearGSComponent();
}

void Level1::Draw() {

	Engine::GetWindow().Clear(0x3399DAFF);

	CS230::Camera* cameraPtr = GetGSComponent<CS230::Camera>();
	background->Draw(*cameraPtr);
	math::TransformMatrix cameraMatrix = cameraPtr->GetMatrix();

	objectPtr->DrawAll(cameraMatrix);
	math::ivec2 winSize = Engine::GetWindow().GetSize();

	timePtr->Draw(math::ivec2{ winSize.x, winSize.y });
	scorePtr->Draw(math::ivec2{ winSize.x/2, winSize.y});
	livesTexture.Draw(math::TranslateMatrix(math::ivec2{ Engine::GetWindow().GetSize().x / 2 -100, winSize.y - livesTexture.GetSize().y - 5 }));
}