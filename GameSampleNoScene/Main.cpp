
# include <Siv3D.hpp> // OpenSiv3D v0.4.2
#include "Player.hpp"
#include "Enemy.hpp"
#include "HPBar.hpp"
#include "Bullet.hpp"




void Main()
{
	constexpr int playerWidth = 20;
	constexpr int playerHeight = 20;
	constexpr int playerSpeed = 10;
	constexpr int playerBulletLimit = 5;
	constexpr int invincibleFrame = 60;
	constexpr int enemyWidth = 10;
	constexpr int enemyLimit = 10;
	constexpr int enemyBulletLimit = 40;
	constexpr int bulletWidth = 6;
	constexpr int bulletHeight = 12;
	constexpr int bulletSpeed = 10;
	constexpr int bulletDamage = 20;

	int playerHP = 100;
	int invincibleTimer = 60;
	bool invincible = false;


	Triangle player = Triangle(Scene::Center(), Scene::Center() + Vec2(playerWidth / -2, playerHeight), Scene::Center() + Vec2(playerWidth / 2, playerHeight));
	Vec2 mvVec; // playerの動く方向
	Array<Circle> enemy;
	Array<Rect> playerBullet;
	Array<Rect> enemyBullet;
	Rect field = Rect(50, 50, 500, 500);
	

	// タイトルを設定
	Window::SetTitle(U"破壊ゲームさんぷる");

	// 背景色を設定
	Scene::SetBackground(Color(0, 0, 0));

	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 60, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");
	FontAsset::Register(U"Score", 30, Typeface::Regular);


	while (System::Update())
	{
		mvVec = Vec2(0, 0);
		if (KeyA.pressed()) { mvVec -= Vec2(playerSpeed, 0); }
		if (KeyD.pressed()) { mvVec += Vec2(playerSpeed, 0); }
		if (KeyW.pressed()) { mvVec -= Vec2(0, playerSpeed); }
		if (KeyS.pressed()) { mvVec += Vec2(0, playerSpeed); }
		player = Triangle(player.p0 + mvVec, player.p1 + mvVec, player.p2 + mvVec);

		if (player.p0.x < field.x || player.p0.x > field.x + field.w || player.p0.y < field.y || player.p0.y > field.y + field.h)
		{
			player = Triangle(player.p0 - mvVec, player.p1 - mvVec, player.p2 - mvVec); // 枠外に出たときの処理
		}

		
		if (KeySpace.down()) // プレイヤーの弾丸の発射処理
		{
			playerBullet.push_back(Rect(player.p0.x - bulletWidth / 2, player.p0.y, bulletWidth, bulletHeight)); // 動的配列の最後尾に追加
			if (playerBullet.size() > playerBulletLimit) // 動的配列の要素数は5個以上だったら
			{
				playerBullet.pop_front(); // 先頭から弾丸を削除(古いものから)
			}
		}

		for (int i : step(playerBullet.size()))
		{
			playerBullet[i].pos.y -= bulletSpeed;
		}

		if (enemy.size() <= enemyLimit)
		{
			enemy.push_back(Circle(Vec2(Random() * field.w + field.x, field.y), 10));
		}

		for (int i : step(enemy.size()))
		{
			enemy[i] = Circle(enemy[i].center + Vec2(RandomInt8() % 2, 3), enemyWidth); // 敵の位置を更新
			if (RandomBool(0.05) && enemyBullet.size() <= enemyBulletLimit)
			{
				enemyBullet.push_back(Rect(enemy[i].center.x, enemy[i].center.y, bulletWidth, bulletHeight));
			}
			if (enemy[i].center.x < field.x || enemy[i].center.x > field.x + field.w || enemy[i].center.y > field.y + field.h)
			{
				enemy.erase(enemy.begin() + i); // 領域外に出た敵は消す
			}
			
			for (int j : step(playerBullet.size()))
			{
				if (enemy[i].intersects(playerBullet[j])) // 敵が弾丸と重なっているかどうか
				{
					enemy.erase(enemy.begin() + i); // 弾丸に当たった敵は消す
					playerBullet.erase(playerBullet.begin() + j); // 弾丸を消す
				}
			}
		}

		for (int i : step(enemyBullet.size()))
		{
			enemyBullet[i].pos.y += bulletSpeed;
			if (player.intersects(enemy[i]) && (!invincible))
			{
				playerHP -= bulletDamage;
				invincible = true;
				invincibleTimer = invincibleFrame;
				enemyBullet.erase(enemyBullet.begin() + i);
			}
		}

		// 無敵時間の処理
		if (invincible)
		{
			invincibleTimer--;
			invincible = (invincibleTimer <= 0);
		}


		player.draw();
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D Slack (ユーザコミュニティ) への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
