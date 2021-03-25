/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/18/2021
-----------------------------------------------------------------*/
#include "Hero.h"
#include "../Engine/Engine.h"
#include "Level1.h"


Hero::Hero(math::vec2 startPos) : startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left),
moveRightKey(CS230::InputKey::Keyboard::Right),moveJumpKey(CS230::InputKey::Keyboard::Up), isJumping(), isRising(){}

void Hero::Load()
{
	sprite.Load("assets/Hero.png", {56,14});
	position = startPos;
	
	isJumping = false;
	isRising = false;
}


void Hero::Update(double dt)//delta time
{
	
	position += velocity;
	
	if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += xAccel * dt;
		Engine::GetLogger().LogDebug("+ Accelerating"); // 오른쪽 버튼 누르면 가속
	}
	else if (moveRightKey.IsKeyDown() == false && velocity.x > 0)
	{
		velocity.x -= xDrag * dt;
		Engine::GetLogger().LogDebug("- Dragging"); //오른쪽 안눌리고 + 이면 drag 적용
	}
	else if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= xAccel * dt;
		Engine::GetLogger().LogDebug("- Accelerating"); // 왼쪽 누르면 왼쪽으로
	}
	else if (moveLeftKey.IsKeyDown() == false && velocity.x < 0)
	{
		velocity.x += xDrag * dt;
		Engine::GetLogger().LogDebug("+ Dragging"); //나머지면 왼쪽 멈춤
	}
	if (velocity.x < 0 && moveRightKey.IsKeyDown())
	{
		velocity.x += xDrag;
		Engine::GetLogger().LogDebug("+ Skidding");
	}
	else if (velocity.x > 0 && moveLeftKey.IsKeyDown())
	{
		velocity.x -= xDrag;
		Engine::GetLogger().LogDebug("- Skidding");
	}
	
	if(isJumping == true)
	{
		velocity.y += Level1::gravity * dt;
		
		if(isRising == true && velocity.y <= 0)
		{
			isRising = false;
			Engine::GetLogger().LogDebug("Top of jump (Early) - YPos: " + to_string(position.y));
		} else if(isRising == true && moveJumpKey.IsKeyReleased() == true)
		{
			velocity.y = 0;
			isRising = false;
			Engine::GetLogger().LogDebug("Top of jump (Early) - YPos:" + to_string(position.y));
		}
	}

	if( moveJumpKey.IsKeyDown() == true && isJumping == false)
	{
		velocity.y = jumpVelocity;
		isJumping = true;
		isRising = true;
		Engine::GetLogger().LogDebug("Starting Jump - YPos:" + to_string(position.y));
	}

	if (velocity.x > xMVelo)
	{
		velocity.x = xMVelo; //최고속도
		Engine::GetLogger().LogDebug("+ Max velocity");
	}
	else if (velocity.x < -xMVelo)
	{
		velocity.x = -xMVelo; //최고속도
		Engine::GetLogger().LogDebug("- Max velocity");
	}


	if( (velocity.x >0 && velocity.x < 0.1)|| (velocity.x < 0 && velocity.x > -0.1) )
	{
		velocity.x = 0;
		Engine::GetLogger().LogDebug("Stopped");
	}

	if(isJumping == true && (position.y < Level1::floor))
	{
		velocity.y = 0;
		position.y = Level1::floor;
		isJumping = false;
		Engine::GetLogger().LogDebug("Ending Jump - YPos: " + to_string(position.y));
	}
}

void Hero::Draw()
{
	sprite.Draw(position);
}



