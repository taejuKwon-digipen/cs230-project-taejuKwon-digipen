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
#include <iostream>


Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : startPos(startPos), moveLeftKey(CS230::InputKey::Keyboard::Left),
moveRightKey(CS230::InputKey::Keyboard::Right), moveJumpKey(CS230::InputKey::Keyboard::Up), isJumping(), isRising(), camera(camera) {};

void Hero::Load()
{
	sprite.Load("assets/Hero.png", math::ivec2{56,14});
	position = startPos;
	velocity = 0.0;

	isJumping = false;
	isRising = false;
}

void Hero::Update(double dt)//delta time
{
	std::cout << position.y << std::endl;
	if (moveRightKey.IsKeyDown() == true)
	{
		velocity.x += xAccel * dt;
		if (velocity.x > 0 && velocity.x < xMVelo) {
			Engine::GetLogger().LogDebug("+ Accelerating"); // ������ ��ư ������ ����
		}
		if (velocity.x < 0)
		{
			velocity.x += xDrag * 2 * dt;
			Engine::GetLogger().LogDebug("+ Skidding");
		}
	}
	else if (moveRightKey.IsKeyDown() == false && velocity.x > 0)
	{
		velocity.x -= xDrag * dt;
		Engine::GetLogger().LogDebug("- Dragging"); //������ �ȴ����� + �̸� drag ����
	}
	
	else if (moveLeftKey.IsKeyDown() == true)
	{
		velocity.x -= xAccel * dt;
		if (velocity.x < 0 && velocity.x > -xMVelo) {
			Engine::GetLogger().LogDebug("- Accelerating"); // ���� ������ ��������
		}
		if (velocity.x > 0)
		{
			velocity.x -= xDrag * 2 * dt;
			Engine::GetLogger().LogDebug("- Skidding");
		}
	}
	else if (moveLeftKey.IsKeyDown() == false && velocity.x < 0)
	{
		velocity.x += xDrag * dt;
		Engine::GetLogger().LogDebug("+ Dragging"); //�������� ���� ����
	}

	if (position.x - camera.GetPosition().x > Engine::GetWindow().GetSize().x - sprite.GetTextureSize().x/2.0)
	{
		velocity.x = 0;
		position.x = Engine::GetWindow().GetSize().x - sprite.GetTextureSize().x / 2 + camera.GetPosition().x;
	}
	else if (position.x < 0)
	{
		velocity.x = 0;
		position.x = 0 + sprite.GetTextureSize().x / 2;
	}

	//=====================================================================================
	
	if(isJumping == true)
	{
		velocity.y += Level1::gravity * dt;
		
		if(isRising == true && velocity.y <= 0)
		{
			isRising = false;
			Engine::GetLogger().LogDebug("Top of jump - YPos: " + to_string(position.y));
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
		velocity.x = xMVelo; //�ְ�ӵ�
		Engine::GetLogger().LogDebug("+ Max velocity");
	}
	else if (velocity.x < -xMVelo)
	{
		velocity.x = -xMVelo; //�ְ�ӵ�
		Engine::GetLogger().LogDebug("- Max velocity");
	}

	
	if ( moveLeftKey.IsKeyDown() == false && moveRightKey.IsKeyDown() == false &&
		(velocity.x > 0 && velocity.x < 0.5 || velocity.x < 0 && velocity.x > -0.5))
	{
		velocity.x = 0;
		Engine::GetLogger().LogDebug("Stopped");
	}

	position += velocity;
	
	if(isJumping == true && (position.y < Level1::floor))
	{
		velocity.y = 0;
		position.y = Level1::floor;
		isJumping = false;
		Engine::GetLogger().LogDebug("Ending Jump - YPos: " + to_string(position.y));
	}

	objectMatrix = math::TranslateMatrix(position);
}

void Hero::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw( objectMatrix * cameraMatrix);

}



