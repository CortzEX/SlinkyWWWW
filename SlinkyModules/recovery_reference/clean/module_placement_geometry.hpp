#pragma once
#include "Fast_Place.hpp"

extern "C" {
__declspec(dllexport) PlacementPosition *recovered_placement_position(PlacementPosition *, double x, double y, double z);
__declspec(dllexport) PlacementPosition *recovered_placement_add(PlacementPosition *, const PlacementPosition *, const PlacementPosition *);
__declspec(dllexport) PlacementBox *recovered_placement_box(PlacementBox *, const PlacementPosition *, const PlacementPosition *);
__declspec(dllexport) std::uint8_t recovered_placement_intersects(const PlacementBox *, const PlacementBox *);
}
