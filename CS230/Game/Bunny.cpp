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
#include "Hero.h"

Bunny::Bunny(math::vec2 pos, std::vector<double> patrolNodes, Hero* heroPtr): GameObject(pos) , currPatrolNode(0), patrolNodes(patrolNodes), heroPtr(heroPtr){
	AddGOComponent(new CS230::Sprite("assets/Bunny.spt", this));
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));
	ChangeState(&statePatrol);
	currState->Enter(this);
}

void Bunny::ResolveCollision(CS230::GameObject* objectA)
{
    if (objectA->GetObjectType() == GameObjectType::Hero) {
        ChangeState(&stateDead);
    }
}

void Bunny::State_Patrol::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Walk_Anim));

	if (bunny->patrolNodes[bunny->currPatrolNode] > bunny->GetPosition().x)
	{
		bunny->SetScale({ 1,1 });
		bunny->SetVelocity({ velocity,0 });
	}
	else if (bunny->patrolNodes[bunny->currPatrolNode] < bunny->GetPosition().x)
	{
		bunny->SetScale({ -1,1 });
		bunny->SetVelocity({ -velocity,0 });
	}
}

void Bunny::State_Patrol::Update(GameObject* object, double dt)
{
	 Bunny* bunny = static_cast<Bunny*>(object);

	 if (bunny->GetPosition().x > bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x > 0)
	 {
		 if (bunny->currPatrolNode == bunny->patrolNodes.size() - 1)
		 {
			 bunny->currPatrolNode--;
			 bunny->ChangeState(this);
		 }
	 }

	 else if (bunny->GetPosition().x < bunny->patrolNodes[bunny->currPatrolNode] && bunny->GetVelocity().x < 0)
	 {
		 if (bunny->currPatrolNode == 0) 
		 {
			 bunny->currPatrolNode++;
			 bunny->ChangeState(this);
		 }
	 }
}

void Bunny::State_Patrol::TestForExit(GameObject* object )
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if(bunny->heroPtr->GetPosition().y == bunny->GetPosition().y )
	{
		if(bunny->GetVelocity().x < 0)
		{
			if(bunny->heroPtr->GetPosition().x < bunny->GetPosition().x)
			{
				if(bunny->patrolNodes[bunny->currPatrolNode] < bunny->heroPtr->GetPosition().x)
				{
					bunny->ChangeState(&bunny->stateAttack);
				}
			}
		}
		else if( bunny->GetVelocity().x > 0)
		{
			if (bunny->heroPtr->GetPosition().x > bunny->GetPosition().x)
			{
				if (bunny->patrolNodes[bunny->currPatrolNode] > bunny->heroPtr->GetPosition().x)
				{
					bunny->ChangeState(&bunny->stateAttack);
				}
			}
		}
	}
	
}

void Bunny::State_Attack::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->SetVelocity({ bunny->GetVelocity().x * 2., 0 });
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Attack_Anim));
}


void Bunny::State_Attack::Update(GameObject* object, double dt)
{
	Bunny* bunny = static_cast<Bunny*>(object);

	if(bunny->GetVelocity().x > 0)
	{
		if(bunny->GetPosition().x >= bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->currPatrolNode--;
			bunny->ChangeState(&bunny->statePatrol);
		}
	}
	else if( bunny->GetVelocity().x < 0)
	{
		if (bunny->GetPosition().x <= bunny->patrolNodes[bunny->currPatrolNode])
		{
			bunny->currPatrolNode++;
			bunny->ChangeState(&bunny->statePatrol);
		}
	}
}


void Bunny::State_Attack::TestForExit(GameObject* object)
{
	[[maybe_unused]] Bunny* bunny = static_cast<Bunny*>(object);
	
}


void Bunny::State_Dead::Enter(GameObject* object)
{
	Bunny* bunny = static_cast<Bunny*>(object);
	bunny->RemoveGOComponent<CS230::Collision>();
	bunny->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Bunny_Anim::Dead_Anim));
	bunny->SetVelocity({ 0,0 });
}


void Bunny::State_Dead::TestForExit(GameObject* object)
{
	[[maybe_unused]] Bunny* bunny = static_cast<Bunny*>(object);
	
}


void Bunny::State_Dead::Update(GameObject* object, double dt)
{
	[[maybe_unused]] Bunny* bunny = static_cast<Bunny*>(object);
	
}









	