/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Project: CS230
Author: Kevin Wright, Taeju Kwon
Creation date: 2/10/2021
-----------------------------------------------------------------*/

#include "MainMenu.h"
#include "Fonts.h"
#include "Screens.h"
#include "../Engine/Engine.h"
#include "../Engine/TransformMatrix.h"

MainMenu::OptionData MainMenu::optionsData[static_cast<int>(MainMenu::Options::Count)] = {
	{"Side Scroller", {0.5, 0.45}, {} },
	{"Space Shooter", {0.5, 0.35}, {} },
	{"Quit", {0.5, 0.25}, {} },
};

MainMenu::MainMenu(): upKey(CS230::InputKey::Keyboard::Up), downKey(CS230::InputKey::Keyboard::Down), selectKey(CS230::InputKey::Keyboard::Enter), selectedIndex(0){	}


void MainMenu::Load() {

	Engine::GetWindow().Clear(0x3399DAFF);
	
	title = Engine::GetSpriteFont(static_cast<int>(Fonts::Font2)).DrawTextToTexture("CS230 Project", 0xFFFFFFFF, true);
	for (OptionData& data : optionsData) {
		RenderOption(data, false);
	}
	selectedIndex = static_cast<int>(Options::Level1);
	RenderOption(optionsData[selectedIndex], true);
}

void MainMenu::Update([[maybe_unused]]double dt)
{
	switch(selectedIndex)
	{
		case 0:
			RenderOption(optionsData[selectedIndex], true);

			if(downKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex++;
			}
			if(selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level1));
			}
			break;
		case 1:
			RenderOption(optionsData[selectedIndex], true);
		
			if(downKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex++;
			} else if(upKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex--;
			}

			if(selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Level2));
			}
			break;
		case 2:
			RenderOption(optionsData[selectedIndex], true);
			if(upKey.IsKeyReleased() == true)
			{
				RenderOption(optionsData[selectedIndex], false);
				selectedIndex--;
			}
			if(selectKey.IsKeyReleased() == true)
			{
				Engine::GetGameStateManager().Shutdown();
			}
			break;
	}

}

void MainMenu::Unload(){}

void MainMenu::Draw()
{
	
	math::ivec2 winSize = Engine::GetWindow().GetSize();
	
	title.Draw(math::TranslateMatrix(math::ivec2{ winSize.x /2 - title.GetSize().x , winSize.y /2 +150 }) * math::ScaleMatrix(math::vec2{2.,2.}));
	
	for (OptionData& data : optionsData) {
		data.texture.Draw(math::TranslateMatrix(math::ivec2{ static_cast<int>((winSize.x * data.positionPercent.x) - data.texture.GetSize().x / 2) , static_cast<int>(winSize.y  * data.positionPercent.y )}) );
	}
}

void MainMenu::RenderOption(OptionData& data, bool isHighlighted) {
	data.texture = Engine::GetSpriteFont(static_cast<int>(Fonts::Font1)).DrawTextToTexture(
		data.text, (isHighlighted == true) ? MainMenu::onColor : MainMenu::offColor, true);
}



