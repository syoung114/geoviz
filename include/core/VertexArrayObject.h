#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <cstddef>
#include <functional>

#include <glad/glad.h>

#include "../util/ImmutableArray.h"

class VertexArrayObject {
    private:
        GLuint _id;
	ImmutableArray<int>* _attributes;
	int _vertex_length;

    public:
	VertexArrayObject(ImmutableArray<int>& attribute_lengths);
        ~VertexArrayObject();

	GLuint get_id();
	int get_vertex_length();
	size_t get_num_attrs();

	void bind();
	void partial_bind();
	//const ImmutableArray<int>& get_attributes();
};

#endif
