/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"  //GetLogger
#include "Level1.h"	//Level1::gravity, floor
#include "Ball.h"

Ball::Ball(math::vec2 startPos) : initPosition(startPos), velocity({ 0,0 }), currState(&stateLand) {}

void Ball::Load() {
	sprite.Load("assets/Ball.png", { 43, 0 });
	position = initPosition;
    velocity = { 0, 0 };
    currState = &stateLand;
    currState->Enter(this);
}

void Ball::Update(double dt) {
    currState->Update(this, dt);
    position += velocity * dt;
    currState->TestForExit(this);

	objectMatrix = math::TranslateMatrix(position);
}

void Ball::Draw(math::TransformMatrix cameraMatrix) {
	sprite.Draw(cameraMatrix * objectMatrix);
}

void Ball::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Ball Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
    currState = newState;
    currState->Enter(this);
}

void Ball::State_Bounce::Enter(Ball* ball) {
    ball->velocity.y = Ball::bounceVelocity;
}
void Ball::State_Bounce::Update(Ball* ball, double dt) {
    ball->velocity.y -= Level1::gravity * dt;
}
void Ball::State_Bounce::TestForExit(Ball* ball) {
    if (ball->position.y < Level1::floor) {
        ball->position.y = Level1::floor;
        ball->velocity.y = 0;
        ball->ChangeState(&ball->stateLand);
    }
}

void Ball::State_Land::Enter(Ball*) { }
void Ball::State_Land::Update([[maybe_unused]] Ball* ball, [[maybe_unused]] double dt) {}
void Ball::State_Land::TestForExit(Ball* ball) {
	ball->ChangeState(&ball->stateBounce);
}