#include "../include/vox-spiral.h"

#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>
#include <random>

#include "../include/core/Geoviz.h"
#include "../include/core/Geomodel.h"
#include "../include/primitives/PrimitiveBuilder.h"

//Ugly but more efficient than an vector because no overhead needed and num of elements certain. Pointer array might be as efficient but that is higher risk for no reason. It's subjective.
struct BresSectionColors {
    float r1;
    float g1;
    float b1;
    float r2;
    float g2;
    float b2;
    float r3;
    float g3;
    float b3;
    float r4;
    float g4;
    float b4;
    float r5;
    float g5;
    float b5;
    float r6;
    float g6;
    float b6;
    float r7;
    float g7;
    float b7;
    float r8;
    float g8;
    float b8;
};

void pool_concat(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int depth, float r, float g, float b) {
    std::string coords_str = std::to_string(x) + "," + std::to_string(y);
    if (coordinates.find(coords_str) == coordinates.end()) {
        pool.push_back(
            PrimitiveBuilder::cube(x, y, depth, r, g, b)
        );
        coordinates.insert(coords_str);
    }
}

void bres_step(std::vector<Geomodel>& pool, std::unordered_set<std::string>& coordinates, int x, int y, int z, BresSectionColors c) {
    pool_concat(pool, coordinates,  x,  y, z, c.r1, c.g1, c.b1);//top right
    pool_concat(pool, coordinates,  y,  x, z, c.r2, c.g2, c.b2);//middle top right, reversed
    pool_concat(pool, coordinates,  y, -x, z, c.r3, c.g3, c.b3);//middle bottom right
    pool_concat(pool, coordinates,  x, -y, z, c.r4, c.g4, c.b4);//bottom right, reversed
    pool_concat(pool, coordinates, -x, -y, z, c.r5, c.g5, c.b5);//bottom left
    pool_concat(pool, coordinates, -y, -x, z, c.r6, c.g6, c.b6);//middle bottom left, reversed
    pool_concat(pool, coordinates, -y,  x, z, c.r7, c.g7, c.b7);//middle top left
    pool_concat(pool, coordinates, -x,  y, z, c.r8, c.g8, c.b8);//top left. reversed
}

void spiralize_bres(std::vector<Geomodel>& pool) {
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

BresSectionColors get_colors() {
    BresSectionColors c;

    //Init RNG
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0,1.0);

    c.r1 = dist(gen); 
    c.g1 = dist(gen);
    c.b1 = dist(gen);
    c.r2 = dist(gen);
    c.g2 = dist(gen);
    c.b2 = dist(gen);
    c.r3 = dist(gen);
    c.g3 = dist(gen);
    c.b3 = dist(gen);
    c.r4 = dist(gen);
    c.g4 = dist(gen);
    c.b4 = dist(gen);
    c.r5 = dist(gen);
    c.g5 = dist(gen);
    c.b5 = dist(gen);
    c.r6 = dist(gen);
    c.g6 = dist(gen);
    c.b6 = dist(gen);
    c.r7 = dist(gen);
    c.g7 = dist(gen);
    c.b7 = dist(gen);
    c.r8 = dist(gen);
    c.g8 = dist(gen);
    c.b8 = dist(gen);

    return c;
}
std::vector<Geomodel> bresenham_circle(int radius) {
    //dont ask me how this works. I just adapted from it from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    int x = 0;
    int y = radius;
    int d = 3 - 2*radius;
    int z = 0.0;

    //Create a vector to group Geomodels and reference them late
    std::vector<Geomodel> pool;
    BresSectionColors colors = get_colors();

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
        bres_step(pool, coordinate_p, x, y, z, colors);
    }

    return pool;
}
