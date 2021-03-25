/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Ball.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/26/2021
-----------------------------------------------------------------*/

#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Vec2.h"
#include "Ball.h"

class Ball {
public:
    Ball(math::vec2 startPos);
    void Load();
    void Update(double dt);
    void Draw();

private:
    CS230::Sprite sprite;
    math::vec2 initPosition;
    math::vec2 position;
    math::vec2 velocity;

    static constexpr double bounceVelocity = 250;

	
};

