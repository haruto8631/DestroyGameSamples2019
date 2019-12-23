#pragma once

#include "Common.hpp"

class Result : public MyApp::Scene
{
public:
	// 初期化
	Result(const InitData& init) : IScene(init)
	{

	}


	// 更新
	void update() override
	{
		if (SimpleGUI::ButtonAt(U"タイトルに戻る", Scene::Center() + Vec2(0, 100)))
		{
			changeScene(State::Title, 300, false);
		}

		if (SimpleGUI::ButtonAt(U"アプリを終了する", Scene::Center() + Vec2(0, 200)))
		{
			System::Exit();
		}
	}


	// 描画
	void draw() const override
	{
		FontAsset(U"Score")(U"あなたのスコア").drawAt(Scene::Center() + Vec2(0, -100));
		FontAsset(U"Score")(Format(getData().score)).drawAt(Scene::Center());
	}


private:

};