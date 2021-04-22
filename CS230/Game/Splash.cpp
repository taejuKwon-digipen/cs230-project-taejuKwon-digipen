/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Splash.cpp
Project: CS230
Author: Kevin Wright
Creation date: 2/10/2021
-----------------------------------------------------------------*/
#include "../Engine/Engine.h"	//GetGameStateManager
#include "../Engine/TransformMatrix.h"
#include "Screens.h" 
#include "Splash.h"
#include "..\Engine/Texture.h"

Splash::Splash() : texturePtr(nullptr),timer(0.) {}

void Splash::Load() {
	/*texture.Load("assets/DigiPen_BLACK_1024px.png");*/
	texturePtr = Engine::GetTextureManager().Load("assets/DigiPen_BLACK_1024px.png");
	timer = 0;
}

void Splash::Update(double dt) {
	timer += dt;
	if (timer >= DISPLAY_TIME) {
		Engine::Instance().GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
	}
}

void Splash::Unload() {
}
void Splash::Draw() {
	Engine::GetWindow().Clear(0xFFFFFFFF);

	/*texture.Draw(math::TranslateMatrix({ (Engine::GetWindow().GetSize() - texture.GetSize()) / 2.0 }));*/
	texturePtr->Draw(math::TranslateMatrix({ (Engine::GetWindow().GetSize() - texturePtr->GetSize() ) / 2.0 }));
}