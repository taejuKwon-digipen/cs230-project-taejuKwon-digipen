/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Floor.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 17/5/2021
-----------------------------------------------------------------*/

#include "Floor.h"
#include "../Engine/Collision.h"

Floor::Floor(math::irect2 rect) : GameObject(math::vec2{ rect.point1 })
{
	AddGOComponent(new CS230::RectCollision(math::irect2{{0,0}, rect.Size()}, this));
}


