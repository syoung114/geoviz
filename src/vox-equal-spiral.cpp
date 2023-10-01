#include "../include/Geoviz.h"
#include "../include/Geomodel.h"
#include "../include/GeomodelPool.h"
#include "../include/PrimitiveBuilder.h"

void pool_concat(GeomodelPool& pool, float x, float y, float z) {
    pool.concat(
        PrimitiveBuilder::cube(x, y, z)
    );
}

void bres_step(GeomodelPool& pool, float x, float y, float z) {
    pool_concat(pool,  x,  y, z);
    pool_concat(pool, -x,  y, z);
    pool_concat(pool,  x, -y, z);
    pool_concat(pool, -x, -y, z);
    pool_concat(pool,  x,  x, z);
    pool_concat(pool, -x,  x, z);
    pool_concat(pool,  x, -x, z);
    pool_concat(pool, -x, -x, z);
}

GeomodelPool bresenham(float radius) {
    //dont ask me how this works. I just adapted from it from https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
    float x = 0;
    float y = radius;
    float d = 3 - 2*radius;
    
    GeomodelPool pool = GeomodelPool();

    bres_step(pool, x, y, 0.0);

    while (y >= x++) {
        if (d > 0) {
            y--;
            d += 4*(x - y) + 10;
        }
        else {
            d += 4*x + 6;
        }
        bres_step(pool, x, y, 0.0);
    }
    return pool;
}

int main(int argc, char* argv[]) {

    Geomodel model = PrimitiveBuilder::cube(0.0,0.0,0.0);
    Geomodel model2 = PrimitiveBuilder::cube(-2.0,-2.0,-2.0);
    Geomodel model3 = PrimitiveBuilder::cube(2.0,.0,.0);

    //    GeomodelPool model_pool = GeomodelPool();
    //    model_pool.concat(model);
    //    model_pool.concat(model2);
    //    model_pool.concat(model3);

    GeomodelPool vox_circle = bresenham(20.0);
    
    Geoviz geo = Geoviz();
    geo.run(vox_circle);

    return 0;
}

