#pragma once

#include "pathing_vector.h"
#include "board.h"

#include <vector>
#include <memory>

namespace tower_defense
{
	constexpr unsigned fieldXDimension = boardXDimension * tileXDimension;
	constexpr unsigned fieldYDimension = boardYDimension * tileYDimension;

	struct pathing_point
	{
		unsigned x;
		unsigned y;

		bool beenSet = false;

		pathing_vector pathing = { 0, directions::unset };

		bool is_goal_point() { return pathing.facing == directions::goal; }

		//This class will be central in determining which enemies are hit and which are at the end
		//as well as any other status effects. It will be where the state of the game is processed
	};

	pathing_point center_of_tile(board_coordinate const& tileInQuestion);
	
	struct pathing_field
	{
		std::array<std::array<pathing_point, fieldYDimension>, fieldXDimension> vectorField;

		pathing_field();
	};
	using pathing_field_ptr = std::unique_ptr<pathing_field>;

	pathing_field_ptr calculate_pathing(board const& source, std::vector<board_coordinate> const& goals);
}