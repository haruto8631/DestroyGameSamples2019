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
	int panjanNum;
	String playerPanjnaName;
	Array<String> panjanDictionary;
};


// シーン管理クラス
using MyApp = SceneManager<State, GameData>;