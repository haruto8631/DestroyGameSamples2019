#pragma once

#include "Common.hpp"
#include "ModLoader.hpp"


class Select : public MyApp::Scene
{
public:
	// ������
	Select(const InitData& init) : IScene(init)
	{
		const JSONReader json(U"Mods/panjan.json");
		getData().panjanNum = json.arrayCount();
		modLoader.loadPanjan(json);

	}


	void update() override
	{

	}


	// �`��
	void draw() const override
	{

	}





private:
	JSONValue jsonData;
	ModLoader modLoader;
};