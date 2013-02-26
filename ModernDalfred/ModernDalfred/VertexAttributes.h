#ifndef VERTEX_ATTRIBUTES_H
#define VERTEX_ATTRIBUTES_H

#include <glm/glm.hpp>

class VertexAttributes {
public:

	VertexAttributes(glm::vec3 p, glm::vec3 c, glm::vec3 n);
	
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 norm;

};


#endif