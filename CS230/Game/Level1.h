/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Project: CS230
Author: Taeju Kwon
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "Hero.h"
#include "Ball.h"

class Level1 : public CS230::GameState {
public:
	Level1();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level1"; }

	static constexpr double floor = 126.0f;
	static constexpr double gravity = -170.0;


protected:
	CS230::InputKey levelNext;
	CS230::InputKey levelReload;
	Hero hero;
	CS230::Texture background;
	Ball ball;

};