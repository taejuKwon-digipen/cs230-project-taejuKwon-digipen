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
#include "ScreenWrap.h"
#include "../Engine/Engine.h" 

Meteor::Meteor() : GameObject({ 0,0 }) {
	AddGOComponent(new ScreenWrap(*this));
	constexpr double PI = 3.1415926535;
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	SetPosition({ static_cast<double>(rand() % (Engine::GetWindow().GetSize().x - 0)) + 0 ,static_cast<double>(rand() % (Engine::GetWindow().GetSize().y - 0)) + 0 });
	SetRotation(static_cast<double>((rand() % 1024 / 1024.) * 2 * PI));
	SetVelocity({ static_cast<double>(rand() % (100 + 100)) - 100 ,static_cast<double>(rand() % (100 + 100)) - 100 });
	SetScale({ ((rand() % 1024) / 4096) + 0.75 , ((rand() % 1024) / 4096) + 0.75 });
}

void Meteor::Update(double dt)
{
	GameObject::Update(dt);
	GetGOComponent<ScreenWrap>()->Update(dt);
}




