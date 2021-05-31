/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyShip.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 6/14/2021
-----------------------------------------------------------------*/
#include "EnemyShip.h"
#include "../Engine/Engine.h"
#include "Flame_Anims.h"
#include "GameObjectTypes.h"
#include "Ship_Anims.h"
#include "Ship.h"
#include "../Engine/Collision.h"


constexpr double PI = 3.1415926535897932384626433832795;

EnemyShip::EnemyShip(GameObject* player) : GameObject(), flameLeft("assets/flame.spt", this), flameRight("assets/flame.spt", this), isDead(false), player(player)
{
	const double distance = -((((rand() % 1024) / 1024.) * 128.) + 128);  //-random number
	const math::vec2 shipPosition = { player->GetPosition() };

	SetRotation((rand() % 1024 / 1024.) * 2 * PI);
	SetPosition(math::vec2{ math::RotateMatrix(GetRotation()) *math::vec2{0,distance} + shipPosition});//ship 에서 부터 -128, -256

	AddGOComponent(new CS230::Sprite("assets/EnemyShip.spt", this));
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ship_Anim::None_Anim));
	flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
	flameRight.PlayAnimation(static_cast<int>(Flame_Anim::Flame_Anim));
}

void EnemyShip::Update(double dt)
{
	flameLeft.Update(dt);
	flameRight.Update(dt);
	const math::vec2 facing = math::vec2{ math::RotateMatrix(GetRotation()) * math::vec2{0,1} } ;
	const math::vec2 Player = math::vec2{ player->GetPosition() - this->GetPosition()}.Normalize();

	if(Player.Cross(facing) > 0.05)
	{
		UpdateRotation(-rotationRate * dt);
	}
	else if(Player.Cross(facing) < -0.05)
	{
		UpdateRotation(rotationRate * dt);
	}
	SetVelocity(GetVelocity() + math::RotateMatrix(GetRotation()) * math::vec2{ 0, accel * dt });
	SetVelocity(GetVelocity() - GetVelocity() * drag * dt);
	UpdatePosition(GetVelocity() * dt);
	UpdateGOComponents(dt);
}

void EnemyShip::Draw(math::TransformMatrix displayMatrix)
{
	const math::TransformMatrix shipScreenMatrix = displayMatrix * GetMatrix();
	
	flameRight.Draw(shipScreenMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(1)));
	flameLeft.Draw(shipScreenMatrix * math::TranslateMatrix(GetGOComponent<CS230::Sprite>()->GetHotSpot(2)));
	GetGOComponent<CS230::Sprite>()->Draw(shipScreenMatrix);
}


GameObjectType EnemyShip::GetObjectType()
{
	return GameObjectType::EnemyShip;
}

std::string EnemyShip::GetObjectTypeName()
{
	return "Enemy Ship";
}

bool EnemyShip::CanCollideWith(GameObjectType collideAgainstType)
{
	if(collideAgainstType == GameObjectType::Laser || collideAgainstType == GameObjectType::Ship)
	{
		return true;
	}
	return false;
}

void EnemyShip::ResolveCollision(GameObject* collidedWith)
{
	switch (collidedWith->GetObjectType()) {
	case GameObjectType::Laser:
		GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(1));
		flameRight.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		flameLeft.PlayAnimation(static_cast<int>(Flame_Anim::None_Anim));
		RemoveGOComponent<CS230::Collision>();
		isDead = true;
		break;
	}
}



