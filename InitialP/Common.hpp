#pragma once
#include <Siv3D.hpp>


// シーンの名前
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


// ゲームデータ
struct GameData
{
	int score;
	int panjanNum;
	String playerPanjanName;
	Array<String> panjanDictionary;
};


// シーン管理クラス
using MyApp = SceneManager<State, GameData>;