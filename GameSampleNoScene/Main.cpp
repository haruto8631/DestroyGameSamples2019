# include <Siv3D.hpp> // OpenSiv3D v0.4.2


void Main()
{
	constexpr int playerWidth = 20;
	constexpr int playerHeight = 20;
	constexpr int playerSpeed = 10;
	constexpr int playerMaxHP = 100;
	constexpr int playerBulletLimit = 5;
	constexpr int invincibleFrame = 60;
	constexpr int enemyWidth = 20;
	constexpr int enemySpeed = 3;
	constexpr int enemyLimit = 10;
	constexpr int enemyBulletLimit = 40;
	constexpr int bulletWidth = 6;
	constexpr int bulletHeight = 12;
	constexpr int bulletSpeed = 8;
	constexpr int bulletDamage = 20;

	int playerHP = playerMaxHP;
	int invincibleTimer = invincibleFrame;
	bool invincible = false;

	int state = 0; // シーン遷移の管理用変数
	int score = 0;

	Triangle player = Triangle(Scene::Center(), Scene::Center() + Vec2(playerWidth / -2, playerHeight), Scene::Center() + Vec2(playerWidth / 2, playerHeight));
	Vec2 mvVec; // playerの動く方向
	Array<Circle> enemy;
	Array<Vec2> enemyDirection;
	Array<Rect> playerBullet;
	Array<Rect> enemyBullet;
	Rect field = Rect(50, 50, 500, 500);
	Rect hpFrame = Rect(600, 550, 100, 25);
	Rect hpBar = Rect(600, 550, 100, 25);
	

	// タイトルを設定
	Window::SetTitle(U"破壊ゲームさんぷる");

	// 背景色を設定
	Scene::SetBackground(Color(0, 0, 0));

	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 60, U"example/font/NotoSansCJKjp/NotoSansCJKjp-Regular.otf");
	FontAsset::Register(U"Score", 30, Typeface::Regular);
	FontAsset::Register(U"HP", 20, Typeface::Regular);


	// メインループ
	while (System::Update())
	{
		// 初期化 (一回ゲームオーバーした後用)
		if (state == -1)
		{
			playerHP = playerMaxHP;
			invincibleTimer = invincibleFrame;
			invincible = false;
			state = 0;
			score = 0;
			player = Triangle(Scene::Center(), Scene::Center() + Vec2(playerWidth / -2, playerHeight), Scene::Center() + Vec2(playerWidth / 2, playerHeight));
			enemy.clear();
			enemyDirection.clear();
			playerBullet.clear();
			enemyBullet.clear();
			field = Rect(50, 50, 500, 500);
			hpFrame = Rect(600, 550, 100, 25);
			hpBar = Rect(600, 550, 100, 25);
		}

		// タイトル画面
		if (state == 0)
		{
			FontAsset(U"Title")(U"破壊ゲームサンプル").drawAt(Scene::Center() + Vec2(0, -100));
			if (SimpleGUI::ButtonAt(U"始める", Scene::Center()))
			{
				state = 1;
			}
			if (SimpleGUI::ButtonAt(U"終わる", Scene::Center() + Vec2(0, 50)))
			{
				System::Exit();
			}
			continue; // 移行の処理を無視して、次のループに入る
		}

		// 結果画面
		if (state == 2)
		{
			if (SimpleGUI::ButtonAt(U"タイトルに戻る", Scene::Center() + Vec2(0, 100)))
			{
				state = -1; // 忘れずに初期化した後、タイトルに戻る
			}
			if (SimpleGUI::ButtonAt(U"アプリを終了する", Scene::Center() + Vec2(0, 200)))
			{
				System::Exit();
			}
			FontAsset(U"Score")(U"あなたのスコア").drawAt(Scene::Center() + Vec2(0, -100));
			FontAsset(U"Score")(Format(score)).drawAt(Scene::Center());
			continue; // 移行の処理を無視して、次のループに入る
		}

		// 自機の移動処理
		mvVec = Vec2(0, 0);
		if (KeyA.pressed()) { mvVec -= Vec2(playerSpeed, 0); }
		if (KeyD.pressed()) { mvVec += Vec2(playerSpeed, 0); }
		if (KeyW.pressed()) { mvVec -= Vec2(0, playerSpeed); }
		if (KeyS.pressed()) { mvVec += Vec2(0, playerSpeed); }
		player = Triangle(player.p0 + mvVec, player.p1 + mvVec, player.p2 + mvVec);

		// 枠外に出たとき
		if (player.p0.x < field.x || player.p0.x > field.x + field.w || player.p0.y < field.y || player.p0.y > field.y + field.h)
		{
			player = Triangle(player.p0 - mvVec, player.p1 - mvVec, player.p2 - mvVec); // 1フレーム前の位置に戻る
		}

		if (KeySpace.down()) // プレイヤーの弾丸の発射処理
		{
			playerBullet.push_back(Rect(player.p0.x - bulletWidth / 2, player.p0.y, bulletWidth, bulletHeight)); // 動的配列の最後尾に追加
			if (playerBullet.size() > playerBulletLimit) // 動的配列の要素数は5個以上だったら
			{
				playerBullet.pop_front(); // 先頭から弾丸を削除(古いものから)
			}
		}

		for (int i = 0; i < playerBullet.size(); i++)
		{
			playerBullet[i].pos.y -= bulletSpeed; // 弾丸の移動
		}

		// 敵の数が上限に達していない時
		if (RandomBool(0.1) && enemy.size() < enemyLimit)
		{
			enemy.push_back(Circle(Vec2(Random<int32>(field.x, field.x + field.w), field.y), 10)); // 敵を適当な位置に生成
			enemyDirection.push_back(Vec2(RandomInt8() % 2, enemySpeed)); // 生成した敵に対して動く方向を決める
		}

		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i] = Circle(enemy[i].center + enemyDirection[i], enemyWidth); // 敵の位置を更新
			if (RandomBool(0.01) && enemyBullet.size() <= enemyBulletLimit)
			{
				enemyBullet.push_back(Rect((int)(enemy[i].x - bulletWidth / 2), enemy[i].y, bulletWidth, bulletHeight)); // enemy[i]の座標に弾丸を作る
			}
			if (enemy[i].x < field.x || enemy[i].x > (field.x + field.w) || enemy[i].y > (field.y + field.h))
			{
				enemy.erase(enemy.begin() + i); // 領域外に出た敵は消す
				enemyDirection.erase(enemyDirection.begin() + i); // 領域外に出た敵の進む方向も消す
				continue;
			}
			
			for (int j = 0; j < playerBullet.size(); j++)
			{
				if (enemy[i].intersects(playerBullet[j])) // 敵が弾丸と重なっているかどうか
				{
					score += 100;
					enemy.erase(enemy.begin() + i); // 弾丸に当たった敵は消す
					enemyDirection.erase(enemyDirection.begin() + i); // 弾丸に当たった敵の進む方向も消す
					playerBullet.erase(playerBullet.begin() + j); // 弾丸を消す
				}
			}
		}

		for (int i = 0; i < enemyBullet.size(); i++)
		{
			enemyBullet[i].pos.y += bulletSpeed; // 敵の弾丸の位置を更新
			if (player.intersects(enemy[i]) && (!invincible)) // 敵の弾丸が自機に重なった時　かつ　自機が無敵ではないとき
			{
				playerHP -= bulletDamage;
				hpBar = Rect(hpFrame.x, hpFrame.y, hpFrame.w * ((double)playerHP / playerMaxHP), hpFrame.h); // HP表示の変更
				invincible = true; // 自機を無敵状態にする
				invincibleTimer = invincibleFrame;
				enemyBullet.erase(enemyBullet.begin() + i); // 自機に当たった弾丸は消す
				continue;
			}

			// 敵機の弾丸が枠の底辺のy座標に達したら
			if (enemyBullet[i].pos.y > field.y + field.h)
			{
				enemyBullet.erase(enemyBullet.begin() + i); // 敵の弾丸を動的配列から削除する
			}
		}

		// 無敵時間の処理
		if (invincible)
		{
			invincibleTimer--;
			// invincibleTimerが0になると、invincibleにfalseが代入される
			invincible = (invincibleTimer >= 0);
		}

		// 自機が死んだら
		if (playerHP <= 0)
		{
			state = 2; // 結果画面に遷移
		}

		// ここから下は全て描画処理
		for (int i = 0; i < enemyBullet.size(); i++)
		{
			enemyBullet[i].draw(Color(255, 20, 20));
		}

		for (int i = 0; i < playerBullet.size(); i++)
		{
			playerBullet[i].draw(Color(127, 127, 127));
		}

		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i].draw(Color(255, 255, 255));
		}

		player.draw();
		field.drawFrame(0, 300, Color(0, 0, 0)).drawFrame(0, 5, Color(255, 255, 255));
		hpFrame.draw(Color(0, 0, 0)).drawFrame(0, 3, Color(255, 255, 255));
		hpBar.draw(Color(40, 255, 40));
		FontAsset(U"Score")(U"Score : " + Format(score)).draw(0, 0);
		FontAsset(U"HP")(U"HP : " + Format(playerHP)).draw(600, 520);
	}
}
