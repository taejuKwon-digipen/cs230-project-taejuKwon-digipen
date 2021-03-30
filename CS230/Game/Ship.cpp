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

Ship::Ship(math::vec2 startPos) : startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::A), moveRightKey(CS230::InputKey::Keyboard::D),
moveDownKey(CS230::InputKey::Keyboard::S), moveUpKey(CS230::InputKey::Keyboard::W) {};

void Ship::Load()
{
	sprite.Load("assets/Ship.png");
	position = startPos;
}

void Ship::Update(double dt)
{

	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	
	if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -=  accel * dt;
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += accel * dt;
	} else if (moveUpKey.IsKeyDown() == true)
	{
		velocity.y +=  accel * dt;
	}else if (moveDownKey.IsKeyDown() == true)
	{
		velocity.y -=  accel * dt;
	}
	
	velocity -= velocity * drag * dt;
	Engine::GetLogger().LogDebug("Velocity = " + to_string(velocity.x) + "," + to_string(velocity.y));
	TestForwrap();
}

void Ship::Draw()
{
	sprite.Draw(position);
}

void Ship::TestForwrap()
{

	if (position.x > Engine::GetWindow().GetSize().x/2)
	{
		position.x =  - Engine::GetWindow().GetSize().x/2;
	}
	else if (position.x == -Engine::GetWindow().GetSize().x / 2)
	{
		position.x = Engine::GetWindow().GetSize().x/2;
	}
	else if (position.y > Engine::GetWindow().GetSize().y/2)
	{
		position.y = -Engine::GetWindow().GetSize().y / 2;
	}
	else if(position.y == -Engine::GetWindow().GetSize().y / 2)
	{
		position.y = Engine::GetWindow().GetSize().y/2;
	}

}


