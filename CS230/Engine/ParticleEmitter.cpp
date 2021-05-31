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
	this->life = life;
	GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(0));
	SetPosition(position);
	SetVelocity(velocity);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	life -= dt;
	if(this->IsAlive() == true)
	{
		GameObject::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if(IsAlive()== true)
	{
		GameObject::Draw(matrix);
	}
}

CS230::ParticleEmitter::ParticleEmitter(double lifetime) : lifetime(lifetime){
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
	math::vec2 emit{};
	
	for (int i = 0; i < number; i++)
	{
		const double emitSpread = (rand() % 1024 / 1024. * spread) - spread / 2; //¹üÀ§
		const double speed = ((rand() % 1024) / 2048. + 0.5); //0.5~1.0
		if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
		{
			Engine::GetLogger().LogError("ParticleEmitter Error");
		}
		emit = math::RotateMatrix{ emitSpread }*emitVector + emitterVelocity;
		emit *= speed;
		
		particleMemoryPool[particleIndexToUse]->Revive(position, emit, lifetime);
		if (particleIndexToUse >= static_cast<int>(particleMemoryPool.size()) - 1)
		{
			particleIndexToUse = 0;
		}
		else if (particleIndexToUse < static_cast<int>(particleMemoryPool.size()) - 1)
		{
			particleIndexToUse++;
		}
	}
}




