#pragma once

#include "Common.hpp"
#include "Bullet.hpp"


#define DEFAULT_PLAYER_SIZE 20
#define DEFAULT_PLAYER_SPEED 10
#define DEFAULT_HP 100;
#define DEFAULT_INVINCIBLE_FRAME 60

class Player
{
public:

	/// <summary> 
	/// コンストラクタ
	/// </summary>
	/// <param name="defaultPosition"> 自機の位置 </param>
	Player(Vec2 defaultPosition)
	{
		invincible = true;
		invincibleTimer = DEFAULT_INVINCIBLE_FRAME;
		playerPosition = defaultPosition;
		setPlayArea(0, 0, Scene::Width(), Scene::Height());
		setSize(DEFAULT_PLAYER_SIZE);
		setSpeed(DEFAULT_PLAYER_SPEED);
		setBothPoints(playerPosition);
	}

	/// <summary> 
	/// コンストラクタ
	/// </summary>
	Player()
	{

	}


	// 更新
	void update() 
	{
		// Wキーで上に移動
		if (KeyW.pressed())
		{
			playerPosition.y -= speed;

			// 移動領域を制限
			if (playerPosition.y <= playArea.y)
			{
				playerPosition.y += speed; // はみ出したら戻す
			}
		}

		// Sキーで下に移動
		if (KeyS.pressed())
		{
			playerPosition.y += speed;

			// 移動領域を制限
			if (playerPosition.y >= playArea.y + playArea.h)
			{
				playerPosition.y -= speed; // はみ出したら戻す
			}
		}

		// Aキーで左に移動
		if (KeyA.pressed())
		{
			playerPosition.x -= speed;

			// 移動領域を制限
			if (playerPosition.x <= playArea.x)
			{
				playerPosition.x += speed; // はみ出したら戻す
			}
		}

		// Dキーで右に移動
		if (KeyD.pressed())
		{
			playerPosition.x += speed;

			// 移動領域を制限
			if (playerPosition.x >= playArea.x + playArea.w)
			{
				playerPosition.x -= speed; // はみ出したら戻す
			}
		}

		// 被弾後の無敵時間の処理
		if (invincible)
		{
			invincibleTimer--;
			if (invincibleTimer <= 0)
			{
				invincible = false;
			}
		}

		setBothPoints(playerPosition); // 三角形の両端の座標を再設定
		collision = Triangle(playerPosition, leftmostPoint, rightmostPoint); // 自機の位置を再設定
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
	// 自機のHPを増やしたり減らしたりできる
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
	/// 自機のHPを変更する
	/// </summary>
	/// <param name="hp"> 自機のHP </param>
	void setHP(int hp)
	{
		hitPoint = hp;
	}



	/// <summary> 
	/// 自機のサイズを変更する
	/// </summary>
	/// <param name="size"> 自機のサイズ </param>
	void setSize(int size)
	{
		width = size;
		height = size;
	}


	/// <summary> 
	/// 自機のスピードの変更
	/// </summary>
	/// <param name="speed"> 自機のスピード </param>
	void setSpeed(int speed)
	{
		this->speed = speed;
	}


	/// <summary> 
	/// HPバーを作成する
	/// </summary>
	/// <param name="posX"> HPバーの左上端のx座標 </param>
	/// <param name="posY"> HPバーの左上端のy座標 </param>
	/// <param name="width"> HPバーの幅 </param>
	/// <param name="height"> HPバーの高さ </param>
	void setPlayArea(int x, int y, int width, int height)
	{
		playArea = Rect(x, y, width, height);
	}



	/// <summary> 
	/// 自機の先端の座標をVec2型で取得する
	/// </summary>
	/// <return> 自機の中央の座標 </return>
	Vec2 getPlayerPosition()
	{
		return playerPosition;
	}


	/// <summary>
	/// 自機の当たり判定のTriangle型を取得する
	/// </summary>
	/// <return> 自機の三角形を返す </return>
	Triangle& getCollision()
	{
		return collision;
	}


	/// <summary>
	/// 現在のHPを返す
	/// </summary>
	int getHP()
	{
		return hitPoint;
	}



private:
	Vec2 playerPosition; // 自機の先端の座標
	Vec2 leftmostPoint; // 自機の左端の座標
	Vec2 rightmostPoint; // 自機の右側の座標
	Triangle collision; // 自機の当たり判定
	Rect playArea; // 自機が移動可能な範囲

	int speed; // 自機のスピード
	int hitPoint; // 自機のHP
	int width; // 自機の幅
	int height; // 自機の高さ
	int invincibleTimer; // 無敵時間を管理するタイマー
	bool invincible; // 無敵かどうか 


	/// <summary> 
	/// 自機の両端の座標を設定する
	/// </summary>
	/// <param name="CenterPosition"> 自機の先端の座標 </param>
	void setBothPoints(Vec2 CenterPosition)
	{
		leftmostPoint = Vec2(CenterPosition.x - (width / 2), CenterPosition.y + height);
		rightmostPoint = Vec2(CenterPosition.x + (width / 2), CenterPosition.y + height);
	}
};