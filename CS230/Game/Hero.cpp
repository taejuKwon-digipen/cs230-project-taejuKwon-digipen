/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetLogger
#include "../Engine/Camera.h"
#include "Level1.h"	//Level1::gravity
#include "Hero.h"
#include "Hero_Anims.h"

Hero::Hero(math::vec2 startPos, const CS230::Camera& camera) : startPos(startPos), camera(camera),
									currState(&stateIdle), jumpKey(CS230::InputKey::Keyboard::Up),
									moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right) {
}

void Hero::Load() {
	sprite.Load("assets/Hero.spt");
	position = startPos;
	velocity = { 0,0 };
	isFlipped = false;
	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt) {
	currState->Update(this, dt);
	position += velocity * dt;
	currState->TestForExit(this);
	sprite.Update(dt);

	// Boundary Check
	if (position.x < camera.GetPosition().x + sprite.GetFrameSize().x / 2) {
		position.x = camera.GetPosition().x + sprite.GetFrameSize().x / 2;
		velocity.x = 0;
	}
	if (position.x + sprite.GetFrameSize().x / 2 > camera.GetPosition().x + Engine::GetWindow().GetSize().x) {
		position.x = camera.GetPosition().x + Engine::GetWindow().GetSize().x - sprite.GetFrameSize().x / 2;
		velocity.x = 0;
	}
	objectMatrix = math::TranslateMatrix(position);
	if (isFlipped == true) {
		objectMatrix *= math::ScaleMatrix({ -1.0, 1 });
	}
}

void Hero::Draw(math::TransformMatrix cameraMatrix) {
	sprite.Draw(cameraMatrix * objectMatrix);
}

void Hero::ChangeState(State* newState) {
	Engine::GetLogger().LogDebug("Hero Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}


void Hero::State_Idle::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));
}
void Hero::State_Idle::Update(Hero*, double)
{
	
}
void Hero::State_Idle::TestForExit(Hero* hero) {
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Running::Enter(Hero* hero) {

	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));
	
	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->isFlipped = false;
	}
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->isFlipped = true;
	}
}
void Hero::State_Running::Update(Hero* hero, double dt) {
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(Hero* hero) {
	if (hero->moveLeftKey.IsKeyDown() == true && hero->velocity.x > 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->velocity.x < 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->velocity.x == 0) {
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Skidding::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(Hero* hero, double dt) {
	
	if (hero->velocity.x > 0) {
		hero->velocity.x -= (xDrag + xAccel) * dt;
	} else if (hero->velocity.x < 0) {
		hero->velocity.x += (xDrag + xAccel) * dt;
	}
}
void Hero::State_Skidding::TestForExit(Hero* hero) {
	if (hero->moveLeftKey.IsKeyDown() == true) {
		if (hero->velocity.x <= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else if (hero->moveRightKey.IsKeyDown() == true) {
		if (hero->velocity.x >= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	} else {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(Hero* hero) {
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	hero->velocity.y = Hero::jumpVelocity;
}
void Hero::State_Jumping::Update(Hero* hero, double dt) {
	hero->velocity.y -= Level1::gravity * dt;
	hero->UpdateXVelocity(dt);
}
void Hero::State_Jumping::TestForExit(Hero* hero) {
	if (hero->jumpKey.IsKeyDown() == false) {
		hero->ChangeState(&hero->stateFalling);
		hero->velocity.y = 0;
	} else if (hero->velocity.y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(Hero* hero)
{
	hero->sprite.PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
}
void Hero::State_Falling::Update(Hero* hero, double dt) {
	hero->velocity.y -= Level1::gravity * dt;
	hero->UpdateXVelocity(dt);
}
void Hero::State_Falling::TestForExit(Hero* hero) {
	if (hero->GetPosition().y <= Level1::floor) {
		if (hero->velocity.x > 0) {
			if (hero->moveLeftKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else if (hero->velocity.x < 0) {
			if (hero->moveRightKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else {
			hero->ChangeState(&hero->stateIdle);
		}
		hero->velocity.y = 0;

		hero->position.y = Level1::floor;
	}
}

void Hero::UpdateXVelocity(double dt) {
	if (moveLeftKey.IsKeyDown() == true) {
		velocity.x -= Hero::xAccel * dt;	// apply acceleration
		if (velocity.x < -Hero::maxXVelocity) {
			velocity.x = -Hero::maxXVelocity;
		}
	} else if (moveRightKey.IsKeyDown() == true) {
		velocity.x += Hero::xAccel * dt;	// apply acceleration
		if (velocity.x > Hero::maxXVelocity) {
			velocity.x = Hero::maxXVelocity;
		}
	} else {
		// no key is down, need to apply drag to slow down
		double xDragDt = Hero::xDrag * dt;
		if (velocity.x > xDragDt) {
			velocity.x -= xDragDt;
		} else if (velocity.x < -xDragDt) {
			velocity.x += xDragDt;
		} else {
			velocity.x = 0;
		}
	}
}