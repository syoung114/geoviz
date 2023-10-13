#include "../include/program/vox-spiral.h"

#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>

#include "../include/core/Geoviz.h"
#include "../include/core/Geomodel.h"
#include "../include/primitives/PrimitiveBuilder.h"

void pool_concat(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int depth) {
    std::string coords_str = std::to_string(x) + "," + std::to_string(y);
    if (coordinates.find(coords_str) == coordinates.end()) {
        pool.push_back(
            PrimitiveBuilder::cube(x, y, depth)
        );
        coordinates.insert(coords_str);
    }
}

void bres_step(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int z) {
    //the depth of voxels in a so-called 'pool_concat group' is ordered by the pool_concat calling order in this function. in other words, if you passed depth to be z*nth_line, the topmost group is the first line. this is an inherent observation. 
    pool_concat(pool, coordinates,  x,  y, z);//top right
    pool_concat(pool, coordinates,  y,  x, z);//middle top right, reversed
    pool_concat(pool, coordinates,  y, -x, z);//middle bottom right
    pool_concat(pool, coordinates,  x, -y, z);//bottom right, reversed
    pool_concat(pool, coordinates, -x, -y, z);//bottom left
    pool_concat(pool, coordinates, -y, -x, z);//middle bottom left, reversed
    pool_concat(pool, coordinates, -y,  x, z);//middle top left
    pool_concat(pool, coordinates, -x,  y, z);//top left. reversed
}

void spiralize_bres(std::vector<Geomodel>& pool) {
  //int descend_every = 360/levels;
  //int vox_per_degree = pool.size() / 360;
    std::vector<int> stride_indices;
    for (int i = 0; i < pool.size(); i += 8) {
        stride_indices.push_back(i);
    }
    bool reverse = false;
    for (int i = 0, j = 0, k = 0; i < pool.size(); i++, j++) {
      if (j >= stride_indices.size()) {
            j = 0;
            k++;
            reverse = !reverse;
        }
        
        if (reverse) {
            pool.at(
                stride_indices.at(stride_indices.size() - j - 1) + k
            ).translate(0,0,i);
        }
        else {
            pool.at(
                stride_indices.at(j) + k
            ).translate(0,0,i);
        }
    }
}

void spiralize_bres(std::vector<Geomodel>& pool, int levels) {
    std::vector<int> stride_indices;
    for (int i = 0; i < pool.size(); i += 8) {
        stride_indices.push_back(i);
    }
    
    bool reverse = false;
    int descend_every = pool.size() / levels;
    float current_depth = 0;
    for (int i = 0, j = 0, k = 0; i < pool.size(); i++, j++) {
      if (i % descend_every == 0) current_depth++;
      if (j >= stride_indices.size()) {
            j = 0;
            k++;
            reverse = !reverse;
        }
        
        if (reverse) {
            pool.at(
                stride_indices.at(stride_indices.size() - j - 1) + k
            ).translate(.0,0.0,current_depth);
        }
        else {
            pool.at(
                stride_indices.at(j) + k
            ).translate(.0,0.0,current_depth);
        }
    }
}

std::vector<Geomodel> bresenham_circle(int radius) {
    //dont ask me how this works. I just adapted from it from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    int x = 0;
    int y = radius;
    int d = 3 - 2*radius;
    int z = 0.0;

    //Create a vector to group Geomodels and reference them late
    std::vector<Geomodel> pool;

    //We need a map to keep track of whether a cube already exists at a specific coordinate. This can be done already using an algorithm on the vector but I prefer the simple option.
    //It turns out I can't do a map of pairs so I am doing a hacky way: string representation of coordinate pairs.
    std::unordered_set<std::string> coordinate_p;

    while (y >= x++) {
        if (d > 0) {
            y--;
            d += 4*(x - y) + 10;
        }
        else {
            d += 4*x + 6;
        }
        bres_step(pool, coordinate_p, x, y, z);
    }

    return pool;
}
