#pragma once

#include "Common.hpp"

// インターフェース
class PanjandrumBase
{
public:
	PanjandrumBase()
	{

	}

	virtual void spawn(Texture wheel, Texture base, Vec2 spawnPos) = 0;
	virtual void rotates(Vec2 position) = 0;
	virtual void suicideBomb() = 0;
	virtual void draw() const = 0;
private:
	
};