#pragma once
#include "Object.h"
#include "Shader.h"

#include <string>
#include <iostream>
#include <map>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Animation
{
	std::string type;
	float start;
	float end;
	float increment;

	void print()
	{
		std::cout << "type: " << type << " start: " << start << " end: " << end << " increment: " << increment << std::endl;
	}
};

class Timeline
{
private:
	std::map<unsigned int, Animation>* mymap;
	float tmp;
public:
	Timeline();
	void Push(Object *obj, std::string animationInfo, float time);
	void PerformAnimation(Object *obj, Shader& shader, float deltaTime);
};