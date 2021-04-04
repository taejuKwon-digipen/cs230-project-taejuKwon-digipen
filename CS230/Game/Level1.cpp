/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Project: CS230
Author: Taeju Kwon
Creation date:  2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "Screens.h"
#include "Level1.h"
#include "..\Engine/Camera.h"

Level1::Level1() : levelNext(CS230::InputKey::Keyboard::Enter), levelReload(CS230::InputKey::Keyboard::R),
hero(math::vec2( Engine::GetWindow().GetSize().x / 2.0 ,floor ),camera), ball1(math::vec2( 600.0, floor )), ball2(math::vec2(2700.0, floor)),
ball3(math::vec2(4800.0, floor)),
camera({ {Engine::GetWindow().GetSize().x * 0.15, 0 },{Engine::GetWindow().GetSize().x * 0.35, Engine::GetWindow().GetSize().y / 1.0 } }) {};

void Level1::Load()
{
	background.Add("assets/clouds.png", 4);
	background.Add("assets/Moutains.png", 2);
	background.Add("assets/foreground.png", 1);
	camera.SetExtent({ {0,0}, {background.Size().x - Engine::GetWindow().GetSize().x, Engine::GetWindow().GetSize().y } });
	camera.SetPosition({ 0,0 });
	hero.Load();
	ball1.Load();
	ball2.Load();
	ball3.Load();
}
void Level1::Update(double dt) {
	if (levelNext.IsKeyReleased() == true) {
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
	}
#ifdef _DEBUG
	if (levelReload.IsKeyReleased() == true) {
		Engine::GetGameStateManager().ReloadState();
	}
#endif
	hero.Update(dt);
	camera.Update(hero.Getposition());
	ball1.Update(dt);
	ball2.Update(dt);
	ball3.Update(dt);
}
void Level1::Unload(){
	background.Unload();
}

void Level1::Draw()
{
	Engine::GetWindow().Clear(0xAAAAFF);
	background.Draw(camera);
	math::TransformMatrix cameraMatrix = camera.GetMatrix();
	hero.Draw(cameraMatrix);
	ball1.Draw(cameraMatrix);
	ball2.Draw(cameraMatrix);
	ball3.Draw(cameraMatrix);

}
