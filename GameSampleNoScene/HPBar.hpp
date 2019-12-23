#pragma once

#include <Siv3D.hpp>


#define DEFAULT_FONTSIZE 20


class HPBar
{
public:

	/// <summary> 
	/// �R���X�g���N�^
	/// </summary>
	HPBar()
	{
		fontSize = DEFAULT_FONTSIZE;
		text = Font(fontSize);
	}


	// �`��
	void draw() const
	{
		text(U"HP : " + Format(remainingHP)).draw(textPosition);
		hpBase.draw(Color(0, 0, 0)).drawFrame(0, 3, Color(255, 255, 255));

		// HP��0�ɂȂ������A�ΐF�̐����c�邽��0�ɂȂ�����`�悵�Ȃ�
		if (remainingHP >= 0)
		{
			hpBar.draw(Color(20, 255, 20));
		}
	}


	/// <summary> 
	/// HP�o�[���쐬����
	/// </summary>
	/// <param name="posX"> HP�o�[�̍���[��x���W </param>
	/// <param name="posY"> HP�o�[�̍���[��y���W </param>
	/// <param name="width"> HP�o�[�̕� </param>
	/// <param name="height"> HP�o�[�̍��� </param>
	void createHPBar(int posX, int posY, int width, int height)
	{
		barPosition = Vec2(posX, posY);
		hpBase = Rect(barPosition.x, barPosition.y, width, height);
		hpBar = Rect(barPosition.x, barPosition.y, width, height);
		textPosition = Vec2(barPosition.x, barPosition.y - fontSize * 2);
	}


	/// <summary> 
	/// HP�c�ʂ�ύX����
	/// </summary>
	/// <param name="remainingHP"> ���݂�HP </param>
	void changeHP(int remainingHP)
	{
		double percent = (double)remainingHP / maxHP;
		this->remainingHP = remainingHP;
		hpBar = Rect(barPosition.x, barPosition.y, hpBase.w * percent, hpBase.h);
	}


	/// <summary> 
	/// HP�̍ő�l���Đݒ肷��
	/// </summary>
	/// <param name="maxHP"> �ő��HP </param>
	void setMaxHP(int maxHP)
	{
		this->maxHP = maxHP;
	}


	/// <summary> 
	/// HP�̍ő�l���Đݒ肷��
	/// </summary>
	/// <param name="size"> �ő��HP </param>
	void setFontSize(int size)
	{
		text = Font(size);
		textPosition = Vec2(barPosition.x - fontSize, barPosition.y);
	}



private:
	Rect hpBase; // HP�o�[�̘g
	Rect hpBar; // �ΐF�̕���
	Font text; // HP�̕����\��
	Vec2 barPosition; // HP�o�[�̈ʒu
	Vec2 textPosition; // HP�\���̃e�L�X�g�̈ʒu

	int maxHP; // �ő�HP
	int remainingHP; // �c��HP
	int fontSize; // �t�H���g�T�C�Y
};