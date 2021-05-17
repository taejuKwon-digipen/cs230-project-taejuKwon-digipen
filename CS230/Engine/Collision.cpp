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


bool CS230::RectCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    math::rect2 MyRectCollision = this->GetWorldCoorRect();
    math::rect2 TestRectCollision = testAgainstObject->GetGOComponent<RectCollision>()->GetWorldCoorRect();

    if (MyRectCollision.Left() < TestRectCollision.Right() && MyRectCollision.Right() > TestRectCollision.Left() && MyRectCollision.Bottom() < TestRectCollision.Top() && MyRectCollision.Top() > TestRectCollision.Bottom())
    {
        return true;
    }
    return false;
}
double CS230::CircleCollision::GetRadius()
{
    return objectPtr->GetScale().x * radius;
}

bool CS230::CircleCollision::DoesCollideWith(GameObject* testAgainstObject)
{
    if ((this->objectPtr->GetPosition().x - testAgainstObject->GetPosition().x) * (this->objectPtr->GetPosition().x - testAgainstObject->GetPosition().x) + (this->objectPtr->GetPosition().y - testAgainstObject->GetPosition().y) * (this->objectPtr->GetPosition().y - testAgainstObject->GetPosition().y) < (this->GetRadius() + testAgainstObject->GetGOComponent<CircleCollision>()->GetRadius()) * (this->GetRadius() + testAgainstObject->GetGOComponent<CircleCollision>()->GetRadius()))
    {
        return true;
    }
    return false;
}
