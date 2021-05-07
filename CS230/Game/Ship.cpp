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
#include "ScreenWrap.h"

Ship::Ship(math::vec2 pos) :rotateCounterKey(CS230::InputKey::Keyboard::A), 
				rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), isAccelerating(false),
				GameObject(pos, GetRotation(), GetScale()), flameLeft("assets/Flame.spt", this), flameRight("assets/Flame.spt", this)
{
	AddGOComponent(new CS230::Sprite("assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
}

void Ship::Update(double dt)
{
	GetGOComponent<CS230::Sprite>()->Update(dt);
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
	UpdateVelocity({ -(GetVelocity() * Ship::drag * dt) });
	UpdatePosition( GetVelocity() * dt );

	SetScale({  0.75, 0.75 });

	GetGOComponent<ScreenWrap>()->Update(dt);
	
}

void Ship::Draw(math::TransformMatrix cameraMatrix) {

	flameRight.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)) * cameraMatrix);
	flameLeft.Draw(GetMatrix() * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)) * cameraMatrix);
	GetGOComponent<CS230::Sprite>()->Draw(GetMatrix() * cameraMatrix);

	ShowCollision* showCollision = Engine::GetGSComponent<ShowCollision>();
	if (showCollision != nullptr)
	{
		if (showCollision->IsEnabled() == true)
		{
			CS230::Collision* collision = GetGOComponent<CS230::Collision>();
			if (collision != nullptr)
			{
				collision->Draw(cameraMatrix);
			}
		}
	}
}