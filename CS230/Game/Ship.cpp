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

void Ship::Update()
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		position.x-= 5;
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		position.x+= 5;
	} else if (moveUpKey.IsKeyDown() == true)
	{
		position.y += 5;
	}else if (moveDownKey.IsKeyDown() == true){
		position.y -= 5;
	}
}

void Ship::Draw()
{
	sprite.Draw(position);
}



