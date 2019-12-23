#pragma once

#include "Common.hpp"

class Title : public MyApp::Scene
{
public:
	// ������
	Title(const InitData& init) : IScene(init)
	{
		titleNamePosition = Vec2(Scene::Width() / 2, Scene::Height() / 4);
		startButtonPosition = Scene::Center();
		exitButtonPosition = Vec2(startButtonPosition.x, startButtonPosition.y + 50);
	}


	// �X�V
	void update() override
	{
		if (SimpleGUI::ButtonAt(U"�n�߂�", startButtonPosition))
		{
			changeScene(State::Game, 300, false);
		}

		if (SimpleGUI::ButtonAt(U"�I���", exitButtonPosition))
		{
			System::Exit();
		}


	}


	// �`��
	void draw() const override
	{
		FontAsset(U"Title")(U"�j��Q�[���T���v��").drawAt(titleNamePosition);
	}


private:
	Vec2 titleNamePosition;
	Vec2 startButtonPosition;
	Vec2 exitButtonPosition;
};