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
#include "TransformMatrix.h" 
#include "GameObject.h"

void CS230::GameObjectManager::Add(GameObject* obj)
{
	gameObjects.push_back(obj);
}

void CS230::GameObjectManager::Unload()
{
	for(int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void CS230::GameObjectManager::UpdateAll(double dt)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update((dt));
	}
}

void CS230::GameObjectManager::DrawAll(math::TransformMatrix& cameraMatrix)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Draw(cameraMatrix);
	}
}





