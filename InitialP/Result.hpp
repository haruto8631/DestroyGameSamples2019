#pragma once

#include "Common.hpp"


class Result : public MyApp::Scene
{
public:
	// ������
	Result(const InitData& init) : IScene(init)
	{
		Scene::SetBackground(Color(0, 0, 0));

	}


	void update() override
	{
		if (SimpleGUI::ButtonAt(U"�^�C�g���ɖ߂�", Scene::Center() + Vec2(0, 100)))
		{
			changeScene(State::Title, 300, false);
		}

		if (SimpleGUI::ButtonAt(U"�A�v�����I������", Scene::Center() + Vec2(0, 200)))
		{
			System::Exit();
		}
	}


	// �`��
	void draw() const override
	{
		FontAsset(U"Score")(U"���Ȃ��̋L�^").drawAt(Scene::Center() + Vec2(0, -100));
		FontAsset(U"Score")(getData().record).drawAt(Scene::Center());
	}





private:

};