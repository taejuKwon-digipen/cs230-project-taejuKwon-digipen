#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Rect.h
Author: Taeju Kwon
Creation date: 2021.03.31
-----------------------------------------------------------------*/
#pragma once

#include <cmath>

using namespace std;

namespace math
{
    struct [[nodiscard]] rect2
    {
        vec2 bottom_left{ 0,0 };
        vec2 top_right{ 0,0 };

    };

    struct [[nodiscard]] irect2
    {
        ivec2 bottom_left{ 0,0 };
        ivec2 top_right{ 0,0 };
    };

}
