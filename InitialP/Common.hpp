#pragma once
#include <Siv3D.hpp>


// �V�[���̖��O
enum class State
{
	Title, Select, Game, Result
};


// �Q�[���f�[�^
struct GameData
{
	int score;
};


// �V�[���Ǘ��N���X
using MyApp = SceneManager<State, GameData>;