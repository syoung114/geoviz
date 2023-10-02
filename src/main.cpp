//Relevant header files from this project
#include "../include/Geoviz.h"
#include "../include/Geomodel.h"
#include "../include/PrimitiveBuilder.h"

int main(int argc, char* argv[]) {

    Geomodel model = PrimitiveBuilder::cube(0.0,0.0,0.0);
    Geomodel model2 = PrimitiveBuilder::cube(-2.0,-2.0,-2.0);    
    Geomodel model3 = PrimitiveBuilder::cube(2.0,.0,.0);

    Geomodel model_pool = Geomodel(6,3);
    model_pool.concat(model);
    model_pool.concat(model2);
    model_pool.concat(model3);
    
    Geoviz geo = Geoviz();
    geo.run(model_pool);
    
    return 0;
}
