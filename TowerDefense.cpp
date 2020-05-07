#include "pathing_field.h"

using namespace tower_defense;

void print_field(pathing_field_ptr const& field)
{
	std::for_each(std::begin(field->vectorField), std::end(field->vectorField),
		[](std::array<pathing_point, fieldYDimension> const& row) {
		std::for_each(std::begin(row), std::end(row),
			[](pathing_point const& point) {std::cout << point.pathing.facing; }
		);
		std::cout << '\n';
	});
}

//TODO: the pathing generation seems to be good but it needs to honor impassable terrain and not extend the active point queue beyond the impassable 
//terrain so that the mazes are always valid.

int __cdecl main()
{
	board_ptr testBoard = std::make_unique<board>();
	pathing_field_ptr test1 = calculate_pathing(*testBoard, { { 50,50 }, { 0,0 } });

	print_field(test1);
}