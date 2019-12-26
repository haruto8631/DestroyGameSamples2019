#pragma once

#include "Common.hpp"


class Title : public MyApp::Scene
{
public:
	// ������
	Title(const InitData& init) : IScene(init)
	{
		Scene::SetBackground(Color(0, 0, 0));
		centerPos = Scene::Center();
	}


	// �X�V
	void update() override
	{
		if (SimpleGUI::ButtonAt(U"Start", centerPos + Vec2(0, 100), 200))
		{
			changeScene(State::Select);
		}
		if (SimpleGUI::ButtonAt(U"Exit", centerPos + Vec2(0, 150), 200))
		{
			System::Exit();
		}
	}


	// �`��
	void draw() const override
	{
		// �ǂݍ��񂾉摜�̃T�C�Y��1000x500���炢�Ȃ̂ŁAresized�œK���ɃT�C�Y��ύX
		TextureAsset(U"Logo").resized(Scene::Height(), Scene::Height() / 2).drawAt(centerPos - Vec2(0, Scene::Height() / 4));
	}


private:
	Texture titleLogo;
	Vec2 centerPos;
};