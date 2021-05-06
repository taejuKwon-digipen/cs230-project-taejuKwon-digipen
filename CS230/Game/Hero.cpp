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

#include "Gravity.h"
#include "Hero_Anims.h"

Hero::Hero(math::vec2 startPos) :GameObject(startPos), isFlipped(false), jumpKey(CS230::InputKey::Keyboard::Up),
									moveLeftKey(CS230::InputKey::Keyboard::Left), moveRightKey(CS230::InputKey::Keyboard::Right)
{
	AddGOComponent(new CS230::Sprite("assets/Hero.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
}

void Hero::Update(double dt) {
	GameObject::Update(dt);
	// Boundary Check
	if (GetPosition().x < Engine::GetGSComponent<CS230::Camera>()-> GetPosition().x+ GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2) {
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 , GetPosition().y });
		SetVelocity({ 0, GetVelocity().y });
	}
	if (GetPosition().x + GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 > Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
		SetPosition({ Engine::GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - GetGOComponent<CS230::Sprite>()->GetFrameSize().x / 2 , GetPosition().y });
		SetVelocity({ 0,GetVelocity().y });
	}
}

void Hero::State_Idle::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Idle_Anim));

}
void Hero::State_Idle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]]double dt){}

void Hero::State_Idle::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
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

void Hero::State_Running::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Run_Anim));

	if (hero->moveRightKey.IsKeyDown() == true) {
		hero->SetScale({ 1.0, 1 });
	}
	if (hero->moveLeftKey.IsKeyDown() == true) {
		hero->SetScale({ -1.0, 1 });
	}
}
void Hero::State_Running::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	hero->UpdateXVelocity(dt);
}
void Hero::State_Running::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true && hero->GetVelocity().x > 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->moveRightKey.IsKeyDown() == true && hero->GetVelocity().x < 0) {
		hero->ChangeState(&hero->stateSkidding);
	}
	if (hero->GetVelocity().x == 0) {
		hero->ChangeState(&hero->stateIdle);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Skidding::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Skid_Anim));
}
void Hero::State_Skidding::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	
	if (hero->GetVelocity().x > 0) {
		/*hero->velocity.x -= (xDrag + xAccel) * dt;*/
		hero->UpdateVelocity({ -(xDrag + xAccel) * dt , hero->GetVelocity().y });
	}
	else if (hero->GetVelocity().x < 0) {
		/*hero->velocity.x += (xDrag + xAccel) * dt;*/
		hero->UpdateVelocity({ (xDrag + xAccel) * dt , hero->GetVelocity().y });
	}
}
void Hero::State_Skidding::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->moveLeftKey.IsKeyDown() == true) {
		if (hero->GetVelocity().x <= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else if (hero->moveRightKey.IsKeyDown() == true) {
		if (hero->GetVelocity().x >= 0) {
			hero->ChangeState(&hero->stateRunning);
		}
	}
	else {
		hero->ChangeState(&hero->stateRunning);
	}
	if (hero->jumpKey.IsKeyDown() == true) {
		hero->ChangeState(&hero->stateJumping);
	}
}

void Hero::State_Jumping::Enter(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
	/*hero->velocity.y = Hero::jumpVelocity;*/
	hero->SetVelocity({ hero->GetVelocity().x, Hero::jumpVelocity });
}

void Hero::State_Jumping::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	/*hero->velocity.y -= Level1::gravity * dt;*/
	hero->UpdateVelocity(math::vec2{ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}
void Hero::State_Jumping::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->jumpKey.IsKeyDown() == false) {
		hero->ChangeState(&hero->stateFalling);
		/*hero->velocity.y = 0;*/
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
	}
	else if (hero->GetVelocity().y <= 0) {
		hero->ChangeState(&hero->stateFalling);
	}
}

void Hero::State_Falling::Enter(GameObject* object)
{
	Hero* hero = static_cast<Hero*>(object);
	hero->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Hero_Anim::Hero_Jump_Anim));
}

void Hero::State_Falling::Update(GameObject* object, double dt) {
	Hero* hero = static_cast<Hero*>(object);
	/*hero->velocity.y -= Level1::gravity * dt;*/
	hero->UpdateVelocity(math::vec2{ 0,-Engine::GetGSComponent<Gravity>()->GetValue() * dt });
	hero->UpdateXVelocity(dt);
}

void Hero::State_Falling::TestForExit(GameObject* object) {
	Hero* hero = static_cast<Hero*>(object);
	if (hero->GetPosition().y <= Level1::floor) {
		if (hero->GetVelocity().x > 0) {
			if (hero->moveLeftKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else if (hero->GetVelocity().x < 0) {
			if (hero->moveRightKey.IsKeyDown() == true) {
				hero->ChangeState(&hero->stateSkidding);
			} else {
				hero->ChangeState(&hero->stateRunning);
			}
		} else {
			hero->ChangeState(&hero->stateIdle);
		}
		/*hero->velocity.y = 0;*/
		hero->SetVelocity({ hero->GetVelocity().x, 0 });
		/*hero->position.y = Level1::floor;*/
		hero->SetPosition({ hero->GetPosition().x,  Level1::floor });
	}
}

void Hero::UpdateXVelocity(double dt) {
	if (moveLeftKey.IsKeyDown() == true) {
		/*velocity.x -= Hero::xAccel * dt;*/	// apply acceleration
		UpdateVelocity({ -(Hero::xAccel * dt), 0});
		if (GetVelocity().x < -Hero::maxXVelocity) {
			/*velocity.x = -Hero::maxXVelocity;*/
			SetVelocity({ -Hero::maxXVelocity , GetVelocity().y });
		}
	} else if (moveRightKey.IsKeyDown() == true) {
		UpdateVelocity({ (Hero::xAccel * dt), 0 });// apply acceleration
		if (GetVelocity().x > Hero::maxXVelocity) {
			/*velocity.x = Hero::maxXVelocity;*/
			SetVelocity({ Hero::maxXVelocity , GetVelocity().y });
		}
	} else {
		// no key is down, need to apply drag to slow down
		double xDragDt = Hero::xDrag * dt;
		if (GetVelocity().x > xDragDt) {
			/*velocity.x -= xDragDt;*/
			UpdateVelocity({ -xDragDt , 0 });
		} else if (GetVelocity().x < -xDragDt) {
			UpdateVelocity({ xDragDt ,0 });
		} else {
			/*velocity.x = 0;*/
			SetVelocity({ 0, GetVelocity().y });
		}
	}
}