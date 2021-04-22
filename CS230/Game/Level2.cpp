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

Level2::Level2() 
	:levelReload(CS230::InputKey::Keyboard::R), levelNext(CS230::InputKey::Keyboard::Enter){}

void Level2::Load()
{
	gameObjectManager.Add(new Ship({ Engine::GetWindow().GetSize() / 2.0 }));
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());
	gameObjectManager.Add(new Meteor());

}

void Level2::Update(double dt) {
	
	gameObjectManager.UpdateAll(dt);

	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().Shutdown();
	}
#ifdef _DEBUG
    if (levelReload.IsKeyReleased() == true) {
        Engine::GetGameStateManager().ReloadState();
    }
#endif
}

void Level2::Unload() {
	gameObjectManager.Unload();
}

void Level2::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	gameObjectManager.DrawAll(cameraMatrix);
}