#include "Line.h"
#include "glm/glm.hpp"
#include "VertexBuffer.h"

Line::Line(glm::vec3 position, glm::vec3 direction, float scalarNum, unsigned int textID)
    : Object(position, textID), scalar(scalarNum)
{
    primitive = GL_LINES;
    dir = glm::normalize(direction)*scalar;
    numVertices = 2;
}

std::vector<Vertex> Line::genVertices(float xOffset, float yOffset, float zOffset)
{
    float x = pos.x + xOffset;
    float y = pos.y + yOffset;
    float z = pos.z + zOffset;

    float positions[2][3] = { 0.f, 0.f, 0.f,
                              dir.x, dir.y, dir.z };

    std::vector<Vertex> vertices(numVertices);

    unsigned int vertexInd = 0;
    for (int i = 0; i < 2; i++) {
        Vertex v;
        v.pos = glm::vec3(x + positions[vertexInd][0], y + positions[vertexInd][1], z + positions[vertexInd][2]);
        v.color = glm::vec4(0.f, 0.f, 0.f, 1.f);
        v.texCord = glm::vec2(0.f, 0.f);
        v.textureID = (float)textID;
        vertices[vertexInd] = v;
        vertexInd++;
    }
    return vertices;
}
