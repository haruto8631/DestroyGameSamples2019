#pragma once

#include "Common.hpp"


class TransmissionSystem
{
public:
	bool ShiftUp(ShiftJudge judge)
	{
		if (gearUpperLimit > gear)
		{
			gear++;
		}

		switch (judge)
		{
		case ShiftJudge::Perfect:
			break;
		case ShiftJudge::Good:
			break;
		case ShiftJudge::Bad:
			break;
		default:
			break;
		}
	}


	void ShiftDown(ShiftJudge judge)
	{

	}


private:
	double speed;
	double speed;
	int gear;
	const int gearLowerLimit = 1;
	int gearUpperLimit = 5;
};