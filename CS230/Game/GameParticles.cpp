/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 5/27/2021
-----------------------------------------------------------------*/
#include "GameParticles.h"

SmokeEmitter::SmokeParticle::SmokeParticle(std::string spriteFile): CS230::ParticleEmitter::Particle(spriteFile)
{
	AddGOComponent(new CS230::ParticleEmitter(1.0));
}

HitEmitter::HitParticle::HitParticle(std::string spriteFile): CS230::ParticleEmitter::Particle(spriteFile)
{
	AddGOComponent(new CS230::ParticleEmitter(1.0));
}

MeteorBitEmitter::MeteorBit::MeteorBit(std::string spriteFile): CS230::ParticleEmitter::Particle(spriteFile)
{
	AddGOComponent(new CS230::ParticleEmitter(1.5));
}
