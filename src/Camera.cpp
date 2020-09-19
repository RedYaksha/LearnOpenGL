#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 initCamPos, glm::vec3 initUp, float initYaw, float initPitch)
	:camPos(initCamPos), up(initUp), yaw(initYaw), pitch(initPitch)
{
    direction = glm::vec3(0.f);
}

void Camera::handleInput(unsigned int inputID, float deltaTime)
{
    float cameraSpeed = 4 * deltaTime;

    if (inputID == GLFW_KEY_W)
        camPos += cameraSpeed * direction;
    if (inputID == GLFW_KEY_S)
        camPos -= cameraSpeed * direction;
    if (inputID == GLFW_KEY_A)
        camPos -= glm::normalize(glm::cross(direction, up)) * cameraSpeed;
    if (inputID == GLFW_KEY_D)
        camPos += glm::normalize(glm::cross(direction, up)) * cameraSpeed;
    if (inputID == GLFW_KEY_LEFT)
        yaw--;
    if (inputID == GLFW_KEY_RIGHT)
        yaw++;
    if (inputID == GLFW_KEY_UP)
        pitch++;
    if (inputID == GLFW_KEY_DOWN)
        pitch--;
}

void Camera::update()
{
    direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    direction.y = glm::sin(glm::radians(pitch));
    direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 eye = camPos;
    glm::vec3 center = camPos + direction;

    glm::vec3 zaxis = glm::normalize(center - eye);
    up = glm::normalize(up);
    glm::vec3 xaxis = glm::normalize(glm::cross(zaxis, up));
    glm::vec3 yaxis = glm::normalize(glm::cross(xaxis, zaxis));

    /*

    We want
    [ xaxis.x xaxis.y  xaxis.z -dot(xaxis, eye)
      yaxis.x yaxis.y  yaxis.z -dot(yaxis, eye)
     -zaxis.x zaxis.y -zaxis.z -dot(zaxis, eye)
        0        0        0           1          ]
     as column order in memory.

     Why is the z-axis negated?
        - The z-axis already pointing towards -z. (it's the direction the camera is pointing) by convention.
        - We only see vertices and shapes that are in negative z land.
        - If our z-axis wasn't negated...
            - Passing a vertex already in negative z land and having it pass through our lookAt matrix
              will put that vertex behind the camera to positive z land. (we don't want that)
            - Conversely, if our camera direction is towards positive z, and we see positive z veritices, passing it through
              our lookAt matrix will only scale it towards positive z, again being left unseen because we didn't negate z-axis.
    */

    glm::mat4 lookAt{
        xaxis.x, yaxis.x, -zaxis.x, 0,
        xaxis.y, yaxis.y, -zaxis.y, 0,
        xaxis.z, yaxis.z, -zaxis.z, 0,
        -glm::dot(xaxis,eye) , -glm::dot(yaxis,eye), glm::dot(zaxis,eye), 1
    };
    return lookAt;
}