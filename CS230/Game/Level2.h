/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Project: CS230
Author: Taeju Kwon
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "Ship.h"

class Level2 : public CS230::GameState {
public:
	Level2();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level2"; }

private:
	CS230::InputKey levelNext;
	CS230::InputKey levelReload;
	Ship ship;
};