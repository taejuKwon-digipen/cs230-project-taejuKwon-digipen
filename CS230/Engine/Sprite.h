/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <filesystem>
#include <vector>
#include "Vec2.h"

namespace math {
	class TransformMatrix;
}

namespace CS230
{
	class Texture;
	class Animation;
}

namespace CS230 {

	class Sprite {
	public:
		Sprite();
		~Sprite();
		
		void Load(const std::filesystem::path& spriteInfoFile);
		void Draw(math::TransformMatrix displayMatrix);
		void PlayAnimation(int anim);
		void Update(double dt);
		bool IsAnimationDone();

		math::ivec2 GetHotSpot(int index);
		math::ivec2 GetFrameSize() const;

	private:

		math::ivec2 GetFrameTexel(int frameNum) const;

		int currAnim;
		std::vector<Animation*> animations;

		Texture* texturePtr;
		int currFrame;
		math::ivec2 frameSize;
		std::vector<math::ivec2> frameTexel;
		std::vector<math::ivec2> hotSpotList;
	};
}