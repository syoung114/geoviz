#include <iostream>
#include <string>
#include <cxxopts.hpp>

#include "../include/core/Geoviz.h"
#include "../include/core/Geomodel.h"
#include "../include/primitives/PrimitiveBuilder.h"
#include "../include/program/vox-spiral.h"

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
    std::vector<Geomodel> bcircle = bresenham_circle(50);

    spiralize_bres(bcircle, radius);

    Geomodel model = Geomodel(3, 6);
    for (Geomodel m : bcircle) {
        model.concat(m);
    }

    return model;
}

int main(int argc, char* argv[]) {
    //Define command line args
    cxxopts::Options options("Geoviz", "Handcrafted visualiser for custom geometry.");
    options.parse_positional({"program"});
    options.add_options()
        ("program", "Which program you want to run in the visualiser. Options test|solar|vox-spiral", cxxopts::value<std::string>())
        ("help", "Print this output.");
    auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout<<options.help()<<std::endl;
	return 0;
    }

    //Find the program they selected and compute the respective model
    std::string prog_sel = args["program"].as<std::string>();
    Geomodel model = Geomodel(0,0);
    if (prog_sel == "test") {
        model = run_test();
    }
    else if (prog_sel == "vox-spiral") {
        model = vox_spiral(20);
    }
    else {
        std::cout<<"invalid program"<<std::endl;
	return 0;
    }
   
    Geoviz geo = Geoviz();
    geo.run(model);
    
    return 0;
}

