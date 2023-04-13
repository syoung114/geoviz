#ifndef COLOR_H
#define COLOR_H

struct Color {
    //Color has different representations but OpenGL uses RGB so we do too.
    //Why floats? We are just working with colours. The margin of error between floats and doubles is probably not visually noticable for the memory trade-off. It might be more important if I wanted the best visuals, but I don't.
    float red;
    float green;
    float blue;
    float alpha;
};

#endif
