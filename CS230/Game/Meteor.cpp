/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Meteor.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Collision.h"
#include "Meteor.h"
#include "Score.h"
#include "ScreenWrap.h"
#include "Meteor_Anims.h"
#include "GameParticles.h"

constexpr double PI = 3.1415926535897932384626433832795;

Meteor::Meteor() : GameObject({ 0,0 }), health(100), size(1) {
	AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
	AddGOComponent(new ScreenWrap(*this));

	math::vec2 newPosition = { static_cast<double>(rand() % Engine::GetWindow().GetSize().x),
							static_cast<double>(rand() % Engine::GetWindow().GetSize().y) };
	SetPosition(newPosition);
	SetRotation((rand() % static_cast<int>(2 * PI * 1024)) / 1024.0f);
	SetVelocity({ 100 - static_cast<double> (rand() % 200), 100 - static_cast<double> (rand() % 200) });
	double scaleAmount = (rand() % 1024) / 4096.0 + .75;
	SetScale({ scaleAmount, scaleAmount });
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
}

Meteor::Meteor(Meteor& original) : GameObject(original.GetPosition()), size(original.size + 1), health(100) {
    AddGOComponent(new CS230::Sprite("assets/Meteor.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));
    AddGOComponent(new ScreenWrap(*this));

    double scaleAmount = 1;
    switch (size) {
    case 2:
        scaleAmount = (rand() % 1024) / 4096.0 + .50;
        break;
    case 3:
        scaleAmount = (rand() % 1024) / 4096.0 + .25;
        break;
    }
    SetScale({ scaleAmount, scaleAmount });
}

void Meteor::Update(double dt) {
    GameObject::Update(dt);
    if ((static_cast<Meteor_Anim>(GetGOComponent<CS230::Sprite>()->GetCurrentAnim()) == Meteor_Anim::Fade_Anim) &&
        GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) {
        Destroy();
    }
}

void Meteor::ResolveCollision(GameObject* objectB) {
    math::vec2 vectorToObject{};
    math::vec2 collisionPoint{};
    math::vec2 blueVector{};
	
    switch (objectB->GetObjectType())
    {
    case GameObjectType::Laser:
        health -= 10;
		vectorToObject = math::vec2{ objectB->GetPosition() - this->GetPosition() }.Normalize();
		collisionPoint = vectorToObject * GetGOComponent<CS230::CircleCollision>()->GetRadius() + this->GetPosition();
        blueVector = vectorToObject * 2 + math::vec2{ objectB->GetVelocity() }.Normalize();
        Engine::GetGSComponent<HitEmitter>()->Emit(1, collisionPoint, GetVelocity(), { 0,0 }, 0);
        Engine::GetGSComponent<MeteorBitEmitter>()->Emit(10, collisionPoint, GetVelocity(), blueVector * 50, PI / 2);
        break;
    }
     
    if (health <= 0) {
        if (size < 3) {
            Meteor* newMeteorA = new Meteor(*this);
            newMeteorA->SetVelocity(math::RotateMatrix(PI / 6) * GetVelocity());
            Meteor* newMeteorB = new Meteor(*this);
            newMeteorB->SetVelocity(math::RotateMatrix(-PI / 6) * GetVelocity());
            Engine::GetGSComponent<CS230::GameObjectManager>()->Add(newMeteorA);
            Engine::GetGSComponent<CS230::GameObjectManager>()->Add(newMeteorB);
        }

        GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::Fade_Anim));
        RemoveGOComponent<CS230::Collision>();
        Engine::GetGSComponent<Score>()->AddScore(100 * size);
    }
    else
    {
        UpdateVelocity(objectB->GetVelocity() * 0.01);
    }
} 