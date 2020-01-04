#pragma once

#include "Common.hpp"
#include "ModLoader.hpp"




class Select : public MyApp::Scene
{
public:
	// 初期化
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


	// 描画
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
		FontAsset(U"PanjanName")(U"名前 : " + panjanNames[selectedTileNum]).draw(30, 420, Color(0, 0, 0));
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
			panjanInfo = U"パンジャンドラム(The Great Panjnadrum)とは、\n第二次世界大戦中にイギリス軍が開発したロケット推進式の陸上爆雷である。\n";
			panjanInfo += U"約1.8トンの炸薬を詰めた本体を直径3mの車輪で挿んだボビン状の構造。\n";
			panjanInfo += U"車輪のリムに装着された多数の固形燃料ロケットモーターを一斉に噴射させることによって車輪を回転させて走行する。\n";
			panjanInfo += U"2019年12月(現在)においても英国面に染まった技術者たちによって盛んに研究開発が行われており、\n我々の生活の中でも平和利用されたパンジャンドラムを見ることができる\n";
			panjanInfo += U"また、最速のパンジャンドラムを決める大会「P1 Grand Prix」も開催されている。";
		}
		else
		{
			panjanInfo = U"Modによって追加されたパンジャンドラム";
		}
	}
};