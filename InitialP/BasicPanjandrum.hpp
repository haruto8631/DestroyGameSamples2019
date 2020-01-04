#pragma once

#include "Common.hpp"
#include "PanjandrumBase.hpp"

class BasicPanjandrum : public PanjandrumBase
{
public:
	BasicPanjandrum() : PanjandrumBase()
	{
		isDead = false;
	}


	void spawn(Texture wheel, Texture base, Vec2 spawnPos)
	{
		this->wheel = wheel.resized(150, 150);
		this->base = base.resized(150, 150);
		position = spawnPos;
	}


	void rotates(Vec2 position)
	{
		this->position = position;
	}


	void draw() const
	{
		if (isDead)
		{
		}
		else
		{
			wheel.rotated(Scene::Time() * rotateSpeed).drawAt(position);
		}
		
	}


	void suicideBomb()
	{
		
	}


	void setRotationSpeed(int speed)
	{
		rotateSpeed = speed;
	}

private:
	bool isDead;
	int rotateSpeed;

	TextureRegion wheel;
	TextureRegion base;
	Vec2 position;
};