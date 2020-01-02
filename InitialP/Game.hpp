#pragma once

#include "Common.hpp"
#include "BasicPanjandrum.hpp"
#include "Course.hpp"


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
		opponent = BasicPanjandrum();
		player.spawn(TextureAsset(getData().playerPanjanName + U"_w"), TextureAsset(getData().playerPanjanName + U"_b"), Vec2(200, 460));
		player.setRotationSpeed(10);
		opponent.spawn(TextureAsset(getData().playerPanjanName + U"_w"), TextureAsset(getData().playerPanjanName + U"_b"), Vec2(200, 460));
		opponent.setRotationSpeed(10);
		course = Course();
		Array<Vec2> coursePath;
		coursePath.push_back(Vec2(0, 0));
		coursePath.push_back(Vec2(200, 400));
		coursePath.push_back(Vec2(200, -400));
		coursePath.push_back(Vec2(400, 0));
		course.makeCourse(coursePath, Vec2(200, 450));
	}


	void update() override
	{
		player.rotates(Vec2(200, 450)  + course.getSidePos(Side::Left));
		opponent.rotates(Vec2(200, 450) + course.getSidePos(Side::Right));
		course.updateProgress(a += 0.001);
	}


	// ï`âÊ
	void draw() const override
	{
		//TextureAsset(U"Stage1").resized(800, 600).drawAt(Scene::Center());
		course.draw();
		TextureAsset(U"TachometerBase").resized(300, 300).drawAt(500, 600);
		TextureAsset(U"TachometerNeedle").resized(230, 230).drawAt(500, 600);
		player.draw();
		opponent.draw();
	}





private:
	BasicPanjandrum player;
	BasicPanjandrum opponent;
	Course course;
	double a = 0;
};