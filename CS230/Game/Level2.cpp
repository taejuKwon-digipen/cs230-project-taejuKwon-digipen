/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"   //GetWindow, GetGameStateManager
#include "Level2.h"
#include "Ship.h"
#include "Meteor.h"
#include "Fonts.h"
#include "Screens.h"
#include "Score.h"

Level2::Level2() : mainmenu(CS230::InputKey::Keyboard::Escape), levelReload(CS230::InputKey::Keyboard::R), objectPtr(nullptr) {}

void Level2::Load()
{
	objectPtr = new CS230::GameObjectManager();
	AddGSComponent(objectPtr);
	AddGSComponent(new Score(0, Fonts::Font2));
	
	objectPtr->Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(shipPtr);
	GameOverTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Game Over", 0xFFFFFFFF, true);
	RestartTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("Press r to restart", 0xFFFFFFFF, true);

#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	
}

void Level2::Update(double dt) {
	
	objectPtr->Update(dt);

	if (mainmenu.IsKeyReleased() == true) 
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
	
#ifdef _DEBUG
	GetGSComponent<ShowCollision>()->Update(dt);
	
    if (levelReload.IsKeyReleased() == true) 
	{
        Engine::GetGameStateManager().ReloadState();
    }
#else
	if(shipPtr -> IsDead() == true && reload.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}

void Level2::Unload() {
	ClearGSComponent();
}

void Level2::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	objectPtr->DrawAll(cameraMatrix);
	GetGSComponent<Score>()->Draw(math::ivec2{ 10, Engine::GetWindow().GetSize().y - 5 });

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	if (shipPtr->IsDead() == true)
	{
		GameOverTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - GameOverTexture.GetSize().x / 2, winSize.y / 2 + GameOverTexture.GetSize().y / 2 }));
		RestartTexture.Draw(math::TranslateMatrix(math::ivec2{ winSize.x / 2 - RestartTexture.GetSize().x / 2, winSize.y / 2 - GameOverTexture.GetSize().y / 2 }));
	}
}