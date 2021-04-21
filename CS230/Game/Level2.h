/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\GameState.h"
#include "..\Engine\Input.h"
#include "..\Engine/GameObjectManager.h"
#include "..\Engine/TransformMatrix.h"

class Ship;

class Level2 : public CS230::GameState {
public:
	Level2();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level 2"; }
private:
	
	CS230::InputKey levelReload;
	CS230::InputKey levelNext;

	CS230::GameObjectManager gameObjectManager;
	math::TransformMatrix cameraMatrix;
};

