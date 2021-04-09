/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ship.cpp
Project: CS230
Author: Teaju Kwon
Creation date: 2/18/2021
-----------------------------------------------------------------*/
#include "Ship.h"
#include "../Engine/Engine.h"

Ship::Ship(math::vec2 startPos) : startPos(startPos),
rotateCounterKey(CS230::InputKey::Keyboard::A), rotateClockKey(CS230::InputKey::Keyboard::D),
accelerateKey(CS230::InputKey::Keyboard::W), rotate(radian) {};

void Ship::Load()
{
	sprite.Load("assets/Ship.png", { {0,0}, {16,0}, {36,0} });
	sprite.Load("assets/flame.png", {35,0});
	sprite.Load("assets/flame.png", {65,0});
	position = startPos;
	math::RotateMatrix(0);
}

void Ship::Update(double dt)
{
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	
	if (rotateCounterKey.IsKeyDown() == true)
	{
		radian -= shipVelo * dt;
	}
	else if (rotateClockKey.IsKeyDown() == true)
	{
		radian += shipVelo * dt;
	} else if (accelerateKey.IsKeyDown() == true)
	{
		math::RotateMatrix{ radian };
		velocity.y += accel * dt;
	}
	velocity.y -= velocity.y * drag * dt;
	velocity.x -= velocity.x * drag * dt;

	Engine::GetLogger().LogDebug("Velocity = " + std::to_string(velocity.x) + "," + std::to_string(velocity.y));
	TestForwrap();
	
	objectMatrix = math::TranslateMatrix(position);
}


void Ship::Draw()
{
	
	sprite.Draw(objectMatrix);
}

void Ship::TestForwrap()
{
	if(position.x > Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x/2)
	{
		position.x =  -sprite.GetTextureSize().x / 2;
	}
	else if(position.x < - sprite.GetTextureSize().x / 2)
	{
		position.x = Engine::GetWindow().GetSize().x + sprite.GetTextureSize().x / 2;
	}
	else if (position.y <  -sprite.GetTextureSize().y /2)
	{
		position.y = Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y / 2;
	}
	else if (position.y > Engine::GetWindow().GetSize().y + sprite.GetTextureSize().y/2)
	{
		position.y = -sprite.GetTextureSize().y/2;
	}	
}




