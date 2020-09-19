#pragma once
#include "glm/glm.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec4 color;
	glm::vec2 texCord;
	float textureID;
};

class Object
{
private:
public:
	glm::vec3 pos;

	static unsigned int current_id;

	unsigned int id;
	unsigned int textID;
	unsigned int numVertices;
	unsigned int primitive;

	Object(glm::vec3 position, unsigned int textureID)
		: pos(position), textID(textureID), id(current_id++)
	{}

	virtual std::vector<Vertex> genVertices(float xOffset = 0, float yOffset = 0, float zOffset = 0) = 0;

};