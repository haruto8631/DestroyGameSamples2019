#pragma once

#include "Common.hpp"

class Tachometer
{
public:
	Tachometer()
	{
	}


	Tachometer(Vec2 position, int size, Array<double> speedLimits)
	{
		meterBase = Texture(Resource(U"texture/TachometerBase.png")).resized(size);
		meterNeedle = Texture(Resource(U"texture/MeterNeedle.png")).resized(size * 0.8);
		this->position = position;
		this->speedLimits = speedLimits;
	}


	void update(double speed, int gear)
	{
		this->speed = speed;
		this->gear = gear;
	}


	void draw() const
	{
		meterBase.drawAt(position);
		FontAsset(U"Meter")(Format(speed * 200) + U"km/h").drawAt(position - Vec2(0, 100));
		meterNeedle.rotated(-45_deg + (90_deg * (speed / speedLimits[gear - 1]))).drawAt(position);
	}
	


private:
	TextureRegion meterBase;
	TextureRegion meterNeedle;
	Vec2 position;
	Array<double> speedLimits;
	int gear;
	double speed;
};