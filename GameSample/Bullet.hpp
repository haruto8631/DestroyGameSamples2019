#pragma once

#include "Common.hpp"


#define DEFAULT_BULLET_COLOR Color(127, 127, 127)
#define DEFAULT_BULLET_WIDTH 8
#define DEFAULT_BULLET_HEIGHT 15
#define DEFAULT_HIT_POINT 1


class Bullet
{
public:
	
	/// <summary> 
	/// コンストラクタ
	/// </summary>
	/// <param name="defaultPosition"> 初期位置 </param>
	/// <param name="direction"> 向きと速度 </param>
	/// <param name="tag"> このクラスにつける種類 </param>
	Bullet(Vec2 defaultPosition, Vec2 direction, int damage, Color color = Color(127, 127, 127))
	{
		this->color = color;
		this->damage = damage;
		position = defaultPosition;
		width = DEFAULT_BULLET_WIDTH;
		height = DEFAULT_BULLET_HEIGHT;
		hitPoint = DEFAULT_HIT_POINT;
		this->direction = direction;
	}


	// 更新
	void update()
	{
		position.x += direction.x;
		position.y += direction.y;
		collision = Rect(position.x - (width / 2), position.y, width, height);
	}


	// 描画
	void draw() const
	{
		collision.draw(color);
	}


	/// <summary> 
	/// 弾丸の進む向きと速度を変更する
	/// </summary>
	/// <param name="direction"> 向きと速度 </param>
	void changeDirection(Vec2 direction)
	{
		this->direction = direction;
	}


	/// <summary> 
	/// 弾丸のサイズを変更する
	/// </summary>
	/// <param name="width"> 幅 </param>
	/// <param name="height"> 高さ </param>
	void changeSize(int width, int height)
	{
		this->width = width;
		this->height = height;
	}


	/// <summary> 
	/// 弾丸のダメージ量を変更する
	/// </summary>
	/// <param name="width"> 威力・ダメージ量 </param>
	void changeDamage(int damage)
	{
		this->damage = damage;
	}


	/// <summary> 
	/// 弾丸のダメージ量を取得する
	/// </summary>
	int getDamage()
	{
		return damage;
	}


	/// <summary> 
	/// 弾丸の当たり判定を取得する
	/// </summary>
	Rect& getCollision()
	{
		return collision;
	}


	/// <summary> 
	/// バレットが何かに当たったことを知らせる
	/// ダメージ量を返す
	/// </summary>
	/// <return> この弾が持つダメージ量 </return>
	int hitBullet()
	{
		hitPoint = 0;
		return damage;
	}


	/// <summary> 
	/// 弾が死んでいるかどうかをBoolで返す
	/// </summary>
	/// <return> 死んでいるかどうか </return>
	bool dead() const
	{
		return (hitPoint <= 0);
	}


private:
	Color color; // 弾丸の色
	Rect collision; // 弾丸の当たり判定
	Vec2 position; // 弾丸の位置
	Vec2 direction; // 弾丸の向き・速度

	int damage; // 弾丸の持つダメージ量
	int width; // 弾丸の幅
	int height; // 弾丸の高さ
	int hitPoint; // 弾丸のHP
};