#pragma once

#include "pathing_vector.h"
#include "board.h"

#include <vector>

namespace tower_defense
{
	constexpr unsigned fieldXDimension = boardXDimension * tileXDimension;
	constexpr unsigned fieldYDimension = boardYDimension * tileYDimension;

	struct pathing_point
	{
		unsigned x;
		unsigned y;

		bool isGoalPoint;

		//This class will be central in determining which enemies are hit and which are at the end
		//as well as any other status effects. It will be where the state of the game is processed

		pathing_point(unsigned const x, unsigned const y);
	};

	pathing_point center_of_tile(board_coordinate const& tileInQuestion);
	
	struct pathing_field
	{
		std::array<std::array<pathing_vector, fieldYDimension>, fieldXDimension> vectorField;
	};

	pathing_field calculate_pathing(board const& source, std::vector<board_coordinate> const& goals);
}