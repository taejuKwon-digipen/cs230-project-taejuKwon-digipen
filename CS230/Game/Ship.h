/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Input.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\TransformMatrix.h"
#include "..\Engine/GameObject.h"

class Ship : public CS230::GameObject{
public:
	Ship(math::vec2 startPos);
	void Update(double dt) override;
	void Draw(math::TransformMatrix cameraMatrix) override;

private:
	void TestForWrap();
	
	CS230::Sprite flameLeft;
	CS230::Sprite flameRight;

	bool isAccelerating;
	static constexpr double accel = 400;
	static constexpr double drag = 1;
	static constexpr double rotationRate = 2.0;

	CS230::InputKey rotateCounterKey;
	CS230::InputKey rotateClockKey;
	CS230::InputKey accelerateKey;
};