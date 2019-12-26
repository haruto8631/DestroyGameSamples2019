#pragma once

#include "Common.hpp"


class ModLoader
{
public:
	// コンストラクタ
	ModLoader()
	{
	}

	Array<String> loadPanjan(const JSONValue& json)
	{
		for (const auto& object : json.objectView())
		{
			switch (object.value.getType())
			{
			case JSONValueType::Empty:
				throw "Explosion Panjan0";
				break;
			case JSONValueType::Null:
				throw "Explosion Panjan1";
				break;
			case JSONValueType::Array:
				for (const auto& element : object.value.arrayView())
				{
					nameDic.push_back(registerPanjan(element));
				}
				break;
			default:
				throw "Pancoro~";
				break;
			}
		}
	}


	String registerPanjan(const JSONValue json)
	{
		String panjanName, wheelPath, basePath;

		for (const auto& object : json.objectView())
		{
			if (object.name == U"name")
			{
				panjanName = object.value.getString();
			}
			else if (object.name == U"wheel")
			{
				wheelPath = object.value.getString();
			}
			else if (object.name == U"base")
			{
				basePath = object.value.getString;
			}
		}

		TextureAsset::Register(panjanName + U"_w", wheelPath);
		TextureAsset::Register(panjanName + U"_b", basePath);
		return panjanName;
	}


private:
	Array<String> nameDic;
};