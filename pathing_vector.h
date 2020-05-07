#pragma once

#include <iostream>

namespace directions
{
	enum direction
	{
		north,
		northeast,
		east,
		southeast,
		south,
		southwest,
		west,
		northwest,
		goal,
		unset,
	};
}
using directions::direction;

std::ostream& operator<<(std::ostream& output, direction const& input);

namespace tower_defense
{
	struct pathing_vector
	{
		unsigned magnitude = 0;
		direction facing = directions::unset;
	};
}