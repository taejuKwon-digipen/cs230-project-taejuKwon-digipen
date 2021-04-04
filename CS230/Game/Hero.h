/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Hero.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "..\Engine\Sprite.h"
#include "..\Engine\Input.h"
#include "..\Engine\Vec2.h"
#include "..\Engine/Camera.h"

class Hero {
public:
    Hero(math::vec2 startPos, const CS230::Camera& camera);
    void Load();
    void Update(double dt);
    void Draw(math::TransformMatrix cameraMatrix);
    math::vec2 Getposition() { return position; }

private:
    CS230::Sprite sprite;
    math::vec2 startPos;
    math::vec2 position;
    math::vec2 velocity = { 0,0 };

    const CS230::Camera& camera;
	
    static constexpr double xAccel = 700; //가속 
    static constexpr double xDrag = 1000; //마찰력
    static constexpr double xMVelo = 1400; //최고속도
	
    static constexpr double jumpVelocity = 1300;

    math::TransformMatrix objectMatrix;

    CS230::InputKey moveLeftKey;
    CS230::InputKey moveRightKey;
    CS230::InputKey moveJumpKey;

    bool isJumping ; //중력을 가할 때 사용
    bool isRising ; //올라갔을때
};

