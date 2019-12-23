#pragma once

#include <Siv3D.hpp>


#define DEFAULT_FONTSIZE 20


class HPBar
{
public:

	/// <summary> 
	/// コンストラクタ
	/// </summary>
	HPBar()
	{
		fontSize = DEFAULT_FONTSIZE;
		text = Font(fontSize);
	}


	// 描画
	void draw() const
	{
		text(U"HP : " + Format(remainingHP)).draw(textPosition);
		hpBase.draw(Color(0, 0, 0)).drawFrame(0, 3, Color(255, 255, 255));

		// HPが0になった時、緑色の線が残るため0になったら描画しない
		if (remainingHP >= 0)
		{
			hpBar.draw(Color(20, 255, 20));
		}
	}


	/// <summary> 
	/// HPバーを作成する
	/// </summary>
	/// <param name="posX"> HPバーの左上端のx座標 </param>
	/// <param name="posY"> HPバーの左上端のy座標 </param>
	/// <param name="width"> HPバーの幅 </param>
	/// <param name="height"> HPバーの高さ </param>
	void createHPBar(int posX, int posY, int width, int height)
	{
		barPosition = Vec2(posX, posY);
		hpBase = Rect(barPosition.x, barPosition.y, width, height);
		hpBar = Rect(barPosition.x, barPosition.y, width, height);
		textPosition = Vec2(barPosition.x, barPosition.y - fontSize * 2);
	}


	/// <summary> 
	/// HP残量を変更する
	/// </summary>
	/// <param name="remainingHP"> 現在のHP </param>
	void changeHP(int remainingHP)
	{
		double percent = (double)remainingHP / maxHP;
		this->remainingHP = remainingHP;
		hpBar = Rect(barPosition.x, barPosition.y, hpBase.w * percent, hpBase.h);
	}


	/// <summary> 
	/// HPの最大値を再設定する
	/// </summary>
	/// <param name="maxHP"> 最大のHP </param>
	void setMaxHP(int maxHP)
	{
		this->maxHP = maxHP;
	}


	/// <summary> 
	/// HPの最大値を再設定する
	/// </summary>
	/// <param name="size"> 最大のHP </param>
	void setFontSize(int size)
	{
		text = Font(size);
		textPosition = Vec2(barPosition.x - fontSize, barPosition.y);
	}



private:
	Rect hpBase; // HPバーの枠
	Rect hpBar; // 緑色の部分
	Font text; // HPの文字表示
	Vec2 barPosition; // HPバーの位置
	Vec2 textPosition; // HP表示のテキストの位置

	int maxHP; // 最大HP
	int remainingHP; // 残りHP
	int fontSize; // フォントサイズ
};