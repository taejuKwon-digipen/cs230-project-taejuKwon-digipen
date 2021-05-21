/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 17/4/2021
-----------------------------------------------------------------*/
#include"GameObjectManager.h"
#include"GameObject.h"   // gameobject
#include"TransformMatrix.h"  //TransformMatrix
#include"Engine.h"
void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

CS230::GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::CollideTest()
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(gameObjects.size()); j++)
		{
			if (gameObjects[i]->CanCollideWith(gameObjects[j]->GetObjectType()) == true && gameObjects[i] != gameObjects[j])
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

void CS230::GameObjectManager::Update(double dt)
{
	for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
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