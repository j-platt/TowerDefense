#pragma once

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
	};
}
using namespace directions;

namespace tower_defense
{
	struct pathing_vector
	{
		unsigned magnitude;
		direction facing;
	};
}