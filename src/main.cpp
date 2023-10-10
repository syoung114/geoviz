#include <iostream>
#include <string>
#include <cxxopts.hpp>

#include "../include/Geoviz.h"
#include "../include/Geomodel.h"
#include "../include/PrimitiveBuilder.h"
#include "../include/vox-spiral.h"

void run_test() {
    Geomodel model = PrimitiveBuilder::cube(0.0,0.0,0.0);
    Geomodel model2 = PrimitiveBuilder::cube(-2.0,-2.0,-2.0);    
    Geomodel model3 = PrimitiveBuilder::cube(2.0,.0,.0);

    Geomodel model_pool = Geomodel(3,6);
    model_pool.concat(model);
    model_pool.concat(model2);
    model_pool.concat(model3);
    
    Geoviz geo = Geoviz();
    geo.run(model_pool);	
}

void vox_spiral(int radius) {
    std::vector<Geomodel> bcircle = bresenham_circle(50);

    spiralize_bres(bcircle, radius);

    Geomodel universe = Geomodel(3, 6);
    for (Geomodel m : bcircle) {
        universe.concat(m);
    }

    Geoviz geo = Geoviz();
    geo.run(universe);
}

int main(int argc, char* argv[]) {

    cxxopts::Options options("Geoviz", "Handcrafted visualiser for custom geometry.");
    options.add_options()
        ("program", "Which program you want to run in the visualiser. Options test|solar|vox-spiral", cxxopts::value<std::string>())
        ("help", "Print this output.");
    options.parse_positional({"program"});
    auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout<<options.help()<<std::endl;
	return 0;
    }

    std::string prog_sel = args["program"].as<std::string>();
    if (prog_sel == "test") {
        run_test();
    }
    else if (prog_sel == "vox-spiral") {
        vox_spiral(20);
    }
    else {
        std::cout<<"invalid program"<<std::endl;
	return 0;
    }
    
   //std::cout<<args["program"].as<std::string>()<<std::endl;
    
    return 0;
}

