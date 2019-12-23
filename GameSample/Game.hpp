#pragma once

#include "Common.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "HPBar.hpp"
#include "Bullet.hpp"


#define PLAYER_BULLET_LIMIT 5
#define ENEMY_LIMIT 10
#define ENEMY_BULLET_LIMIT 40


class Game : public MyApp::Scene
{
public:
	// 初期化
	Game(const InitData& init) : IScene(init)
	{
		player = Player(Scene::Center());
		player.setHP(100);

		hpBar = HPBar();
		hpBar.createHPBar(650, 500, 100, 25);
		hpBar.setMaxHP(player.getHP());
		hpBar.changeHP(player.getHP());

		field = Rect(50, 50, 500, 500);

		player.setPlayArea(field.x, field.y, field.w, field.h);

		getData().score = 0;
	}


	void update() override
	{
		player.update(); // Playerの情報更新

		if (enemy.size() <= ENEMY_LIMIT)
		{
			if (RandomBool(0.05))
			{
				enemy.push_back(Enemy(Vec2(Random() * field.w + field.x, field.y), Vec2(RandomInt8() % 2, 2), 20));
			}
		}


		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i].update(); // 敵の情報更新

			// 敵が打つ弾丸を発生させる
			if (RandomBool(0.01) && (!enemy[i].dead()))
			{
				enemyBullet.push_back(Bullet(enemy[i].getEnemyPosition(), Vec2(0, 20), 20, Color(255, 40, 40)));
				if (enemyBullet.size() > ENEMY_BULLET_LIMIT)
				{
					enemyBullet.pop_front();
				}
			}

			// 枠外、あるいは死んだ敵を後始末する
			if (enemy[i].dead() || enemy[i].getEnemyPosition().x < field.x || enemy[i].getEnemyPosition().x > field.x + field.w || enemy[i].getEnemyPosition().y > field.y + field.h)
			{
				enemy.erase(enemy.begin() + i);
			}
		}
		
		// プレイヤーの弾丸の発射処理
		if (KeySpace.down())
		{
			// 動的配列の最後尾に追加
			playerBullet.push_back(Bullet(player.getPlayerPosition(), Vec2(0, -10), 30));

			// 動的配列の要素数は5個以上だったら
			if (playerBullet.size() > PLAYER_BULLET_LIMIT)
			{
				playerBullet.pop_front(); // 先頭から弾丸を削除(古いものから)
			}
		}

		for (int i = 0; i < playerBullet.size(); i++)
		{
			playerBullet[i].update(); // プレイヤーの弾丸の移動

			for (int j = 0; j < enemy.size(); j++)
			{
				// プレイヤーの弾と敵の当たり判定は接触した時
				if (playerBullet[i].getCollision().intersects(enemy[j].getCollision()))
				{
					enemy[j].hit(playerBullet[i].hitBullet());
					getData().score += 100;
				}
			}
		}

		for (int i = 0; i < enemyBullet.size(); i++)
		{
			enemyBullet[i].update(); // 敵の弾丸の移動

			// プレイヤーと弾丸の当たり判定が重なったとき
			if (player.getCollision().intersects(enemyBullet[i].getCollision()))
			{
				player.hit(enemyBullet[i].hitBullet());
				hpBar.changeHP(player.getHP());
				break; // 無敵時間に入るので以降の処理はスキップ
			}
		}

		// プレイヤーが死んだら結果画面に遷移
		if (player.dead())
		{
			changeScene(State::Result, 500);
		}
	}


	// 描画
	void draw() const override
	{
		// 自機の弾丸の描画
		for (int i = 0; i < playerBullet.size(); i++)
		{
			if (!(playerBullet[i].dead()))
			{
				playerBullet[i].draw();
			}
		}

		// 敵機の弾丸の描画
		for (int i = 0; i < enemyBullet.size(); i++)
		{
			if (!(enemyBullet[i].dead()))
			{
				enemyBullet[i].draw();
			}
		}

		// 敵機の描画
		for (int i = 0; i < enemy.size(); i++)
		{
			if (!enemy[i].dead())
			{
				enemy[i].draw();
			}
		}

		player.draw(); // 自機の描画
		field.drawFrame(0, 200, Color(0, 0, 0)).drawFrame(0, 5, Color(255, 255, 255)); // 枠や枠外の描画
		hpBar.draw(); // HPの描画
		FontAsset(U"Score")(U"Score : " + Format(getData().score)).draw(0, 0, Color(255, 255, 255)); // Scoreの描画
	}





private:
	Player player; // 自機
	Array<Enemy> enemy; // 敵のリスト
	Array<Bullet> playerBullet; // 自機の弾丸のリスト
	Array<Bullet> enemyBullet; // 敵の弾丸のリスト
	HPBar hpBar; // HPバー
	Rect field; // 枠
};