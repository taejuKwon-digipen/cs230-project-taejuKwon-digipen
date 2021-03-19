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

void Ship::Draw()
{
	if (moveLeftKey.IsKeyDown() == true)
	{
		position.x--;
	}
	else if (moveRightKey.IsKeyDown() == true)
	{
		position.x++;
	} else if (moveUpKey.IsKeyDown() == true)
	{
		position.y++;
	}else if (moveDownKey.IsKeyDown() == true){
		position.y--;
	}
}

void Ship::Update()
{
	sprite.Draw(position);
}



