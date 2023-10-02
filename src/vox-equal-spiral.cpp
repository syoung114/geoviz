#include <cmath>

#include "../include/Geoviz.h"
#include "../include/Geomodel.h"
#include "../include/PrimitiveBuilder.h"

void pool_concat(Geomodel& pool, float x, float y, float depth) {
    pool.concat(
        PrimitiveBuilder::cube(x, y, depth)
    );
}

void bres_step(Geomodel& pool, float x, float y, float z) {
    //the depth of voxels in a so-called 'pool_concat group' is ordered by the pool_concat calling order in this function. in other words, if you passed depth to be z*nth_line, the topmost group is the first line. this is an inherent observation. 
    pool_concat(pool,  x,  y, z);//top right
    pool_concat(pool,  y,  x, z);//middle top right
    pool_concat(pool,  y, -x, z);//middle bottom right
    pool_concat(pool,  x, -y, z);//bottom right
    pool_concat(pool, -x, -y, z);//bottom left
    pool_concat(pool, -y, -x, z);//middle bottom left
    pool_concat(pool, -y,  x, z);//middle top left
    pool_concat(pool, -x,  y, z);//top left
}

Geomodel bresenham_circle(float radius) {
    //dont ask me how this works. I just adapted from it from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    float x = 0;
    float y = radius;
    float d = 3 - 2*radius;
    float z = 0.0;
    Geomodel pool = Geomodel(3, 6);

    bres_step(pool, x, y, x);

    while (y >= x++) {
        if (d > 0) {
            y--;
            d += 4*(x - y) + 10;
        }
        else {
            d += 4*x + 6;
        }
        z += 1.0;
        bres_step(pool, x, y, z);
    }
    return pool;
}

void spiralize_bres(Geomodel& circle_set) {
    //for (int i = 0; i < circle_set.length(); i++) {
    //     
    //}
}

int main(int argc, char* argv[]) {
    Geomodel model = PrimitiveBuilder::cube(0.0,0.0,0.0,0.0,1.0,0.0);
    Geomodel model2 = PrimitiveBuilder::cube(-2.0,-2.0,-2.0);
    Geomodel model3 = PrimitiveBuilder::cube(2.0,2.0,2.0,.0,.0,.5);
    model.concat(model2);
    model.concat(model3); 
    
    Geoviz geo = Geoviz();
    geo.run(model);

    return 0;
}

