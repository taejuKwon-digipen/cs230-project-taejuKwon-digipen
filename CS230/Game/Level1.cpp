/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level1.h"

Level1::Level1() : hero({ 150, Level1::floor }, camera), 
						camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0 }, {0.35 * Engine::GetWindow().GetSize().x, 0 }}),
						ball1({ 600, Level1::floor }), ball2({ 2700, Level1::floor }), ball3({ 4800, Level1::floor }),
						levelReload(CS230::InputKey::Keyboard::R), levelNext(CS230::InputKey::Keyboard::Enter) {}

void Level1::Load() {
	hero.Load();
	ball1.Load();
	ball2.Load();
	ball3.Load();

	background.Add("assets/clouds.png", 4);
	background.Add("assets/mountains.png", 2);
	background.Add("assets/foreground.png", 1);

	camera.SetPosition({ 0,0 });
	camera.SetExtent({{ 0,0 }, { background.Size() - Engine::GetWindow().GetSize() } });
}
void Level1::Update(double dt) {
	hero.Update(dt);
	ball1.Update(dt);
	ball2.Update(dt);
	ball3.Update(dt);
	camera.Update(hero.GetPosition());

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
}

void Level1::Draw() {
	Engine::GetWindow().Clear(0x3399DAFF);

	background.Draw(camera);

	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero.Draw(cameraMatrix);
	ball1.Draw(cameraMatrix);
	ball2.Draw(cameraMatrix);
	ball3.Draw(cameraMatrix);
}