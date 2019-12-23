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
	// ‰Šú‰»
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
		player.update(); // Player‚Ìî•ñXV

		if (enemy.size() <= ENEMY_LIMIT)
		{
			if (RandomBool(0.05))
			{
				enemy.push_back(Enemy(Vec2(Random() * field.w + field.x, field.y), Vec2(RandomInt8() % 2, 2), 20));
			}
		}


		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i].update(); // “G‚Ìî•ñXV

			// “G‚ª‘Å‚Â’eŠÛ‚ğ”­¶‚³‚¹‚é
			if (RandomBool(0.01) && (!enemy[i].dead()))
			{
				enemyBullet.push_back(Bullet(enemy[i].getEnemyPosition(), Vec2(0, 20), 20, Color(255, 40, 40)));
				if (enemyBullet.size() > ENEMY_BULLET_LIMIT)
				{
					enemyBullet.pop_front();
				}
			}

			// ˜gŠOA‚ ‚é‚¢‚Í€‚ñ‚¾“G‚ğŒãn––‚·‚é
			if (enemy[i].dead() || enemy[i].getEnemyPosition().x < field.x || enemy[i].getEnemyPosition().x > field.x + field.w || enemy[i].getEnemyPosition().y > field.y + field.h)
			{
				enemy.erase(enemy.begin() + i);
			}
		}
		
		// ƒvƒŒƒCƒ„[‚Ì’eŠÛ‚Ì”­Ëˆ—
		if (KeySpace.down())
		{
			// “®“I”z—ñ‚ÌÅŒã”ö‚É’Ç‰Á
			playerBullet.push_back(Bullet(player.getPlayerPosition(), Vec2(0, -10), 30));

			// “®“I”z—ñ‚Ì—v‘f”‚Í5ŒÂˆÈã‚¾‚Á‚½‚ç
			if (playerBullet.size() > PLAYER_BULLET_LIMIT)
			{
				playerBullet.pop_front(); // æ“ª‚©‚ç’eŠÛ‚ğíœ(ŒÃ‚¢‚à‚Ì‚©‚ç)
			}
		}

		for (int i = 0; i < playerBullet.size(); i++)
		{
			playerBullet[i].update(); // ƒvƒŒƒCƒ„[‚Ì’eŠÛ‚ÌˆÚ“®

			for (int j = 0; j < enemy.size(); j++)
			{
				// ƒvƒŒƒCƒ„[‚Ì’e‚Æ“G‚Ì“–‚½‚è”»’è‚ÍÚG‚µ‚½
				if (playerBullet[i].getCollision().intersects(enemy[j].getCollision()))
				{
					enemy[j].hit(playerBullet[i].hitBullet());
					getData().score += 100;
				}
			}
		}

		for (int i = 0; i < enemyBullet.size(); i++)
		{
			enemyBullet[i].update(); // “G‚Ì’eŠÛ‚ÌˆÚ“®

			// ƒvƒŒƒCƒ„[‚Æ’eŠÛ‚Ì“–‚½‚è”»’è‚ªd‚È‚Á‚½‚Æ‚«
			if (player.getCollision().intersects(enemyBullet[i].getCollision()))
			{
				player.hit(enemyBullet[i].hitBullet());
				hpBar.changeHP(player.getHP());
			}
		}

		// ƒvƒŒƒCƒ„[‚ª€‚ñ‚¾‚çŒ‹‰Ê‰æ–Ê‚É‘JˆÚ
		if (player.dead())
		{
			changeScene(State::Result, 500);
		}
	}


	// •`‰æ
	void draw() const override
	{
		// ©‹@‚Ì’eŠÛ‚Ì•`‰æ
		for (int i = 0; i < playerBullet.size(); i++)
		{
			if (!(playerBullet[i].dead()))
			{
				playerBullet[i].draw();
			}
		}

		// “G‹@‚Ì’eŠÛ‚Ì•`‰æ
		for (int i = 0; i < enemyBullet.size(); i++)
		{
			if (!(enemyBullet[i].dead()))
			{
				enemyBullet[i].draw();
			}
		}

		// “G‹@‚Ì•`‰æ
		for (int i = 0; i < enemy.size(); i++)
		{
			if (!enemy[i].dead())
			{
				enemy[i].draw();
			}
		}

		player.draw(); // ©‹@‚Ì•`‰æ
		field.drawFrame(0, 200, Color(0, 0, 0)).drawFrame(0, 5, Color(255, 255, 255)); // ˜g‚â˜gŠO‚Ì•`‰æ
		hpBar.draw(); // HP‚Ì•`‰æ
		FontAsset(U"Score")(U"Score : " + Format(getData().score)).draw(0, 0, Color(255, 255, 255)); // Score‚Ì•`‰æ
	}





private:
	Player player; // ©‹@
	Array<Enemy> enemy; // “G‚ÌƒŠƒXƒg
	Array<Bullet> playerBullet; // ©‹@‚Ì’eŠÛ‚ÌƒŠƒXƒg
	Array<Bullet> enemyBullet; // “G‚Ì’eŠÛ‚ÌƒŠƒXƒg
	HPBar hpBar; // HPƒo[
	Rect field; // ˜g
};