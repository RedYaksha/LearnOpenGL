#include "Timeline.h"
#include <iostream>
#include <map>
#include "glm/gtx/string_cast.hpp"

void _parseAnimationInfo(std::string animationInfo, std::string& aniType, float& end)
{
	int ind = animationInfo.find(":");
	aniType = animationInfo.substr(0, ind);
	end = std::stof(animationInfo.substr(ind+1));
}

Animation _createAnimation(std::string animationInfo, float time)
{
	/* Parsing info -- animationInfo will come like: "rotate:45" or "translateY:20" */
	
	std::string aniType;
	float end;
	_parseAnimationInfo(animationInfo, aniType, end);

	float start = 0;
	float incPerSec = end/time; //increment per second

	/* Animation = { type, startTime, endTime, increment } */
	return { aniType , start, end, incPerSec };
}

Timeline::Timeline()
	:tmp(0.f)
{
	mymap = new std::map<unsigned int, Animation>;
}

void Timeline::Push(Object *obj, std::string animationInfo, float time)
{
	if (mymap->find(obj->id) != mymap->end())
	{
		std::cout << "this object is already in the map! " << std::endl;
		return;
	}

	Animation ani = _createAnimation(animationInfo, time);
	mymap->insert(std::pair<unsigned int, Animation>(obj->id, ani));
}

void Timeline::PerformAnimation(Object *obj, Shader& shader, float deltaTime)
{
	/* check if obj is in mymap */
	if (mymap->find(obj->id) == mymap->end()) {
		shader.SetUniformMat4f("model", glm::mat4(1.0f));
		return;
	}

	/* TODO: - multiple animations */

	/* TODO: - delayed animations */

	/* if it is, then perform animation (change model matrix) */
	Animation* ani = &mymap->at(obj->id);

	if (ani->start < ani->end)
	{
		float increment = ani->increment * deltaTime;
		ani->start += increment;
	}

	glm::mat4 model(1.f);
	
	if(ani->type == "rotateX")
		model = glm::rotate(model, glm::radians(ani->start), glm::vec3(1.f, 0.f, 0.f));
	else if (ani->type == "rotateY")
		model = glm::rotate(model, glm::radians(ani->start), glm::vec3(0.f, 1.f, 0.f));
	else if (ani->type == "rotateZ")
		model = glm::rotate(model, glm::radians(ani->start), glm::vec3(0.f, 0.f, 1.f));
	else if (ani->type == "translate")
		model = glm::rotate(model, glm::radians(ani->start), glm::vec3(0.f, 0.f, 1.f));

	shader.SetUniformMat4f("model", model);
}