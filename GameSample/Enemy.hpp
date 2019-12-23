#pragma once

#include "Common.hpp"
#include "Bullet.hpp"


#define DEFAULT_ENEMY_SIZE 15
#define DEFAULT_INVINCIBLE_FRAME 60

class Enemy
{
public:

	/// <summary> 
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="defaultPosition"> �G�@�̈ʒu </param>
	Enemy(Vec2 defaultPosition, Vec2 defaultDirection, int hp)
	{
		enemyPosition = defaultPosition;
		enemyDirection = defaultDirection;
		hitPoint = hp;
		this->size = DEFAULT_ENEMY_SIZE;
	}


	// �X�V
	void update()
	{
		enemyPosition.x += enemyDirection.x;
		enemyPosition.y += enemyDirection.y;
		collision = Circle(enemyPosition, size); // �G�@�̈ʒu���Đݒ�

		if (invincible)
		{
			invincibleTimer--;
			if (invincibleTimer <= 0)
			{
				invincible = false;
			}
		}
	}


	// �`��
	void draw() const
	{
		collision.draw();
	}


	/// <summary>
	/// �G�@������ł��邩�ǂ�����Bool�ŕԂ�
	/// </summary>
	/// <return> ����ł��邩�ǂ��� </return>
	bool dead() const
	{
		return (hitPoint <= 0);
	}


	/// <summary> 
	/// �_���[�W���󂯂�Ƃ��Ɏ��s����֐�
	// �G�@��HP�𑝂₵���茸�炵����ł���
	/// </summary>
	/// <param name="damage"> �_���[�W�̒l </param>
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
	/// �G�@�̃T�C�Y��ύX����
	/// </summary>
	/// <param name="size"> �G�@�̃T�C�Y </param>
	void setSize(int size)
	{
		this->size = size;
	}


	/// <summary> 
	/// �G�@�̃X�s�[�h�̕ύX
	/// </summary>
	/// <param name="speed"> �G�@�̃X�s�[�h </param>
	void setSpeed(int speed)
	{
		this->speed = speed;
	}


	/// <summary> 
	/// �G�@�̒����̍��W��Vec2�^�Ŏ擾����
	/// </summary>
	/// <return> �G�@�̒����̍��W </return>
	Vec2 getEnemyPosition()
	{
		return enemyPosition;
	}


	/// <summary>
	/// �G�@�̓����蔻��̓����蔻����擾����
	/// </summary>
	/// <return> �G�@�̉~��Ԃ� </return>
	Circle& getCollision()
	{
		return collision;
	}



private:
	Vec2 enemyPosition; // �G�@�̐�[�̍��W
	Vec2 enemyDirection;
	Circle collision; // �G�@�̓����蔻��

	int speed; // �G�@�̃X�s�[�h
	int hitPoint; // �G�@��HP
	int size; // �G�@�̔��a
	int invincibleTimer; // ���G���Ԃ��Ǘ�����^�C�}�[
	bool invincible; // ���G���ǂ��� 

};