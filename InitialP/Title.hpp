#pragma once

#include "Common.hpp"


class Title : public MyApp::Scene
{
public:
	// 初期化
	Title(const InitData& init) : IScene(init)
	{
		Scene::SetBackground(Color(0, 0, 0));
		centerPos = Scene::Center();
	}


	// 更新
	void update() override
	{
		if (SimpleGUI::ButtonAt(U"Start", centerPos + Vec2(0, 100), 200))
		{
			changeScene(State::Select);
		}
		if (SimpleGUI::ButtonAt(U"Exit", centerPos + Vec2(0, 150), 200))
		{
			System::Exit();
		}
	}


	// 描画
	void draw() const override
	{
		// 読み込んだ画像のサイズは1000x500くらいなので、resizedで適当にサイズを変更
		TextureAsset(U"Logo").resized(Scene::Height(), Scene::Height() / 2).drawAt(centerPos - Vec2(0, Scene::Height() / 4));
	}


private:
	Texture titleLogo;
	Vec2 centerPos;
};