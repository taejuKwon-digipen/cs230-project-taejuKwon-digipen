/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ScreenWrap.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/17/2021
-----------------------------------------------------------------*/

#include "ScreenWrap.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"

void ScreenWrap::Update([[maybe_unused]]double dt)
{
	if (object.GetPosition().y > Engine::GetWindow().GetSize().y + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) {
		/*position.y = 0 - sprite.GetFrameSize().y / 2.0;*/
		object.SetPosition({ object.GetPosition().x, 0 - object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 });
	}
	else if (object.GetPosition().y < 0 - object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0) {
		/*position.y = Engine::GetWindow().GetSize().y + sprite.GetFrameSize().y / 2.0;*/
		object.SetPosition({ object.GetPosition().x,Engine::GetWindow().GetSize().y + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().y / 2.0 });
	}
	if (object.GetPosition().x > Engine::GetWindow().GetSize().x + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) {
		/*position.x = 0 - sprite.GetFrameSize().x / 2.0;*/
		object.SetPosition({ 0 - object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 , object.GetPosition().y });
	}
	else if (object.GetPosition().x < 0 - object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0) {
		/*position.x = Engine::GetWindow().GetSize().x + sprite.GetFrameSize().x / 2.0;*/
		object.SetPosition({ Engine::GetWindow().GetSize().x + object.GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2.0 , object.GetPosition().y });
	}
}
