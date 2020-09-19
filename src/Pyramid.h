#pragma once
#include "Object.h"
#include <array>
#include <vector>

class Pyramid : public Object
{
private:
	float height;
	float angle;
	float degrees;
	glm::vec3 rotationAxis;
	glm::vec4 color;
public:
	Pyramid(glm::vec3 position, float height, float angle, float degrees, glm::vec3 rotationAxis, glm::vec4 color, unsigned int textID = 0);
	void setTexture(std::string path);
	std::vector<Vertex> genVertices(float xOffset = 0, float yOffset = 0, float zOffset = 0);
};