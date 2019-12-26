#pragma once

#include "Common.hpp"


class PanjandrumBase
{
public:
	PanjandrumBase(Vec2 pos, int speed) : speed(speed, 0)
	{

	}

	virtual void spawn() = 0;
	virtual void rotates() = 0;
	virtual void suicideBomb() = 0;

private:
	Vec2 centerPosition;
	Vec2 speed;
};