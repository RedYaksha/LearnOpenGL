#pragma once

#include "glm/glm.hpp"

/*
	this is specifically a "look-at camera"
*/
class Camera
{
private:
	glm::vec3 camPos;
	glm::vec3 direction;
	glm::vec3 up;
	float yaw;
	float pitch;
public:
	Camera(glm::vec3 initCamPos, glm::vec3 initUp, float initYaw = -90.f, float initPitch = 0);
	void handleInput(unsigned int inputID, float deltaTime);
	glm::mat4 getViewMatrix();
	void update();
};