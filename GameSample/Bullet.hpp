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
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="defaultPosition"> �����ʒu </param>
	/// <param name="direction"> �����Ƒ��x </param>
	/// <param name="tag"> ���̃N���X�ɂ����� </param>
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


	// �X�V
	void update()
	{
		position.x += direction.x;
		position.y += direction.y;
		collision = Rect(position.x - (width / 2), position.y, width, height);
	}


	// �`��
	void draw() const
	{
		collision.draw(color);
	}


	/// <summary> 
	/// �e�ۂ̐i�ތ����Ƒ��x��ύX����
	/// </summary>
	/// <param name="direction"> �����Ƒ��x </param>
	void changeDirection(Vec2 direction)
	{
		this->direction = direction;
	}


	/// <summary> 
	/// �e�ۂ̃T�C�Y��ύX����
	/// </summary>
	/// <param name="width"> �� </param>
	/// <param name="height"> ���� </param>
	void changeSize(int width, int height)
	{
		this->width = width;
		this->height = height;
	}


	/// <summary> 
	/// �e�ۂ̃_���[�W�ʂ�ύX����
	/// </summary>
	/// <param name="width"> �З́E�_���[�W�� </param>
	void changeDamage(int damage)
	{
		this->damage = damage;
	}


	/// <summary> 
	/// �e�ۂ̃_���[�W�ʂ��擾����
	/// </summary>
	int getDamage()
	{
		return damage;
	}


	/// <summary> 
	/// �e�ۂ̓����蔻����擾����
	/// </summary>
	Rect& getCollision()
	{
		return collision;
	}


	/// <summary> 
	/// �o���b�g�������ɓ����������Ƃ�m�点��
	/// �_���[�W�ʂ�Ԃ�
	/// </summary>
	/// <return> ���̒e�����_���[�W�� </return>
	int hitBullet()
	{
		hitPoint = 0;
		return damage;
	}


	/// <summary> 
	/// �e������ł��邩�ǂ�����Bool�ŕԂ�
	/// </summary>
	/// <return> ����ł��邩�ǂ��� </return>
	bool dead() const
	{
		return (hitPoint <= 0);
	}


private:
	Color color; // �e�ۂ̐F
	Rect collision; // �e�ۂ̓����蔻��
	Vec2 position; // �e�ۂ̈ʒu
	Vec2 direction; // �e�ۂ̌����E���x

	int damage; // �e�ۂ̎��_���[�W��
	int width; // �e�ۂ̕�
	int height; // �e�ۂ̍���
	int hitPoint; // �e�ۂ�HP
};