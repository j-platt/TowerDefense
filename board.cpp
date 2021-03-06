#include "board.h"

#include <assert.h>

namespace tower_defense
{
	board_coordinate::board_coordinate(unsigned const x, unsigned const y) : x(x), y(y)
	{
		assert(x < boardXDimension);
		assert(y < boardYDimension);
	}
}
