#include "primitives/PrimitiveBuilder.h"
#include "core/Geomodel.h"

Geomodel PrimitiveBuilder::cube(float x, float y, float z) {
  return PrimitiveBuilder::cube(x, y, z, 0.5, 0.0, 0.0);
}

Geomodel PrimitiveBuilder::cube(float x, float y, float z, float r, float g, float b) {
  return PrimitiveBuilder::cube(x, y, z, r, g, b, 1.0, 1.0, 1.0);
}

Geomodel PrimitiveBuilder::cube(float x, float y, float z, float r, float g, float b, float w, float h, float l) {
    //the actual vertex locations are centred about an origin that is usually at (w,h,l)/2. we work about this origin give or take.
    float half_w = w/2;
    float half_h = h/2;
    float half_l = l/2;
  
    Geomodel model = Geomodel(3, 6, {
        -half_w+x, -half_h+y, -half_l+z,  r, g, b, 
        -half_w+x, -half_h+y,  half_l+z,  r, g, b,
        -half_w+x,  half_h+y, -half_l+z,  r, g, b,
        -half_w+x,  half_h+y,  half_l+z,  r, g, b,
         half_w+x, -half_h+y, -half_l+z,  r, g, b,
         half_w+x, -half_h+y,  half_l+z,  r, g, b,
         half_w+x,  half_h+y, -half_l+z,  r, g, b,
         half_w+x,  half_h+y,  half_l+z,  r, g, b
      },{
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
    });
    
    return model;
}
