#pragma once

#include "Common.hpp"
#include "Bullet.hpp"


#define DEFAULT_ENEMY_SIZE 15
#define DEFAULT_INVINCIBLE_FRAME 60

class Enemy
{
public:

	/// <summary> 
	/// コンストラクタ
	/// </summary>
	/// <param name="defaultPosition"> 敵機の位置 </param>
	Enemy(Vec2 defaultPosition, Vec2 defaultDirection, int hp)
	{
		enemyPosition = defaultPosition;
		enemyDirection = defaultDirection;
		hitPoint = hp;
		this->size = DEFAULT_ENEMY_SIZE;
	}


	// 更新
	void update()
	{
		enemyPosition.x += enemyDirection.x;
		enemyPosition.y += enemyDirection.y;
		collision = Circle(enemyPosition, size); // 敵機の位置を再設定

		if (invincible)
		{
			invincibleTimer--;
			if (invincibleTimer <= 0)
			{
				invincible = false;
			}
		}
	}


	// 描画
	void draw() const
	{
		collision.draw();
	}


	/// <summary>
	/// 敵機が死んでいるかどうかをBoolで返す
	/// </summary>
	/// <return> 死んでいるかどうか </return>
	bool dead() const
	{
		return (hitPoint <= 0);
	}


	/// <summary> 
	/// ダメージを受けるときに実行する関数
	// 敵機のHPを増やしたり減らしたりできる
	/// </summary>
	/// <param name="damage"> ダメージの値 </param>
	void hit(int damage)
	{
		if (!invincible)
		{
			invincible = true;
			hitPoint -= damage;
			invincibleTimer = DEFAULT_INVINCIBLE_FRAME;
		}
	}


	/// <summary> 
	/// 敵機のサイズを変更する
	/// </summary>
	/// <param name="size"> 敵機のサイズ </param>
	void setSize(int size)
	{
		this->size = size;
	}


	/// <summary> 
	/// 敵機のスピードの変更
	/// </summary>
	/// <param name="speed"> 敵機のスピード </param>
	void setSpeed(int speed)
	{
		this->speed = speed;
	}


	/// <summary> 
	/// 敵機の中央の座標をVec2型で取得する
	/// </summary>
	/// <return> 敵機の中央の座標 </return>
	Vec2 getEnemyPosition()
	{
		return enemyPosition;
	}


	/// <summary>
	/// 敵機の当たり判定の当たり判定を取得する
	/// </summary>
	/// <return> 敵機の円を返す </return>
	Circle& getCollision()
	{
		return collision;
	}



private:
	Vec2 enemyPosition; // 敵機の先端の座標
	Vec2 enemyDirection;
	Circle collision; // 敵機の当たり判定

	int speed; // 敵機のスピード
	int hitPoint; // 敵機のHP
	int size; // 敵機の半径
	int invincibleTimer; // 無敵時間を管理するタイマー
	bool invincible; // 無敵かどうか 

};