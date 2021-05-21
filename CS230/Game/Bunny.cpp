
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "Bunny.h"
#include "Bunny_Anims.h"
#include "GameObjectTypes.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "../Engine/Engine.h"

Bunny::Bunny(math::vec2 pos) : GameObject(pos) {

	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
	this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::None_Anim));
}

void Bunny::ResolveCollision(GameObject* objectA)
{
	/*if (objectA->DoesCollideWith(this) == true)
	{*/
	if (objectA->GetObjectType() == GameObjectType::Hero)
	{
		this->RemoveGOComponent<CS230::Collision>();
		this->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
		Engine::GetGSComponent<Score>()->AddScore(100);
	};
	//}
}


