#pragma once
#include <vector>
#include "Object.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Timeline.h"

class Scene
{
private:
	std::vector<Object*> elements;
	unsigned int totalVertices;
	Timeline timeline;
public:
	Scene(Timeline& timeline);
	void Setup(VertexArray& va);
	void Render(Shader& shader, float deltaTime);
	void Push(Object* obj);
	std::vector<Vertex> getAllVertices();
};