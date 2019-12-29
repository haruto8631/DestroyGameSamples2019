#pragma once

#include "Common.hpp"
#include "PanjandrumBase.hpp"

class BasicPanjandrum : public PanjandrumBase
{
public:
	BasicPanjandrum() : PanjandrumBase()
	{

	}


	void spawn(Texture wheel, Texture base, Vec2 spawnPos)
	{
		this->wheel = wheel.resized(200, 200);
		this->base = base.resized(200, 200);
		position = spawnPos;
	}


	void rotates(Vec2 position)
	{
	}


	void draw() const
	{
		wheel.rotated(Scene::Time() * rotateSpeed).drawAt(position);
	}


	void suicideBomb()
	{

	}


	void setRotateSpeed(int speed)
	{
		rotateSpeed = speed;
	}

private:
	int rotateSpeed;

	TextureRegion wheel;
	TextureRegion base;
	Vec2 position;
	Timer timer;

};