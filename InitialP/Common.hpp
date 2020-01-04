#pragma once
#include <Siv3D.hpp>


// �V�[���̖��O
enum class State
{
	Title, Select, Game, Result
};

enum class Side
{
	Center, Left, Right
};

enum class ShiftJudge
{
	Perfect, Good, Bad
};

enum class driveOpe
{
	stepAccel, releaseAccel, stepBrakes, releaseBrakes
};


// �Q�[���f�[�^
struct GameData
{
	int score;
	int panjanNum;
	String playerPanjanName;
	Array<String> panjanDictionary;
};


// �V�[���Ǘ��N���X
using MyApp = SceneManager<State, GameData>;