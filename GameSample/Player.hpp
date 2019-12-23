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
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="defaultPosition"> ���@�̈ʒu </param>
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
	/// �R���X�g���N�^
	/// </summary>
	Player()
	{

	}


	// �X�V
	void update() 
	{
		// W�L�[�ŏ�Ɉړ�
		if (KeyW.pressed())
		{
			playerPosition.y -= speed;

			// �ړ��̈�𐧌�
			if (playerPosition.y <= playArea.y)
			{
				playerPosition.y += speed; // �͂ݏo������߂�
			}
		}

		// S�L�[�ŉ��Ɉړ�
		if (KeyS.pressed())
		{
			playerPosition.y += speed;

			// �ړ��̈�𐧌�
			if (playerPosition.y >= playArea.y + playArea.h)
			{
				playerPosition.y -= speed; // �͂ݏo������߂�
			}
		}

		// A�L�[�ō��Ɉړ�
		if (KeyA.pressed())
		{
			playerPosition.x -= speed;

			// �ړ��̈�𐧌�
			if (playerPosition.x <= playArea.x)
			{
				playerPosition.x += speed; // �͂ݏo������߂�
			}
		}

		// D�L�[�ŉE�Ɉړ�
		if (KeyD.pressed())
		{
			playerPosition.x += speed;

			// �ړ��̈�𐧌�
			if (playerPosition.x >= playArea.x + playArea.w)
			{
				playerPosition.x -= speed; // �͂ݏo������߂�
			}
		}

		// ��e��̖��G���Ԃ̏���
		if (invincible)
		{
			invincibleTimer--;
			if (invincibleTimer <= 0)
			{
				invincible = false;
			}
		}

		setBothPoints(playerPosition); // �O�p�`�̗��[�̍��W���Đݒ�
		collision = Triangle(playerPosition, leftmostPoint, rightmostPoint); // ���@�̈ʒu���Đݒ�
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
	// ���@��HP�𑝂₵���茸�炵����ł���
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
	/// ���@��HP��ύX����
	/// </summary>
	/// <param name="hp"> ���@��HP </param>
	void setHP(int hp)
	{
		hitPoint = hp;
	}



	/// <summary> 
	/// ���@�̃T�C�Y��ύX����
	/// </summary>
	/// <param name="size"> ���@�̃T�C�Y </param>
	void setSize(int size)
	{
		width = size;
		height = size;
	}


	/// <summary> 
	/// ���@�̃X�s�[�h�̕ύX
	/// </summary>
	/// <param name="speed"> ���@�̃X�s�[�h </param>
	void setSpeed(int speed)
	{
		this->speed = speed;
	}


	/// <summary> 
	/// HP�o�[���쐬����
	/// </summary>
	/// <param name="posX"> HP�o�[�̍���[��x���W </param>
	/// <param name="posY"> HP�o�[�̍���[��y���W </param>
	/// <param name="width"> HP�o�[�̕� </param>
	/// <param name="height"> HP�o�[�̍��� </param>
	void setPlayArea(int x, int y, int width, int height)
	{
		playArea = Rect(x, y, width, height);
	}



	/// <summary> 
	/// ���@�̐�[�̍��W��Vec2�^�Ŏ擾����
	/// </summary>
	/// <return> ���@�̒����̍��W </return>
	Vec2 getPlayerPosition()
	{
		return playerPosition;
	}


	/// <summary>
	/// ���@�̓����蔻���Triangle�^���擾����
	/// </summary>
	/// <return> ���@�̎O�p�`��Ԃ� </return>
	Triangle& getCollision()
	{
		return collision;
	}


	/// <summary>
	/// ���݂�HP��Ԃ�
	/// </summary>
	int getHP()
	{
		return hitPoint;
	}



private:
	Vec2 playerPosition; // ���@�̐�[�̍��W
	Vec2 leftmostPoint; // ���@�̍��[�̍��W
	Vec2 rightmostPoint; // ���@�̉E���̍��W
	Triangle collision; // ���@�̓����蔻��
	Rect playArea; // ���@���ړ��\�Ȕ͈�

	int speed; // ���@�̃X�s�[�h
	int hitPoint; // ���@��HP
	int width; // ���@�̕�
	int height; // ���@�̍���
	int invincibleTimer; // ���G���Ԃ��Ǘ�����^�C�}�[
	bool invincible; // ���G���ǂ��� 


	/// <summary> 
	/// ���@�̗��[�̍��W��ݒ肷��
	/// </summary>
	/// <param name="CenterPosition"> ���@�̐�[�̍��W </param>
	void setBothPoints(Vec2 CenterPosition)
	{
		leftmostPoint = Vec2(CenterPosition.x - (width / 2), CenterPosition.y + height);
		rightmostPoint = Vec2(CenterPosition.x + (width / 2), CenterPosition.y + height);
	}
};