
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Bunny.cpp
Project: CS230
Author: Taeju Kwon
Creation date: 2/15/2021
-----------------------------------------------------------------*/

#include "Bunny.h"
 
Bunny::Bunny(math::vec2 pos) : GameObject(pos) {

	sprite.Load("assets/Bunny.spt");
	
}

