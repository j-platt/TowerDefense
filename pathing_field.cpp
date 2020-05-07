#include "pathing_field.h"

#include <assert.h>
#include <algorithm>
#include <queue>

using namespace tower_defense;

namespace tower_defense
{
	pathing_field::pathing_field()
	{
		unsigned rowIndex = 0;
		for(std::array<pathing_point, fieldYDimension>& row : vectorField)
		{
			unsigned columnIndex = 0;
			std::generate(std::begin(row), std::end(row),
				[rowIndex, &columnIndex]() 
			{ 
				pathing_point reply;
				reply.x = columnIndex;
				reply.y = rowIndex;
				++columnIndex;
				return reply;
			});
			++rowIndex;
		}
	}
}

pathing_point tower_defense::center_of_tile(board_coordinate const& tileInQuestion)
{
	unsigned const xCoord = (tileInQuestion.x * tileXDimension) + (tileXDimension / 2);
	unsigned const yCoord = (tileInQuestion.y * tileYDimension) + (tileYDimension / 2);
	pathing_point reply;
	reply.x = xCoord;
	reply.y = yCoord;
	return reply;
}

namespace
{
	std::vector<pathing_point> transform_to_pathing_points(std::vector<board_coordinate> const& subjects)
	{
		std::vector<pathing_point> reply;
		reply.reserve(subjects.size());
		for(board_coordinate const& subject : subjects)
		{
			reply.push_back(center_of_tile(subject));
		}
		return reply;
	}

	void extend_pathing_to_adjacent_points(pathing_field& field, pathing_point const& originPoint, std::queue<pathing_point>& activePoints)
	{
		bool hasSpaceToLeft = originPoint.x > 0;
		bool hasSpaceToRight = originPoint.x < (fieldXDimension - 1);
		bool hasSpaceAbove = originPoint.y > 0;
		bool hasSpaceBelow = originPoint.y < (fieldYDimension - 1);
		if(hasSpaceAbove)
		{
			if(hasSpaceToLeft)
			{
				pathing_point& topLeft = field.vectorField[originPoint.y - 1][originPoint.x - 1];
				if(!topLeft.beenSet)
				{
					topLeft.pathing.facing = directions::southeast;
					topLeft.beenSet = true;
					activePoints.push(topLeft);
				}
			}

			pathing_point& top = field.vectorField[originPoint.y - 1][originPoint.x];
			if(!top.beenSet)
			{
				top.pathing.facing = directions::south;
				top.beenSet = true;
				activePoints.push(top);
			}

			if(hasSpaceToRight)
			{
				pathing_point& topRight = field.vectorField[originPoint.y - 1][originPoint.x + 1];
				if(!topRight.beenSet)
				{
					topRight.pathing.facing = directions::southwest;
					topRight.beenSet = true;
					activePoints.push(topRight);
				}
			}
		}

		if(hasSpaceToLeft)
		{
			pathing_point& left = field.vectorField[originPoint.y][originPoint.x - 1];
			if(!left.beenSet)
			{
				left.pathing.facing = directions::east;
				left.beenSet = true;
				activePoints.push(left);
			}
		}

		if(hasSpaceToRight)
		{
			pathing_point& right = field.vectorField[originPoint.y][originPoint.x + 1];
			if(!right.beenSet)
			{
				right.pathing.facing = directions::west;
				right.beenSet = true;
				activePoints.push(right);
			}
		}

		if(hasSpaceBelow)
		{
			if(hasSpaceToLeft)
			{
				pathing_point& bottomLeft = field.vectorField[originPoint.y + 1][originPoint.x - 1];
				if(!bottomLeft.beenSet)
				{
					bottomLeft.pathing.facing = directions::northeast;
					bottomLeft.beenSet = true;
					activePoints.push(bottomLeft);
				}
			}

			pathing_point& bottom = field.vectorField[originPoint.y + 1][originPoint.x];
			if(!bottom.beenSet)
			{
				bottom.pathing.facing = directions::north;
				bottom.beenSet = true;
				activePoints.push(bottom);
			}

			if(hasSpaceToRight)
			{
				pathing_point& bottomRight = field.vectorField[originPoint.y + 1][originPoint.x + 1];
				if(!bottomRight.beenSet)
				{
					bottomRight.pathing.facing = directions::northwest;
					bottomRight.beenSet = true;
					activePoints.push(bottomRight);
				}
			}
		}
	}
}//end anonymous namespace

pathing_field_ptr tower_defense::calculate_pathing(board const& source, std::vector<board_coordinate> const& goals)
{
	pathing_field_ptr reply = std::make_unique<pathing_field>();
	std::vector<pathing_point> initialPoints = transform_to_pathing_points(goals);

	std::for_each(std::begin(initialPoints), std::end(initialPoints),
		[](pathing_point& point) { point.beenSet = true; point.pathing.facing = directions::goal; });
	std::for_each(std::begin(initialPoints), std::end(initialPoints),
		[&reply](pathing_point const& point) { reply->vectorField[point.y][point.x] = point; });

	std::queue<pathing_point> activePoints;
	std::for_each(std::begin(initialPoints), std::end(initialPoints), [&activePoints](pathing_point const& point) { activePoints.push(point); });
	
	while(!activePoints.empty())
	{
		extend_pathing_to_adjacent_points(*reply, activePoints.front(), activePoints);
		activePoints.pop();
	}
	return reply;
}