#pragma once

#include "Common.hpp"

#define DEFAULT_INVINCIBLE_FRAME 60
#define PERFECT_WIDTH 0.1
#define GOOD_WIDTH 0.2


class TransmissionSystem
{
public:
	TransmissionSystem()
	{

	}


	TransmissionSystem(int gearUpperLimitNum)
	{
		speed = 0;
		gear = 1;
		acceleration = 0.002;
		needJudgeUpdate = false;
		for (int i = 0; i < gearUpperLimitNum; i++)
		{
			speedLimits.push_back((1.0 / gearUpperLimitNum)  * (i + 1));
		}
		gearUpperLimit = gearUpperLimitNum;
	}


	void update(driveOpe operation)
	{
		switch (operation)
		{
		case driveOpe::stepAccel:
			speed += acceleration;
			if (speedLimits[gear - 1] < speed)
			{
				speed -= acceleration * 2;
			}
		default:
			break;
		}

		if (KeyD.down())
		{
			ShiftJudge judge;
			if ((speed / speedLimits[gear - 1]) < 0.6 && (speed / speedLimits[gear - 1]) > 0.4)
			{
				judge = ShiftJudge::Perfect;
			}
			else if ((speed / speedLimits[gear - 1]) < 0.7 && (speed / speedLimits[gear - 1]) > 0.3)
			{
				judge = ShiftJudge::Good;
			}
			else
			{
				judge = ShiftJudge::Bad;
			}
			
			if (ShiftUp(judge))
			{
				needJudgeUpdate = true;
				lastJudge = judge;
			}
		}
	}

	
	int getGear()
	{
		return gear;
	}


	double getSpeed()
	{
		return speed;
	}


	Array<double> getSpeedLimits()
	{
		return speedLimits;
	}


	std::pair<bool, ShiftJudge> getLastJudge()
	{
		bool temp = needJudgeUpdate;
		needJudgeUpdate = false;
		return { temp, lastJudge };
	}


private:
	double acceleration;
	double speed;
	int gear;
	int gearLowerLimit = 1;
	int gearUpperLimit;
	Array<double> speedLimits;

	bool needJudgeUpdate;
	ShiftJudge lastJudge;

	bool ShiftUp(ShiftJudge judge)
	{
		if (gearUpperLimit > gear)
		{
			gear++;
			switch (judge)
			{
			case ShiftJudge::Perfect:
				speed += 0.01;
				break;
			case ShiftJudge::Good:
				break;
			case ShiftJudge::Bad:
				speed -= 0.005;
				break;
			default:
				break;
			}
			return true;
		}
		return false;
	}


	bool ShiftDown(ShiftJudge judge)
	{
		return false;
	}
};