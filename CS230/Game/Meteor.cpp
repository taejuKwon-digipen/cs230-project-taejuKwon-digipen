/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "Meteor.h"
#include "../Engine/Engine.h"

Meteor::Meteor() : GameObject({ 0,0 }) {

	constexpr double PI = 3.1415926535;

	sprite.Load("assets/Meteor.spt");
	SetPosition({ static_cast<double>(rand() % (Engine::GetWindow().GetSize().x - 0)) + 0 ,static_cast<double>(rand() % (Engine::GetWindow().GetSize().y - 0)) + 0 });
	SetRotation(static_cast<double>((rand() % 1024 / 1024.) * 2 * PI));
	SetVelocity({ static_cast<double>(rand() % (100 + 100)) - 100 ,static_cast<double>(rand() % (100 + 100)) - 100 });
	SetScale({ ((rand() % 1024) / 4096) + 0.75 , ((rand() % 1024) / 4096) + 0.75 });
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
}

void Meteor::TestForWrap()
{
	if (GetPosition().y > Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0) {
		/*position.y = 0 - sprite.GetFrameSize().y / 2.0;*/
		SetPosition({ GetPosition().x, 0 - sprite.GetFrameSize().y / 2.0 });
	}
	else if (GetPosition().y < 0 - sprite.GetFrameSize().y / 2.0) {
		/*position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;*/
		SetPosition({ GetPosition().x,Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0 });
	}
	if (GetPosition().x > Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0) {
		/*position.x = 0 - sprite.GetFrameSize().x / 2.0;*/
		SetPosition({ 0 - sprite.GetFrameSize().x / 2.0 , GetPosition().y });
	}
	else if (GetPosition().x < 0 - sprite.GetFrameSize().x / 2.0) {
		/*position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;*/
		SetPosition({ Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0 , GetPosition().y });
	}
}



