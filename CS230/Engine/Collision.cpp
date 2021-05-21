/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Collision.cpp
Project: CS230
Author: taeju Kwon
Creation date: 2/12/2021
-----------------------------------------------------------------*/

#include "Collision.h"
#include <doodle/drawing.hpp>
#include "GameObject.h"
#include "TransformMatrix.h"

void CS230::RectCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();
}

void CS230::CircleCollision::Draw(math::TransformMatrix cameraMatrix) {
    doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();
}

math::rect2 CS230::RectCollision::GetWorldCoorRect()
{
    math::rect2 RectCollision;
    RectCollision.point1 = math::TransformMatrix(objectPtr->GetMatrix()) * static_cast<math::vec2>(rect.point1);
    RectCollision.point2 = math::TransformMatrix(objectPtr->GetMatrix()) * static_cast<math::vec2>(rect.point2);
    return RectCollision;
}


bool CS230::RectCollision::DoesCollideWith(math::vec2 point)
{
    math::rect2 MyRectCollision = this->GetWorldCoorRect();
   
	if(MyRectCollision.Left() <= point.x && MyRectCollision.Right() >= point.x && MyRectCollision.Bottom() <= point.y && MyRectCollision.Top() >= point.y)
	{
        return true;
	}
    return false;
}

bool CS230::RectCollision::DoesCollideWith(GameObject* objectB)
{
    if (this->GetWorldCoorRect().Left() < objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Right() &&
        this->GetWorldCoorRect().Right() > objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Left() &&
        this->GetWorldCoorRect().Bottom() < objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Top() &&
        this->GetWorldCoorRect().Top() > objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Bottom())
    {
        return true;
    }
    return false;
};

double CS230::CircleCollision::GetRadius()
{
    return objectPtr->GetScale().x * radius;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* objectB)
{
    if ((this->GetRadius() + objectB->GetGOComponent<CircleCollision>()->GetRadius()) * 2 >
        (objectB->GetPosition().x + objectPtr->GetPosition().x) * (objectB->GetPosition().x + objectPtr->GetPosition().x)
        + (objectB->GetPosition().y + objectPtr->GetPosition().y) * (objectB->GetPosition().y + objectPtr->GetPosition().y))
    {
        return true;
    }
    return false;
}


bool CS230::CircleCollision::DoesCollideWith(math::vec2 point)
{
    if (this->objectPtr->GetPosition().x == point.x && this->objectPtr->GetPosition().y == point.y)
    {
        return true;
    }
        return false;
	
}
