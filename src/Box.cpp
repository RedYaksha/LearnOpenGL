#include "Box.h"
#include "glm/glm.hpp"
#include "VertexBuffer.h"
#include "glm/gtc/matrix_transform.hpp"

Box::Box(glm::vec3 position, float initHeight, float initWidth, float initLength, float initDegrees, glm::vec3 initRotationAxis, glm::vec4 initColor, unsigned int textID)
    : Object(position, textID), height(initHeight), width(initWidth), length(initLength), degrees(initDegrees), rotationAxis(initRotationAxis), color(initColor)
{
    primitive = GL_TRIANGLES;
    numVertices = 36;
}


std::vector<Vertex> Box::genVertices(float xOffset, float yOffset, float zOffset)
{
    float x = pos.x + xOffset;
    float y = pos.y + yOffset;
    float z = pos.z + zOffset;

    float texSet[3][12] = { { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
                            { 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
                            { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}   };

    float normSet[6][3] = { {0.f, 0.f, -1.f}, {0.f, 0.f, 1.f}, {-1.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, -1.f, 0.f}, {0.f, 1.f, 0.f} };

    float positions[36][3] = {  
                                -0.5f, -0.5f, -0.5f,
                                 0.5f, -0.5f, -0.5f,
                                 0.5f,  0.5f, -0.5f,
                                 0.5f,  0.5f, -0.5f,
                                 -0.5f,  0.5f, -0.5f,
                                 -0.5f, -0.5f, -0.5f,

                                 -0.5f, -0.5f,  0.5f,
                                 0.5f, -0.5f,  0.5f,
                                 0.5f,  0.5f,  0.5f,
                                 0.5f,  0.5f,  0.5f,
                                 -0.5f,  0.5f,  0.5f,
                                 -0.5f, -0.5f,  0.5f,

                                 -0.5f,  0.5f,  0.5f,
                                 -0.5f,  0.5f, -0.5f,
                                 -0.5f, -0.5f, -0.5f,
                                 -0.5f, -0.5f, -0.5f,
                                 -0.5f, -0.5f,  0.5f,
                                 -0.5f,  0.5f,  0.5f,

                                 0.5f,  0.5f,  0.5f,
                                 0.5f,  0.5f, -0.5f,
                                 0.5f, -0.5f, -0.5f,
                                 0.5f, -0.5f, -0.5f,
                                 0.5f, -0.5f,  0.5f,
                                 0.5f,  0.5f,  0.5f,

                                 -0.5f, -0.5f, -0.5f,
                                 0.5f, -0.5f, -0.5f,
                                 0.5f, -0.5f,  0.5f,
                                 0.5f, -0.5f,  0.5f,
                                 -0.5f, -0.5f,  0.5f,
                                 -0.5f, -0.5f, -0.5f,

                                 -0.5f,  0.5f, -0.5f,
                                 0.5f,  0.5f, -0.5f,
                                 0.5f,  0.5f,  0.5f,
                                 0.5f,  0.5f,  0.5f,
                                 -0.5f, 0.5f, 0.5f,
                                 -0.5f, 0.5f, -0.5f, };

    std::vector<Vertex> vertices(numVertices);
    glm::mat4 rotate(1.0f);
    rotate = glm::rotate(rotate, glm::radians(degrees), rotationAxis);

    unsigned int vertexInd = 0;
    unsigned int normInd = 0;
    unsigned int normTmp = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 24; j += 2) {
            Vertex v;

            if (normTmp % 6 == 0)
                normInd++;
            glm::vec4 tmp = rotate * glm::vec4(x + (positions[vertexInd][0] / 0.5) * width / 2, y + (positions[vertexInd][1] / 0.5) * height / 2, z + (positions[vertexInd][2] / 0.5) * length / 2, 1);
            v.pos = glm::vec3(tmp.x, tmp.y, tmp.z);
            v.norm = glm::vec3(normSet[normInd][0], normSet[normInd][1], normSet[normInd][2]);
            v.color = color;
            v.texCord = glm::vec2( texSet[i][j%12], texSet[i][j%12 + 1]);
            v.textureID = (float)textID;
            vertices[vertexInd] = v;

            vertexInd++;
            normTmp++;
        }
    }

    return vertices;
}

void Box::setTexture(std::string path)
{

}