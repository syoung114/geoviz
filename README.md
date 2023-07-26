# geoviz

Personal scripts for making specific 3D visualisations that I can't find anywhere or prefer to write myself. You probably won't ever need them. Also includes a well-encapsulated object-oriented rendering backend I made which I prefer over the many OpenGL tutorials that use procedural programming.

![geoviz example](doc/cube.GIF)

## Voxel Cylinder Ramp

This exists to anwer a question that arised while I was playing a game:

> Given a voxelised cylinder, how should a spiral inside of it be evenly segmented across the height axis?

Well, here is my solution.

**Example**

INSERT GIF

**Usage**

INSERT ARGUMENTS

Cloning the repo and building from source requires you to also init the GLFW and GLM submodules. You will also need to copy the GLAD2 gl4.x files from https://gen.glad.sh/ to the respective folder in `./lib`

**TODO**

- Different starting and ending positions
