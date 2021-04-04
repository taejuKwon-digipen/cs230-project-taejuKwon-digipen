/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "TransformMatrix.h"

namespace CS230 {
	class Camera {
	public:
		Camera(math::rect2 movableRange);
		void SetPosition(math::vec2 newPosition);
		const math::vec2& GetPosition() const; 
		void SetExtent(math::irect2 newExtent); 
		void Update(const math::vec2& followObjPos);
		math::TransformMatrix GetMatrix();
	
	private:
		math::irect2 extent;//범위
		math::vec2 position;//위치
		math::rect2 movableRange;//카메라 안에 있는 object가 움직일 수있는 범위
	};
}


