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
#include "TreeStump.h"

Level1::Level1() : camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 } }),
levelReload(CS230::InputKey::Keyboard::R), levelNext(CS230::InputKey::Keyboard::Enter), heroPtr(nullptr) {}

void Level1::Load() {
	heroPtr = new Hero({ 150, Level1::floor }, camera);

	gameObjectManager.Add(heroPtr);
	gameObjectManager.Add(new Ball({ 600, Level1::floor }));
	gameObjectManager.Add(new Ball({ 2700, Level1::floor }));
	gameObjectManager.Add(new Ball({ 4800, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 1000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 2000, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3200, Level1::floor }));
	gameObjectManager.Add(new Bunny({ 3800, Level1::floor }));
	gameObjectManager.Add(new TreeStump({ 300, Level1::floor }, 3));
	gameObjectManager.Add(new TreeStump({ 1200, Level1::floor }, 2));
	gameObjectManager.Add(new TreeStump({ 2200, Level1::floor }, 1));
	gameObjectManager.Add(new TreeStump({ 2800, Level1::floor }, 5));
	gameObjectManager.Add(new TreeStump({ 5100, Level1::floor }, 5));

	background.Add("assets/clouds.png", 4);
	background.Add("assets/mountains.png", 2);
	background.Add("assets/foreground.png", 1);

	camera.SetPosition({ 0,0 });
	camera.SetExtent({ { 0,0 }, { background.Size() - Engine::GetWindow().GetSize() } });

}
void Level1::Update(double dt) {
	gameObjectManager.UpdateAll(dt);
	camera.Update(heroPtr->GetPosition());

	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
}
void Level1::Unload() {
	background.Unload();
	gameObjectManager.Unload();
}

void Level1::Draw() {
	Engine::GetWindow().Clear(0x3399DAFF);

	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	gameObjectManager.DrawAll(cameraMatrix);
}