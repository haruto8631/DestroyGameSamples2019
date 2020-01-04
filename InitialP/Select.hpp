#pragma once

#include "Common.hpp"
#include "ModLoader.hpp"




class Select : public MyApp::Scene
{
public:
	// ������
	Select(const InitData& init) : IScene(init)
	{
		selectedTileNum = 0;
		getData().panjanNum = 1;
		const JSONReader json(U"Mods/panjan.json");
		if (json) 
		{
			loadModPanjan(json);
		}
		panjanNum = getData().panjanNum;
		panjanNames.push_front(U"TheGreatPanjandrum");
		TextureAsset::Register(U"TheGreatPanjandrum_b", Resource(U"texture/TheGreatPanjandrumBase.png"));
		TextureAsset::Register(U"TheGreatPanjandrum_w", Resource(U"texture/TheGreatPanjandrumWheel.png"));
		TextureAsset::Register(U"TheGreatPanjandrum_d", Resource(U"texture/TheGreatPanjandrum.jpg"));
		makeTileSelecter();
		updatePanjanInfo();
		textBox = Rect(10, 400, Scene::Width() - 20, 190 );
	}


	void update() override
	{
		if (KeyLeft.down())
		{
			selectedTileNum--;
			if (selectedTileNum < 0)
			{
				selectedTileNum = 0;
			}
			updatePanjanInfo();
		}

		if (KeyRight.down())
		{
			selectedTileNum++;
			if (selectedTileNum >= panjanNum)
			{
				selectedTileNum = panjanNum - 1;
			}
			updatePanjanInfo();
		}

		if (KeyEnter.down())
		{
			getData().panjanDictionary = panjanNames;
			getData().playerPanjanName = panjanNames[selectedTileNum];
			changeScene(State::Game);
		}
	}


	// �`��
	void draw() const override
	{
		
		for (int i = 0; i < selectedTileNum; i++)
		{
			panjanTiles[i].resized(160, 160).drawAt((selectedTileNum - i) * -160 + offset, 300);
		}
		panjanTiles[selectedTileNum].resized(200, 200).drawAt(offset, 280);
		for (int i = 1; i < panjanNum - selectedTileNum; i++)
		{
			panjanTiles[i].resized(160, 160).drawAt(i * 160 + offset + 20, 300);
		}
		textBox.draw(Color(255, 255, 255)).drawFrame(0, 5, Color(255, 255, 255)).drawFrame(5, 0, Color(0, 0, 0));
		FontAsset(U"PanjanName")(U"���O : " + panjanNames[selectedTileNum]).draw(30, 420, Color(0, 0, 0));
		FontAsset(U"PanjanInfo")(panjanInfo).draw(30, 450, Color(0, 0, 0));
	}


private:
	int offset = 300;
	int selectedTileNum;
	int panjanNum;
	String panjanInfo;
	Rect textBox;

	JSONValue jsonData;
	ModLoader modLoader;
	Array<String> panjanNames;
	Array<Texture> panjanTiles;


	void loadModPanjan(const JSONValue& json)
	{
		panjanNames = modLoader.loadPanjan(json);
		getData().panjanNum += panjanNames.size();
	}


	void makeTileSelecter()
	{
		for (int i = 0; i < panjanNames.size(); i++)
		{
			panjanTiles.push_back(TextureAsset(panjanNames[i] + U"_d"));
		}
	}


	void updatePanjanInfo()
	{
		if (selectedTileNum == 0)
		{
			panjanInfo = U"�p���W�����h����(The Great Panjnadrum)�Ƃ́A\n��񎟐��E��풆�ɃC�M���X�R���J���������P�b�g���i���̗��㔚���ł���B\n";
			panjanInfo += U"��1.8�g�����y����l�߂��{�̂𒼌a3m�̎ԗւő}�񂾃{�r����̍\���B\n";
			panjanInfo += U"�ԗւ̃����ɑ������ꂽ�����̌Ō`�R�����P�b�g���[�^�[����Ăɕ��˂����邱�Ƃɂ���Ďԗւ���]�����đ��s����B\n";
			panjanInfo += U"2019�N12��(����)�ɂ����Ă��p���ʂɐ��܂����Z�p�҂����ɂ���Đ���Ɍ����J�����s���Ă���A\n��X�̐����̒��ł����a���p���ꂽ�p���W�����h���������邱�Ƃ��ł���\n";
			panjanInfo += U"�܂��A�ő��̃p���W�����h���������߂���uP1 Grand Prix�v���J�Â���Ă���B";
		}
		else
		{
			panjanInfo = U"Mod�ɂ���Ēǉ����ꂽ�p���W�����h����";
		}
	}
};