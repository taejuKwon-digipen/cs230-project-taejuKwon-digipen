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
#include "..\Engine\TransformMatrix.h"

namespace CS230 {
	class Camera;
}

class Hero {
public:
	Hero(math::vec2 startPos, const CS230::Camera& camera);
	void Load();
	void Update(double dt);
	void Draw(math::TransformMatrix cameraMatrix);

	const math::vec2& GetPosition() const { return position; }
private:
    class State {
    public:
        virtual void Enter(Hero* hero) = 0;
        virtual void Update(Hero* hero, double dt) = 0;
        virtual void TestForExit(Hero* hero) = 0;
        virtual std::string GetName() = 0;
    };
    class State_Idle : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Idle"; }
    };
    class State_Running : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Running"; }
    };
    class State_Skidding : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Skidding"; }
    };
    class State_Jumping : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Jumping"; }
    };
    class State_Falling : public State {
    public:
        virtual void Enter(Hero* hero) override;
        virtual void Update(Hero* hero, double dt) override;
        virtual void TestForExit(Hero* hero) override;
        std::string GetName() override { return "Falling"; }
    };
    State_Idle stateIdle;
    State_Running stateRunning;
    State_Skidding stateSkidding;
    State_Jumping stateJumping;
    State_Falling stateFalling;

    void UpdateXVelocity(double dt);
    void ChangeState(State* newState);

    State* currState;
	const CS230::Camera& camera;
	CS230::Sprite sprite;
	math::vec2 startPos;
	math::vec2 position;
	math::vec2 velocity;
	math::TransformMatrix objectMatrix;
	bool isFlipped;

	static constexpr double jumpVelocity = 950;
	static constexpr double xAccel = 500;
	static constexpr double xDrag = 750;
	static constexpr double maxXVelocity = 750;

	CS230::InputKey jumpKey;
	CS230::InputKey moveLeftKey;
	CS230::InputKey moveRightKey;
};