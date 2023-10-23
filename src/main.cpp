#include <iostream>
#include <string>
#include <CLI/CLI.hpp>

#include "../include/core/Geoviz.h"
#include "../include/core/Geomodel.h"
#include "../include/primitives/PrimitiveBuilder.h"
#include "../include/vox-spiral.h"

Geomodel run_test() {
    Geomodel model = PrimitiveBuilder::cube(0.0,0.0,0.0);
    Geomodel model2 = PrimitiveBuilder::cube(-2.0,-2.0,-2.0);    
    Geomodel model3 = PrimitiveBuilder::cube(2.0,.0,.0);

    Geomodel model_pool = Geomodel(3,6);
    model_pool.concat(model);
    model_pool.concat(model2);
    model_pool.concat(model3);
    
    return model_pool;
}

Geomodel vox_spiral(int radius) {
    std::vector<Geomodel> bcircle = bresenham_circle(radius);

    spiralize_bres(bcircle, radius);

    Geomodel model = Geomodel(3, 6);
    for (Geomodel m : bcircle) {
        model.concat(m);
    }

    return model;
}

int main(int argc, char* argv[]) {
    //Define command line args
    CLI::App app("Geoviz: Handcrafted visualiser for custom geometry.");
    app.require_subcommand(1);

    CLI::App *spiral_program = app.add_subcommand("vox-spiral", "Given a radius, draw a voxelized spiral that descends evenly until a full revolution.");
    
    int vox_rad{10};
    //std::string vox_rad_str;
    spiral_program->add_option("radius", vox_rad, "How big do you want the spiral?")
        ->capture_default_str()
        ->check(CLI::Number)
        ->required()
        ;
    spiral_program->callback([&](){
        Geomodel model = vox_spiral(vox_rad);
        Geoviz geo = Geoviz();
        geo.run(model);
    }); 
    
    CLI11_PARSE(app, argc, argv);

    return 0;
}
