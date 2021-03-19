/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Project: CS230
Author: Taeju Kwon
Creation date:  2/10/2021
-----------------------------------------------------------------*/
#include "Engine.h"

Engine::Engine() : lastTick(std::chrono::system_clock::now()), frameCount(0),
#ifdef _DEBUG				
    logger(CS230::Logger::Severity::Debug, true)
#else 						
    logger(CS230::Logger::Severity::Event, false)
#endif
{}

Engine::~Engine() {};

void Engine::Init(std::string windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	fpsCalcTime = lastTick;
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update()
{
	double dt = std::chrono::duration<double>(std::chrono::system_clock::now() - lastTick).count();
	
	if(dt > 1 / Target_FPS)
	{
		frameCount++;
		logger.LogVerbose("Engine Update");
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
		lastTick = std::chrono::system_clock::now();
	}
	if (frameCount >= FPS_IntervalFrameCount)
	{
		const double countAvarageFPS = frameCount / std::chrono::duration<double>(lastTick - fpsCalcTime).count();
		logger.LogEvent("FPS: "+ std::to_string(countAvarageFPS));
		fpsCalcTime = lastTick;
		frameCount = 0;
	}
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}
