#pragma once

#include "Common.hpp"

#define DEFAULT_VISIBLE_FRAME 30



class JudgeTexture
{
public:
	JudgeTexture()
	{
		TextureAsset::Register(U"RightPerfect", Resource(U"texture/PerfectShiftRight.png"));
		TextureAsset::Register(U"RightGood", Resource(U"texture/GoodShiftRight.png"));
		TextureAsset::Register(U"RightBad", Resource(U"texture/BadShiftRight.png"));
		visibleTimer = DEFAULT_VISIBLE_FRAME;
		visible = false;
	}

	void update(std::pair<bool, ShiftJudge> judge)
	{
		bool needUpdate = judge.first;
		ShiftJudge lastJudge = judge.second;

		if (needUpdate)
		{
			switch (lastJudge)
			{
			case ShiftJudge::Perfect:
				judgeTexture = TextureAsset(U"RightPerfect");
				break;
			case ShiftJudge::Good:
				judgeTexture = TextureAsset(U"RightGood");
				break;
			case ShiftJudge::Bad:
				judgeTexture = TextureAsset(U"RightBad");
				break;
			default:
				break;
			}
			visibleTimer = DEFAULT_VISIBLE_FRAME;
			visible = true;
		}


		if (visible)
		{
			visibleTimer--;
			if (visibleTimer <= 0)
			{
				visible = false;
			}
		}
	}


	void draw() const
	{
		if (visible)
		{
			judgeTexture.resized(300, 300).draw(500 + Random<int>(-3, 3), 100 + Random<int>(-3, 3));
		}
	}

private:
	int visibleTimer;
	bool visible;
	Texture judgeTexture;
	Side side;
};