/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 3/31/2021
-----------------------------------------------------------------*/
#include "Camera.h"
#include "TransformMatrix.h"

CS230::Camera::Camera(math::rect2 movableRange) : movableRange(movableRange){};

void CS230::Camera::SetPosition(math::vec2 newPosition)
{
	position = newPosition;
}

void CS230::Camera::SetExtent(math::irect2 newExtent)
{
	extent = newExtent;
}

void CS230::Camera::Update(const math::vec2& followObjPos)
{
    if (followObjPos.x - position.x > movableRange.top_right.x)
    {
        position.x = followObjPos.x - movableRange.top_right.x;
    }
    else if (followObjPos.x - position.x < movableRange.bottom_left.x)
    {
        position.x = followObjPos.x - movableRange.bottom_left.x;
    }
    if (extent.bottom_left.x > position.x)
    {
        position.x = extent.bottom_left.x;
    }
    else if (extent.top_right.x < position.x)
    {
        position.x = extent.top_right.x;
    }
}

const math::vec2& CS230::Camera::GetPosition() const
{
	return position;
}

math::TransformMatrix CS230::Camera::GetMatrix()
{
     return math::TranslateMatrix(math::vec2(-position));
}







