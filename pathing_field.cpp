#include "pathing_field.h"

#include <assert.h>

namespace tower_defense
{
	pathing_point::pathing_point(unsigned const x, unsigned const y) : isGoalPoint(false)
	{
		assert(x < fieldXDimension);
		assert(y < fieldYDimension);
	}
}

tower_defense::pathing_point tower_defense::center_of_tile(board_coordinate const& tileInQuestion)
{
	unsigned const xReply = (tileInQuestion.x * tileXDimension) + (tileXDimension / 2);
	unsigned const yReply = (tileInQuestion.y * tileYDimension) + (tileYDimension / 2);
	return pathing_point(xReply, yReply);
}

namespace
{
	std::vector<tower_defense::pathing_point> transform_to_pathing_points(std::vector<tower_defense::board_coordinate> const& subjects)
	{
		std::vector<tower_defense::pathing_point> reply;
		reply.reserve(subjects.size());
		for(tower_defense::board_coordinate const& subject : subjects)
		{
			reply.push_back(tower_defense::center_of_tile(subject));
		}
		return reply;
	}
}

tower_defense::pathing_field tower_defense::calculate_pathing(board const& source, std::vector<tower_defense::board_coordinate> const& goals)
{
	pathing_field reply;
	std::vector<pathing_point> activePoints;
	activePoints.reserve((fieldXDimension * fieldYDimension));//allocation and copy costlier than memory
	
	std::vector<pathing_point> intialPoints = transform_to_pathing_points(goals);
	for(pathing_point& point : intialPoints)
	{
		point.isGoalPoint = true;
	}
	std::copy(intialPoints.begin(), intialPoints.end(), activePoints.begin());
	
	for(unsigned remainingPoints = boardXDimension * boardYDimension; remainingPoints > 0; --remainingPoints)
	{
		for(pathing_point const& point : activePoints)
		{

				//set all un-set-adjacent-points and add them to active container
				//decrement remaining points
			
			//remove current point from active
		}
	}
	return reply;
}