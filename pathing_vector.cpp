#include "pathing_vector.h"

std::ostream& operator<<(std::ostream& output, direction const& input)
{
	switch(input)
	{
	case directions::north:
		output << '^';
		break;
	case directions::northeast:
		output << '/';
		break;
	case directions::east:
		output << '>';
		break;
	case directions::southeast:
		output << '\\';
		break;
	case directions::south:
		output << 'v';
		break;
	case directions::southwest:
		output << '/';
		break;
	case directions::west:
		output << '<';
		break;
	case directions::northwest:
		output << '\\';
		break;
	case directions::goal:
		output << 'O';
		break;
	default:
		output << 'X';
	}
	return output;
}