#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <vector>
#include <glad/glad.h>

class VertexArrayObject {
    private:
        GLuint _id;
	const std::vector<int>* _attr_layout;
    public:
	VertexArrayObject(const std::vector<int>& attribute_layout);
        ~VertexArrayObject();

	GLuint get_id() const {
            //Wait, aren't you exposing the very thing that this class wraps?
	    //Yes. but it's to allow one-to-many relationships with this class and VBOs. A vector of VBOs here would be redundant when you can just do this.
	    //On breaking encapsulation - I think you'd have no reason to use the id besides working with VBOs. You arent stupid to run glDeleteArrays or something.
            return _id;
	};

	void init();
	void bind();
};

#endif
