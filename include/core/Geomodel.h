#ifndef GEOMODEL_H
#define GEOMODEL_H

#include <vector>
#include <numeric>
#include <glad/glad.h>

class Geomodel {
    private:
	// Might seem strange to make only this vector private but it has significant intention: You don't want to allow modification of what defines the layout of a vertex after instantiation. If such an instance is bound to a VBO (it probably is), big trouble if we change the layout and make vertex modifications accordingly. Therefore, keep apples with apples and oranges with oranges.
	// TODO need class for safe editing of vectors while respecting _attr_layout
	std::vector<int> _attr_layout;

	//this is the sum of _attr_layout
	int _vertex_length;
	int _accumulate_attr_layout() const {
            return std::accumulate(_attr_layout.begin(), _attr_layout.end(), 0);
	}
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        Geomodel(const std::vector<int> attribute_layout) : _attr_layout(attribute_layout) {
            _vertex_length = _accumulate_attr_layout();
        }

        Geomodel(const std::vector<int> attribute_layout, const std::vector<GLfloat> vertices, const std::vector<GLuint> indices)
	    : _attr_layout(attribute_layout), vertices(vertices), indices(indices)
	{
            _vertex_length = _accumulate_attr_layout();
	}
        
        bool concat(const Geomodel& other);

        void translate(GLfloat x, GLfloat y, GLfloat z);

	const std::vector<int>& get_attribute_layout() const {
            return _attr_layout;
        }

	int get_vertex_length() const {
            return _vertex_length;
        }
};

#endif
