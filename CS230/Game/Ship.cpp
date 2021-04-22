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

Ship::Ship(math::vec2 pos) :rotateCounterKey(CS230::InputKey::Keyboard::A), 
				rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), isAccelerating(false),
				GameObject(pos, GetRotation(), GetScale())
{
	sprite.Load("assets/Ship.spt");
	flameLeft.Load("assets/Flame.spt");
	flameRight.Load("assets/Flame.spt");
}

void Ship::Update(double dt)
{
	sprite.Update(dt);
	flameLeft.Update(dt);
	flameRight.Update(dt);
	
	if (rotateClockKey.IsKeyDown() == true) {
		/*rotationAmount -= Ship::rotationRate * dt;*/
		UpdateRotation({ -Ship::rotationRate * dt });
	}
	if (rotateCounterKey.IsKeyDown() == true) {
		UpdateRotation({ Ship::rotationRate * dt });
	}
	
	math::TransformMatrix roation = math::RotateMatrix(GetRotation());
	
	if (accelerateKey.IsKeyDown() == true) {
		/*velocity += math::RotateMatrix(rotationAmount) * math::vec2 { 0, accel* dt };*/
		UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
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

	/*velocity -= (velocity * Ship::drag * dt);*/
	UpdateVelocity({ -(GetVelocity() * Ship::drag * dt) });

	/*position += velocity * dt;*/
	UpdatePosition( GetVelocity() * dt );

	SetScale({  0.75, 0.75 });
	/*objectMatrix = math::TranslateMatrix(position) * math::RotateMatrix(rotationAmount) * math::ScaleMatrix({ 0.75, 0.75 });*/
	TestForWrap();
}

void Ship::TestForWrap() {
	if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0) {
		/*position.y = 0 - sprite.GetFrameSize().y / 2.0;*/
		SetPosition({ GetPosition().x, 0 - sprite.GetFrameSize().y / 2.0 });
	} else if (GetPosition().y < 0 - sprite.GetFrameSize().y / 2.0) {
		/*position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;*/
		SetPosition({ GetPosition().x,Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0 });
	}
	if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0) {
		/*position.x = 0 - sprite.GetFrameSize().x / 2.0;*/
		SetPosition({ 0 - sprite.GetFrameSize().x / 2.0 , GetPosition().y });
	} else if (GetPosition().x < 0 - sprite.GetFrameSize().x / 2.0) {
		/*position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;*/
		SetPosition({ Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0 , GetPosition().y });
	}
}

void Ship::Draw(math::TransformMatrix cameraMatrix) {
	GetMatrix();
	
	flameRight.Draw(GetMatrix() * math::TranslateMatrix(sprite.GetHotSpot(1)) * cameraMatrix);
	flameLeft.Draw(GetMatrix() * math::TranslateMatrix(sprite.GetHotSpot(2)) * cameraMatrix);
	sprite.Draw(GetMatrix()* cameraMatrix);
}