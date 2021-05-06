/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 3/10/2021
-----------------------------------------------------------------*/
#include "Level1.h"	//Level1::gravity, floor
#include "Ball.h"
#include "Ball_Anims.h"
#include "Gravity.h"
#include "../Engine/Engine.h"

Ball::Ball(math::vec2 startPos) : GameObject(startPos) {
    AddGOComponent(new CS230::Sprite("assets/Ball.spt", this));
    currState = &stateBounce;
    currState->Enter(this);
}

void Ball::State_Bounce::Enter(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::None_Anim));
    ball->SetVelocity({ ball->GetVelocity().x, bounceVelocity }); 
}
void Ball::State_Bounce::Update(GameObject* object, double dt) {
    Ball* ball = static_cast<Ball*>(object);
    ball->UpdateVelocity({ ball->GetVelocity().x, -(Engine::GetGSComponent<Gravity>()->GetValue() * dt) });
}
void Ball::State_Bounce::TestForExit(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetPosition().y < Level1::floor) {
        ball->SetPosition({ ball->GetPosition().x, Level1::floor });
        ball->SetVelocity({ ball->GetVelocity().x, 0 });
        ball->ChangeState(&ball->stateLand);
    }
}

void Ball::State_Land::Enter(GameObject* object)
{
    Ball* ball = static_cast<Ball*>(object);
    ball->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Ball_Anim::Squish_Anim));
}
void Ball::State_Land::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt){}

void Ball::State_Land::TestForExit(GameObject* object) {
    Ball* ball = static_cast<Ball*>(object);
    if (ball->GetGOComponent<CS230::Sprite>()->IsAnimationDone() == true) {
        {
            ball->ChangeState(&ball->stateBounce);
        }
    }
}
