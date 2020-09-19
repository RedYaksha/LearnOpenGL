#pragma once
#include "Object.h"
#include <array>
#include <vector>

class Line : public Object
{
private:
	glm::vec3 dir;
	float scalar;
public:
	Line(glm::vec3 position, glm::vec3 direction, float scalar, unsigned int textID = 0);
	std::vector<Vertex> genVertices(float xOffset = 0, float yOffset = 0, float zOffset = 0);
};