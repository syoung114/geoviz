//standard libraries
#include <vector>
#include <cmath>
#include <iostream>

//Relevant header files from this project
#include "../include/Geoviz.h"
#include "../include/Geomodel.h"
#include "../include/GeomodelPool.h"

int main(int argc, char* argv[]) {
    
    Geomodel model = Geomodel();
    model.vertices = {
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0,
        -0.5, -0.5, 0.5, 0.0, 1.0, 0.0,
        -0.5, 0.5, -0.5, 0.0, 0.0, 1.0,
        -0.5, 0.5, 0.5, 1.0, 0.0, 1.0,
        0.5, -0.5, -0.5, 1.0, 1.0, 1.0,
        0.5, -0.5, 0.5, 0.0, 1.0, 1.0,
        0.5, 0.5, -0.5, 1.0, 1.0, 1.0,
        0.5, 0.5, 0.5, 0.0, 0.0, 0.0
    };
	model.indices = {
		0, 2, 1, 
		1, 2, 3,
		4, 5, 6, 
		5, 7, 6,
		0, 1, 4, 
		1, 5, 4,
		2, 6, 3, 
		3, 6, 7,
		0, 4, 2, 
		2, 4, 6,
		1, 3, 5, 
		3, 7, 5,
	};

    Geomodel model2 = Geomodel();
    model2.vertices = {
        -2.5, -2.5, -2.5, 1.0, 0.0, 0.0,
        -2.5, -2.5, -1.5, 0.0, 1.0, 0.0,
        -2.5, -1.5, -2.5, 0.0, 0.0, 1.0,
        -2.5, -1.5, -1.5, 1.0, 0.0, 1.0,
        -1.5, -2.5, -2.5, 1.0, 1.0, 1.0,
        -1.5, -2.5, -1.5, 0.0, 1.0, 1.0,
        -1.5, -1.5, -2.5, 1.0, 1.0, 1.0,
        -1.5, -1.5, -1.5, 0.0, 0.0, 0.0
    };
	model2.indices = {
		0, 2, 1, 
		1, 2, 3,
		4, 5, 6, 
		5, 7, 6,
		0, 1, 4, 
		1, 5, 4,
		2, 6, 3, 
		3, 6, 7,
		0, 4, 2, 
		2, 4, 6,
		1, 3, 5, 
		3, 7, 5,
	};

    GeomodelPool model_pool = GeomodelPool();
    model_pool.concat(model);
    model_pool.concat(model2);
    
    Geoviz geo = Geoviz();
    geo.run(model_pool);
    
    return 0;
}
