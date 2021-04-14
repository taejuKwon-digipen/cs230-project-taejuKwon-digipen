/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"    //Engine::GetWindow
#include "../Engine/TransformMatrix.h"
#include "Ship.h"

Ship::Ship(math::vec2 pos) : initPosition(pos), rotateCounterKey(CS230::InputKey::Keyboard::A), 
				rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W) {}

void Ship::Load() {
	sprite.Load("assets/Ship.png", { {50, 41}, {-15, -41}, {15, -41} });
	position = initPosition;

	flameLeft.Load("assets/flame.png", { 8,15 });
	flameRight.Load("assets/flame.png", { 8,15 });
	velocity = { 0,0 };
	rotationAmount = 0;
}

void Ship::Update(double dt) {
	if (rotateClockKey.IsKeyDown() == true) {
		rotationAmount -= Ship::rotationRate * dt;
	}
	if (rotateCounterKey.IsKeyDown() == true) {
		rotationAmount += Ship::rotationRate * dt;
	}
	math::TransformMatrix roation = math::RotateMatrix(rotationAmount);
	if (accelerateKey.IsKeyDown() == true) {
		velocity += math::RotateMatrix(rotationAmount) * math::vec2 { 0, accel* dt };
		if (isAccelerating == false) {
			Engine::GetLogger().LogDebug("Accelerating");
			isAccelerating = true;
		}
	} else {
		if (isAccelerating == true) {
			Engine::GetLogger().LogDebug("Stopped Accelerating");
			isAccelerating = false;
		}
	}

	velocity -= (velocity * Ship::drag * dt);

	position += velocity * dt;

	objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotationAmount) * math::ScaleMatrix({ 0.75, 0.75 });
	TestForWrap();
}

void Ship::TestForWrap() {
	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2.0) {
		position.y = 0 - sprite.GetTextureSize().y / 2.0;
	} else if (position.y < 0 - sprite.GetTextureSize().y / 2.0) {
		position.y = Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2.0;
	}
	if (position.x > Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2.0) {
		position.x = 0 - sprite.GetTextureSize().x / 2.0;
	} else if (position.x < 0 - sprite.GetTextureSize().x / 2.0) {
		position.x = Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2.0;
	}
}

void Ship::Draw() {
	flameRight.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(1)));
	flameLeft.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(2)));
	sprite.Draw(objectMatrix);
}