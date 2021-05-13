/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 17/4/2021
-----------------------------------------------------------------*/
#include "GameObjectManager.h"
#include "Engine.h"
#include "TransformMatrix.h" 
#include "GameObject.h"

CS230::GameObjectManager::~GameObjectManager()
{
	for (GameObject*& index : gameObjects)
	{
		delete index;
	}
	gameObjects.clear();
}

	void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Update(double dt)
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()-1); i++)
	{
		gameObjects[i]->Update(dt);
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		gameObjects[i]->Draw(cameraMatrix);
	}
}

void CS230::GameObjectManager::CollideTest()
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(gameObjects.size()); j++)
		{
			if (gameObjects[i]->CanCollideWith(gameObjects[j]->GetObjectType()) == true)
			{
				if (gameObjects[i]->DoesCollideWith(gameObjects[j]) == true)
				{
					Engine::GetLogger().LogEvent("Collision Detected : " + gameObjects[i]->GetObjectTypeName() + " and " + gameObjects[j]->GetObjectTypeName());
					gameObjects[i]->ResolveCollision(gameObjects[j]);
				}
			}
		}
	}


}





