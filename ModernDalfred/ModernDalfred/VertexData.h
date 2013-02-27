#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <glm/glm.hpp>

/*
 * Holds the data for one vertex
 */
class VertexData {
public:

	VertexData(glm::vec3 &p, glm::vec3 &c, glm::vec3 &n);
	
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;

};


#endif