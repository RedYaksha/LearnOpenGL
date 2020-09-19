#include "Scene.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

Scene::Scene(Timeline& initTimeline)
	: timeline(initTimeline)
{
	totalVertices = 0;
}

void Scene::Setup(VertexArray& va)
{
	std::vector<Vertex> vertices;

	for (Object* obj : elements)
	{
		std::vector<Vertex> elementVertices = obj->genVertices();
		vertices.insert(vertices.end(), elementVertices.begin(), elementVertices.end());
	}
	
	std::cout << "total vertices: " << totalVertices << std::endl;
	/* for (auto it = vertices.begin(); it != vertices.end(); it++)
	{
		std::cout << glm::to_string(it->pos) << glm::to_string(it->color) << glm::to_string(it->texCord) << " - " << it->textureID << std::endl;
	} */
	
	VertexBuffer* vbo = new VertexBuffer(&vertices[0], sizeof(Vertex)*totalVertices, GL_STATIC_DRAW);

	va.Bind();
	vbo->Bind();
	/* This sets the new layout, needs to be abstractified */
	GLCall(glEnableVertexAttribArray(0)); //enables the attribute
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos)));

	GLCall(glEnableVertexAttribArray(1)); //enables the attribute
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, norm)));

	GLCall(glEnableVertexAttribArray(2)); //enables the attribute
	GLCall(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color)));

	GLCall(glEnableVertexAttribArray(3)); //enables the attribute
	GLCall(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCord)));

	GLCall(glEnableVertexAttribArray(4)); //enables the attribute
	GLCall(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, textureID)));
}

std::vector<Vertex> Scene::getAllVertices()
{
	std::vector<Vertex> vertices;

	for (Object* obj : elements)
	{
		std::vector<Vertex> elementVertices = obj->genVertices();
		vertices.insert(vertices.end(), elementVertices.begin(), elementVertices.end());
	}
	

	std::cout << "total vertices: " << totalVertices << std::endl;
	for (auto it = vertices.begin(); it != vertices.end(); it++)
	{
		std::cout << glm::to_string(it->pos) << glm::to_string(it->norm) << glm::to_string(it->color) << glm::to_string(it->texCord) << std::endl;
	}
	return vertices;
}

void Scene::Push(Object* obj)
{
	elements.push_back(obj);
	totalVertices += obj->numVertices;
}

void Scene::Render(Shader& shader, float deltaTime)
{

	int indexOffset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		/*
			timeline.preformAnimation(elements[i], shader)
				- change uniform model matrix in the shader (need reference to shader class)
				- 
		*/
		timeline.PerformAnimation(elements[i], shader, deltaTime);
		GLCall(glDrawArrays(elements[i]->primitive, indexOffset, elements[i]->numVertices));
		indexOffset += elements[i]->numVertices;
	}
	
}