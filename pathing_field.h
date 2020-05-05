#pragma once

#include "pathing_vector.h"
#include "board.h"

namespace tower_defense
{
	constexpr unsigned field_x_dimension = board_x_dimension * tile_x_dimension;
	constexpr unsigned field_y_dimension = board_y_dimension * tile_y_dimension;
	
	struct pathing_field
	{
		std::array<std::array<pathing_vector, field_y_dimension>, field_x_dimension> vectorField;
	};

	pathing_field calculate_pathing(board const& source);
}