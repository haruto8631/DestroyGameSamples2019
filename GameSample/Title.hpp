#pragma once

#include "Common.hpp"

class Title : public MyApp::Scene
{
public:
	// 初期化
	Title(const InitData& init) : IScene(init)
	{
		titleNamePosition = Vec2(Scene::Width() / 2, Scene::Height() / 4);
		startButtonPosition = Scene::Center();
		exitButtonPosition = Vec2(startButtonPosition.x, startButtonPosition.y + 50);
	}


	// 更新
	void update() override
	{
		if (SimpleGUI::ButtonAt(U"始める", startButtonPosition))
		{
			changeScene(State::Game, 300, false);
		}

		if (SimpleGUI::ButtonAt(U"終わる", exitButtonPosition))
		{
			System::Exit();
		}


	}


	// 描画
	void draw() const override
	{
		FontAsset(U"Title")(U"破壊ゲームサンプル").drawAt(titleNamePosition);
	}


private:
	Vec2 titleNamePosition;
	Vec2 startButtonPosition;
	Vec2 exitButtonPosition;
};