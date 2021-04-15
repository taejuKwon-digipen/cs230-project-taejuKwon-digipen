/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 3/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"    //Engine::GetWindow
#include "../Engine/TransformMatrix.h"
#include "Ship.h"
#include "Flame_Anims.h"

Ship::Ship(math::vec2 pos) : initPosition(pos), rotateCounterKey(CS230::InputKey::Keyboard::A), 
				rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W) {}

void Ship::Load() {
	sprite.Load("assets/Ship.spt");
	position = initPosition;

	flameLeft.Load("assets/Flame.spt");
	flameRight.Load("assets/Flame.spt");
	velocity = { 0,0 };
	rotationAmount = 0;
}

void Ship::Update(double dt) {

	sprite.Update(dt);
	flameLeft.Update(dt);
	flameRight.Update(dt);
	
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
			flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			isAccelerating = true;
		}
	} else {
		if (isAccelerating == true) {
			/*Engine::GetLogger().LogDebug("Stopped Accelerating");*/
			flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			isAccelerating = false;
		}
	}

	velocity -= (velocity * Ship::drag * dt);

	position += velocity * dt;

	objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotationAmount) * math::ScaleMatrix({ 0.75, 0.75 });
	TestForWrap();
}

void Ship::TestForWrap() {
	if (position.y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0) {
		position.y = 0 - sprite.GetFrameSize().y / 2.0;
	} else if (position.y < 0 - sprite.GetFrameSize().y / 2.0) {
		position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;
	}
	if (position.x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0) {
		position.x = 0 - sprite.GetFrameSize().x / 2.0;
	} else if (position.x < 0 - sprite.GetFrameSize().x / 2.0) {
		position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;
	}
}

void Ship::Draw() {
	flameRight.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(1)));
	flameLeft.Draw(objectMatrix * math::TranslateMatrix(sprite.GetHotSpot(2)));
	sprite.Draw(objectMatrix);
}