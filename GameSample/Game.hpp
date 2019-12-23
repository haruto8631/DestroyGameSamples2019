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
	// ������
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
		player.update(); // Player�̏��X�V

		if (enemy.size() <= ENEMY_LIMIT)
		{
			if (RandomBool(0.05))
			{
				enemy.push_back(Enemy(Vec2(Random() * field.w + field.x, field.y), Vec2(RandomInt8() % 2, 2), 20));
			}
		}


		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i].update(); // �G�̏��X�V

			// �G���łe�ۂ𔭐�������
			if (RandomBool(0.01) && (!enemy[i].dead()))
			{
				enemyBullet.push_back(Bullet(enemy[i].getEnemyPosition(), Vec2(0, 20), 20, Color(255, 40, 40)));
				if (enemyBullet.size() > ENEMY_BULLET_LIMIT)
				{
					enemyBullet.pop_front();
				}
			}

			// �g�O�A���邢�͎��񂾓G����n������
			if (enemy[i].dead() || enemy[i].getEnemyPosition().x < field.x || enemy[i].getEnemyPosition().x > field.x + field.w || enemy[i].getEnemyPosition().y > field.y + field.h)
			{
				enemy.erase(enemy.begin() + i);
			}
		}
		
		// �v���C���[�̒e�ۂ̔��ˏ���
		if (KeySpace.down())
		{
			// ���I�z��̍Ō���ɒǉ�
			playerBullet.push_back(Bullet(player.getPlayerPosition(), Vec2(0, -10), 30));

			// ���I�z��̗v�f����5�ȏゾ������
			if (playerBullet.size() > PLAYER_BULLET_LIMIT)
			{
				playerBullet.pop_front(); // �擪����e�ۂ��폜(�Â����̂���)
			}
		}

		for (int i = 0; i < playerBullet.size(); i++)
		{
			playerBullet[i].update(); // �v���C���[�̒e�ۂ̈ړ�

			for (int j = 0; j < enemy.size(); j++)
			{
				// �v���C���[�̒e�ƓG�̓����蔻��͐ڐG������
				if (playerBullet[i].getCollision().intersects(enemy[j].getCollision()))
				{
					enemy[j].hit(playerBullet[i].hitBullet());
					getData().score += 100;
				}
			}
		}

		for (int i = 0; i < enemyBullet.size(); i++)
		{
			enemyBullet[i].update(); // �G�̒e�ۂ̈ړ�

			// �v���C���[�ƒe�ۂ̓����蔻�肪�d�Ȃ����Ƃ�
			if (player.getCollision().intersects(enemyBullet[i].getCollision()))
			{
				player.hit(enemyBullet[i].hitBullet());
				hpBar.changeHP(player.getHP());
			}
		}

		// �v���C���[�����񂾂猋�ʉ�ʂɑJ��
		if (player.dead())
		{
			changeScene(State::Result, 500);
		}
	}


	// �`��
	void draw() const override
	{
		// ���@�̒e�ۂ̕`��
		for (int i = 0; i < playerBullet.size(); i++)
		{
			if (!(playerBullet[i].dead()))
			{
				playerBullet[i].draw();
			}
		}

		// �G�@�̒e�ۂ̕`��
		for (int i = 0; i < enemyBullet.size(); i++)
		{
			if (!(enemyBullet[i].dead()))
			{
				enemyBullet[i].draw();
			}
		}

		// �G�@�̕`��
		for (int i = 0; i < enemy.size(); i++)
		{
			if (!enemy[i].dead())
			{
				enemy[i].draw();
			}
		}

		player.draw(); // ���@�̕`��
		field.drawFrame(0, 200, Color(0, 0, 0)).drawFrame(0, 5, Color(255, 255, 255)); // �g��g�O�̕`��
		hpBar.draw(); // HP�̕`��
		FontAsset(U"Score")(U"Score : " + Format(getData().score)).draw(0, 0, Color(255, 255, 255)); // Score�̕`��
	}





private:
	Player player; // ���@
	Array<Enemy> enemy; // �G�̃��X�g
	Array<Bullet> playerBullet; // ���@�̒e�ۂ̃��X�g
	Array<Bullet> enemyBullet; // �G�̒e�ۂ̃��X�g
	HPBar hpBar; // HP�o�[
	Rect field; // �g
};