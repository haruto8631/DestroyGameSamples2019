#pragma once

#include "Common.hpp"


class PanjandrumBase
{
public:
	PanjandrumBase(Vec2 pos, int speed) : speed(speed, 0)
	{

	}

	enum class ShiftJudgment
	{
		Perfect, Good, Bad
	};

	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void suicideBomb() = 0;
	
	void shiftUp(ShiftJudgment result )
	{
	
	}

	void shiftDown(ShiftJudgment result)
	{
	
	}

private:
	Vec2 centerPosition;
	Vec2 speed;

	int gear = 1;
	int topGear = 5;
};