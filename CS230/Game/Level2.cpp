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
#include "ScreenWrap.h"

Level2::Level2() 
	:levelReload(CS230::InputKey::Keyboard::R), mainmenu(CS230::InputKey::Keyboard::Escape), timer(0), score(0), lives(0),Show(CS230::InputKey::Keyboard::Tilde){}

void Level2::Load()
{
	objectPtr = new CS230::GameObjectManager();
	
	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
	scoreTexture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture(scoreString, 0xFFFFFFFF, true);
	
	objectPtr->Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());
	objectPtr->Add(new Meteor());

#ifdef _DEBUG
	AddGSComponent(new ShowCollision(CS230::InputKey::Keyboard::Tilde));
#endif
	
}

void Level2::Update(double dt) {
	
	objectPtr->Update(dt);

	if (mainmenu.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::MainMenu));
	}
#ifdef _DEBUG
    if (levelReload.IsKeyReleased() == true) {
        Engine::GetGameStateManager().ReloadState();
    }
	GetGSComponent<ShowCollision>()->Update(dt);
	
#endif
}

void Level2::Unload() {
	ClearGSComponent();
}

void Level2::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	objectPtr->DrawAll(cameraMatrix);

	math::ivec2 winSize = Engine::GetWindow().GetSize();
	
	scoreTexture.Draw(math::TranslateMatrix(math::ivec2{ 10, winSize.y - scoreTexture.GetSize().y - 5 }));
}