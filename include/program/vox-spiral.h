#ifndef VOX_SPIRAL_H
#define VOX_SPIRAL_H

#include <vector>
#include <unordered_set>
#include <string>

#include "../core/Geoviz.h"
#include "../core/Geomodel.h"

void pool_concat(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int depth);

void bres_step(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int z);

void spiralize_bres(std::vector<Geomodel>& pool);

void spiralize_bres(std::vector<Geomodel>& pool, int levels);

std::vector<Geomodel> bresenham_circle(int radius);

#endif
