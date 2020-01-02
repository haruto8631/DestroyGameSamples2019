#pragma once

#include  "Common.hpp"


#define LINE_WIDTH 200


class Course
{
public :
	Course()
	{

	}


	/// <summary>
	/// コースを生成する関数
	/// points[0]~[N]までの座標を加算していきコースを形成する
	/// </summary>
	void makeCourse(Array<Vec2> points, Vec2 offset)
	{
		this->offset = offset;
		rawData = points;
		directDistance = Vec2(0, 0);
		coursePath.clear();
		coursePath.push_back(points[0]);
		distance.push_back(points[0].length());
		totalDistance = points[0].length();
		directDistance += Abs(points[0]);
		for (int i = 1; i < points.size(); i++)
		{
			coursePath.push_back(coursePath[i - 1] + points[i]);
			distance.push_back(points[i].length());
			totalDistance += points[i].length();
		}
		course = LineString(coursePath);
		currentPos = rawData[0];
	}


	/// <summary>
	/// 現在コースのどこにいるかを更新する
	/// </summary>
	/// <param name="percent"> 0~1.0の間で書く </param>
	void updateProgress(double percent)
	{
		if (percent < 0)
		{
			percent = 0;
		}
		else if (percent > 1)
		{
			percent = 1;
		}
		double currentDistance = totalDistance * percent;
		double temp = 0;
		for (int i = 0; i < coursePath.size(); i++)
		{
			temp += distance[i];
			if (temp >= currentDistance)
			{
				temp -= currentDistance;
				currentPos = coursePath[i] - (rawData[i] * (temp / distance[i]));
				break;
			}
		}
	}


	Vec2 getCurrentPos()
	{
		return currentPos;
	}


	Vec2 getSidePos(Side side)
	{
		switch (side)
		{
		case Side::Left:
			return currentPos.rotated(-90_deg).setLength(LINE_WIDTH / 4);
		case Side::Right:
			return currentPos.rotated(90_deg).setLength(LINE_WIDTH / 4);
		default:
			return Vec2(0, 0);
		}
	}


	void draw() const
	{
		course.movedBy(-currentPos + offset).draw(LINE_WIDTH, Color(50, 50, 50));
		course.movedBy(-currentPos + offset).draw(LineStyle::SquareDot, 10, Color(255, 255, 255));
	}


private:

	Array<Vec2> coursePath;
	Array<Vec2> rawData;
	Array<double> distance;
	double totalDistance;
	LineString course;
	Vec2 currentPos;
	Vec2 offset;
	Vec2 directDistance;
	Vec2 direction;

};