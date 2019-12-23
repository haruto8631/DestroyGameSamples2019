#pragma once

#include "Common.hpp"

class Result : public MyApp::Scene
{
public:
	// ������
	Result(const InitData& init) : IScene(init)
	{

	}


	// �X�V
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
		FontAsset(U"Score")(U"���Ȃ��̃X�R�A").drawAt(Scene::Center() + Vec2(0, -100));
		FontAsset(U"Score")(Format(getData().score)).drawAt(Scene::Center());
	}


private:

};