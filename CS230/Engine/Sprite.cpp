/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#include "Engine.h"			//Engine::GetLogger
#include "TransformMatrix.h"
#include "Sprite.h"

CS230::Sprite::Sprite() {}

void CS230::Sprite::Load(const std::filesystem::path& texturePath) {
	texture.Load(texturePath);
	hotSpotList.push_back({ GetTextureSize() / 2 });
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotspot) {
	texture.Load(texturePath);
	hotSpotList.push_back(hotspot);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots) {
	texture.Load(texturePath);
	for (math::ivec2 hotspot : hotspots) {
		hotSpotList.push_back(hotspot);
	}
}

math::ivec2 CS230::Sprite::GetTextureSize() {
	return texture.GetSize();
}

math::ivec2 CS230::Sprite::GetHotSpot(int index) {
	if (index >= hotSpotList.size()) {
		Engine::GetLogger().LogError("Sprite is missing hotspot index: " + std::to_string(index));
		return { 0,0 };
	}
	return hotSpotList[index];
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix) {
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)));
}