#pragma once

#include "Common.hpp"
#include "BasicPanjandrum.hpp"
#include "Course.hpp"
#include "TransmissionSystem.hpp"
#include "Tachometer.hpp"
#include "JudgeTexture.hpp"


class Game : public MyApp::Scene
{
public:
	// ������
	Game(const InitData& init) : IScene(init)
	{
		TextureAsset::Register(U"backgroundImage", Resource(U"texture/backgroundImage1.png"));
		player = BasicPanjandrum();
		player.spawn(TextureAsset(getData().playerPanjanName + U"_w"), TextureAsset(getData().playerPanjanName + U"_b"), Vec2(200, 460));
		player.setRotationSpeed(0);
		course = Course();
		Array<Vec2> coursePath;
		coursePath.push_back(Vec2(0, 0));
		coursePath.push_back(Vec2(8000, 0));
		course.makeCourse(coursePath, Vec2(200, 450));
		judgeTexture = JudgeTexture();
		trSys = TransmissionSystem(5);
		meter = Tachometer(Vec2(500, 600), 300, trSys.getSpeedLimits());
		sw.reset();
		isStarted = false;
		isUpdated = false;
		progress = 0;
	}


	void update() override
	{
		if (KeySpace.down())
		{
			isStarted = true;
			sw.start();
		}

		if (isStarted)
		{
			trSys.update(driveOpe::stepAccel);
			judgeTexture.update(trSys.getLastJudge());
			progress += trSys.getSpeed() * 0.01;
			player.setRotationSpeed(trSys.getSpeed() * 100);
		}
		meter.update(trSys.getSpeed(), trSys.getGear());
		player.rotates(Vec2(200, 450) + course.getSidePos(Side::Left));
		course.updateProgress(progress);
		isUpdated = true;
	}


	// �`��
	void draw() const override
	{
		if (isUpdated)
		{
			TextureAsset(U"backgroundImage").resized(800, 600).draw(0, 0);
			course.draw();
			meter.draw();
			player.draw();
			judgeTexture.draw();
			FontAsset(U"Time")(sw.format(U"mm:ss:xx"_sv)).drawAt(400, 50);
		}
	}





private:
	BasicPanjandrum player;
	Course course;
	JudgeTexture judgeTexture;
	TransmissionSystem trSys;
	Tachometer meter;

	bool isUpdated;
	bool isStarted;
	double progress;
	double speed;
	Stopwatch sw;
};