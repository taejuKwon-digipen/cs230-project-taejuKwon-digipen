/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/24/2021
-----------------------------------------------------------------*/

#include "Ball.h"
#include "Level1.h"

Ball::Ball(math::vec2 startPos) : initPosition(startPos) {};

void Ball::Load()
{
	sprite.Load("assets/Ball.png", (44, 0));
	position = initPosition;
	velocity = math::vec2(0, 0);
}

void Ball::Update(double dt)
{

	velocity.y += Level1::gravity * dt;
	position.y += velocity.y * dt ;
	
	if (position.y < Level1::floor)
	{
		position.y = Level1::floor;
		velocity.y = bounceVelocity;
	}
	
	objectMatrix = math::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix)
{
	sprite.Draw({ cameraMatrix * objectMatrix });
}


