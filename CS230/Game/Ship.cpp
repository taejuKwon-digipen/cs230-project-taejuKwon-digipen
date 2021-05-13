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
#include "Ship_Anims.h"

Ship::Ship(math::vec2 pos) :rotateCounterKey(CS230::InputKey::Keyboard::A), 
                            rotateClockKey(CS230::InputKey::Keyboard::D), accelerateKey(CS230::InputKey::Keyboard::W), isAccelerating(false),
                            GameObject(pos, GetRotation(), GetScale()), flameLeft("assets/Flame.spt", this), flameRight("assets/Flame.spt", this)
{
	AddGOComponent(new CS230::Sprite("assets/Ship.spt", this));
	AddGOComponent(new ScreenWrap(*this));
}

void Ship::Update(double dt)
{
	if (isDead == false)
	{
		if (rotateCounterKey.IsKeyDown() == true)
		{
			UpdateRotation(rotationRate * dt);
		}
		if (rotateClockKey.IsKeyDown() == true)
		{
			UpdateRotation(-(rotationRate * dt));
		}
		if (accelerateKey.IsKeyDown() == true)
		{
			if (isAccelerating == false)
			{
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
			}
			isAccelerating = true;
			UpdateVelocity(math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
		}
		if (accelerateKey.IsKeyReleased() == true)
		{
			if (isAccelerating == true)
			{
				flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
				flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
			}
			isAccelerating = false;
		}
	}
	UpdateVelocity(math::vec2{ -(GetVelocity().x * Ship::drag * dt) ,-(GetVelocity().y * Ship::drag * dt) });
	UpdatePosition(math::vec2{ GetVelocity().x * dt,GetVelocity().y * dt });
	UpdateGOComponents(dt);
	flameLeft.Update(dt);
	flameRight.Update(dt);
	
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

bool Ship::CanCollideWith(GameObjectType ObjectBType)
{
	if (ObjectBType == GameObjectType::Ship)
	{
		return false;
	}
	return true;
}

void Ship::ResolveCollision(CS230::GameObject* )
{
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
	this->RemoveGOComponent<CS230::Collision>();
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::Explode_Anim));
	isDead = true;
}

