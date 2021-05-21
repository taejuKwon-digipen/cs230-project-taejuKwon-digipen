
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Project: CS230
Author: Kevin Wright
Creation date: 2/14/2021
-----------------------------------------------------------------*/
#pragma once

#include "..\Engine\ComponentManager.h"
#include "..\Engine\Vec2.h"
#include "..\Engine\Sprite.h"
#include "..\Engine\TransformMatrix.h"
#include "ShowCollision.h"
#include "Collision.h"
enum class GameObjectType;
namespace CS230 {
	  
	class Component;
	
	class GameObject {
		friend class Sprite;
		
	public:
		GameObject(math::vec2 position); //hero
		GameObject(math::vec2 position, double rotation, math::vec2 scale); //ship
		virtual ~GameObject()
		{
			ClearGOComponents();
		}

		virtual void ResolveCollision(GameObject*);
		
		virtual void Update(double dt);
		virtual void Draw(math::TransformMatrix cameraMatrix);

		void SetPosition(math::vec2 newPosition);

		const math::TransformMatrix& GetMatrix();
		const math::vec2& GetPosition() const;
		const math::vec2& GetVelocity() const;
		const math::vec2& GetScale() const;
		double GetRotation() const;

		template<typename T>
		T* GetGOComponent() { return components.GetComponent<T>(); }

		virtual GameObjectType GetObjectType() = 0;
		virtual std::string GetObjectTypeName() = 0;
		virtual bool CanCollideWith(GameObjectType objectBType);
		bool DoesCollideWith(math::vec2 point);
		bool DoesCollideWith(GameObject* objectB);

	protected:
		void UpdatePosition(math::vec2 adjustPosition);
		void SetVelocity(math::vec2 newPosition);
		void UpdateVelocity(math::vec2 adjustPosition);
		void SetScale(math::vec2 newScale);
		void SetRotation(double newRotationAmount);
		void UpdateRotation(double newRotationAmount);

		void AddGOComponent(Component* component) { components.AddComponent(component); }
		void UpdateGOComponents(double dt) { components.UpdateAll(dt); }
		void ClearGOComponents() { components.Clear(); }
		
		template<typename T>
		void RemoveGOComponent() { components.RemoveComponent<T>(); }

		class State {
		public:
			virtual void Enter(GameObject* object) = 0;
			virtual void Update(GameObject* object, double dt) = 0;
			virtual void TestForExit(GameObject* object) = 0;
			virtual std::string GetName() = 0;
		};
		class State_Nothing : public State {
		public:
			void Enter(GameObject*) override {}
			void Update(GameObject*, double) override {}
			void TestForExit(GameObject*) override {}
			std::string GetName() { return ""; }
		};

		State_Nothing state_nothing;
		void ChangeState(State* newState);
		State* currState;
		ShowCollision* show;
	
	private:
		math::TransformMatrix objectMatrix;
		bool updateMatrix;
		ComponentManager components;

		double rotation;
		math::vec2 scale;
		math::vec2 position;
		math::vec2 velocity;


	};
}

