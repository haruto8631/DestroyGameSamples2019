#pragma once

#include "Common.hpp"
#include "BasicPanjandrum.hpp"


class Game : public MyApp::Scene
{
public:
	// èâä˙âª
	Game(const InitData& init) : IScene(init)
	{
		TextureAsset::Register(U"Stage1", Resource(U"texture/backgroundImage1.png"));
		TextureAsset::Register(U"Stage1Start", Resource(U"texture/backgroundImage1Start.png"));
		TextureAsset::Register(U"Stage1Goal", Resource(U"texture/backgroundImage1Goal.png"));
		TextureAsset::Register(U"TachometerBase", Resource(U"texture/TachometerBase.png"));
		TextureAsset::Register(U"TachometerNeedle", Resource(U"texture/MeterNeedle.png"));
		player = BasicPanjandrum();
		player.spawn(TextureAsset(getData().playerPanjnaName + U"_w"), TextureAsset(getData().playerPanjnaName + U"_b"), Scene::Center());
		player.setRotateSpeed(10);
	}


	void update() override
	{
		player.rotates(Scene::Center());
	}


	// ï`âÊ
	void draw() const override
	{
		TextureAsset(U"Stage1").resized(800, 600).drawAt(Scene::Center());
		TextureAsset(U"TachometerBase").resized(300, 300).drawAt(500, 600);
		TextureAsset(U"TachometerNeedle").resized(230, 230).drawAt(500, 600);
		player.draw();
	}





private:
	BasicPanjandrum player;
	BasicPanjandrum opponent;
};