#pragma once

#include "Common.hpp"


class ModLoader
{
public:
	// コンストラクタ
	ModLoader()
	{
	}

	static Array<String> loadPanjan(const JSONValue& json)
	{
		Array<String> nameDic;
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

		return nameDic;
	}


	static String registerPanjan(const JSONValue& json)
	{
		String panjanName, wheelPath, basePath, displayImagePath;

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
				basePath = object.value.getString();
			}
			else if (object.name == U"displayImage")
			{
				displayImagePath = object.value.getString();
			}
		}

		TextureAsset::Register(panjanName + U"_w", wheelPath);
		TextureAsset::Register(panjanName + U"_b", basePath);
		TextureAsset::Register(panjanName + U"_d", displayImagePath);
		return panjanName;
	}

};