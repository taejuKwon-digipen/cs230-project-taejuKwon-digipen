/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "Score.h"
#include "Bunny.h"
#include "Bunny_Anims.h"

Bunny::Bunny(math::vec2 pos) : GameObject(pos) {
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::None_Anim));
}

void Bunny::ResolveCollision(CS230::GameObject* objectA) {
    if (objectA->GetObjectType() == GameObjectType::Hero) {
        RemoveGOComponent<CS230::Collision>();
        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
        Engine::GetGSComponent<Score>()->AddScore(100);
    }
}