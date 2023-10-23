# geoviz

Geoviz is a basic OpenGL renderer that is designed to compute a static scene of geometry defined from a script you write, allowing for some very niche visualisations. Applications like Blender likely allow you to do this too but I wanted to write another renderer from scratch, this time with object-oriented programming. The tutorials on OpenGL I've seen are usually in a procedural style so I wanted to do it myself.

## Voxel Spiral

Given a radius, this program renders a spiral of voxels that descends at even intervals. It was intended to solve a specific problem I had playing a game where I needed to create a 3D spiral but had no obvious resource to reference. Here is my solution.

**Usage**

```
./geoviz vox-spiral <radius>
```

**Example**

![vox-spiral example](doc/vox-spiral.GIF)


***

Cloning the repo and building from source requires you to also init the git submodules. You will also need to copy the GLAD2 gl4.x files from https://gen.glad.sh/ to the respective folder in `./lib`
