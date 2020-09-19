#pragma once
#include "Object.h"
#include <array>
#include <vector>

class Box : public Object
{
private:
	float height;
	float length;
	float width;
	float degrees;
	glm::vec3 rotationAxis;
	glm::vec4 color;
public:
	Box(glm::vec3 position, float height, float width, float length, float degrees, glm::vec3 rotationAxis, glm::vec4 color, unsigned int textID = 0);
	void setTexture(std::string path);
	std::vector<Vertex> genVertices(float xOffset = 0, float yOffset = 0, float zOffset = 0);
};