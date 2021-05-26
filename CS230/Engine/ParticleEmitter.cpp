/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/26/2021
-----------------------------------------------------------------*/

#include "ParticleEmitter.h"
#include "Sprite.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile)
{
	AddGOComponent(new CS230::Sprite(spriteFile, this) );
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 position, math::vec2 velocity, double life)
{
	AddGOComponent(new CS230::ParticleEmitter(life));
	/*GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Meteor_Anim::None_Anim));*/
	SetPosition(position);
	SetVelocity(velocity);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if(this->IsAlive() == true)
	{
		GetGOComponent<Particle>()->Update(life); //?이상한데 일단 넣어봄
		Particle::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if(IsAlive()== true)
	{
		GetGOComponent<Particle>()->Draw(matrix);
	}
}

CS230::ParticleEmitter::ParticleEmitter(double lifetime)
{
	Engine::GetGSComponent<>()
}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(particleData);
	
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	for(int i = 0; i < number; i++)
	{
		/*if(i == particleIndexToUse)
		{
			Engine::GetLogger().LogError("ParticleEmitter Error");	
		}*/
	}
	
	double angle = (rand() % static_cast<int>(((-spread / 2) + spread / 2)));
	emitterVelocity = math::RotateMatrix{ angle } * emitVector;
}




