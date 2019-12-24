#pragma once
#include <Siv3D.hpp>


// シーンの名前
enum class State
{
	Title, Select, Game, Result
};


// ゲームデータ
struct GameData
{
	int score;
};


// シーン管理クラス
using MyApp = SceneManager<State, GameData>;