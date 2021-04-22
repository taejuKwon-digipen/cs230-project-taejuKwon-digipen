/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Project: CS230
Author: Kevin Wright
Creation date: 2/12/2021
-----------------------------------------------------------------*/
#pragma once
#include "Vec2.h"
 
namespace math {
    struct [[nodiscard]] rect2 {
        vec2 bottomLeft{ 0.0, 0.0 };
        vec2 topRight{ 0.0, 0.0 };
    };
    struct [[nodiscard]] irect2 {
        ivec2 bottomLeft{ 0, 0 };
        ivec2 topRight{ 0, 0 };
    };
}
