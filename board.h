#pragma once

#include "tile.h"

#include <array>
#include <memory>

namespace tower_defense
{
	constexpr unsigned boardXDimension = 100;
	constexpr unsigned boardYDimension = 100;
	
	struct board_coordinate
	{
		unsigned x;
		unsigned y;

		board_coordinate(unsigned const x, unsigned const y);
	};

	struct board
	{
		std::array<std::array<tile, boardYDimension>, boardXDimension> tiles;
	};
	using board_ptr = std::unique_ptr<board>;
}