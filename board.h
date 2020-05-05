#pragma once

#include "tile.h"

#include <array>

namespace tower_defense
{
	constexpr unsigned board_x_dimension = 100;
	constexpr unsigned board_y_dimension = 100;

	struct board
	{
		std::array<std::array<tile, board_y_dimension>, board_x_dimension> tiles;
	};
}

