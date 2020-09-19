#include "Pyramid.h"
#include "glm/glm.hpp"
#include "VertexBuffer.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/matrix_transform.hpp"

Pyramid::Pyramid(glm::vec3 position, float initHeight, float initAngle, float initDegrees, glm::vec3 initRotationAxis, glm::vec4 initColor, unsigned int textID)
    : Object(position, textID), height(initHeight), angle(initAngle), degrees(initDegrees), rotationAxis(initRotationAxis), color(initColor)
{
    primitive = GL_TRIANGLES;
    numVertices = 12;
}

std::vector<Vertex> Pyramid::genVertices(float xOffset, float yOffset, float zOffset)
{
    float x = xOffset;
    float y = yOffset;
    float z = zOffset;

    glm::vec3 commonPoint(x, y + height / 2, z);

    float hypoCos = (height / glm::tan(glm::radians(angle)))*glm::cos(glm::radians(45.f));
    float hypoSin = (height / glm::tan(glm::radians(angle))) * glm::sin(glm::radians(45.f));
    float bottom_y = y - height / 2;

    glm::vec3 norm_mids[4] = { glm::vec3(x, bottom_y, z-hypoSin), glm::vec3(x + hypoCos, bottom_y, z), glm::vec3(x, bottom_y, z + hypoSin), glm::vec3(x - hypoCos, bottom_y, z) };

    float positions[12][3] = { x-hypoCos, bottom_y, z-hypoSin,
                               x+hypoCos, bottom_y, z-hypoSin,
                               commonPoint.x, commonPoint.y, commonPoint.z,

                               x+hypoCos, bottom_y, z-hypoSin,
                               x+hypoCos, bottom_y, z+hypoSin,
                               commonPoint.x, commonPoint.y, commonPoint.z,

                               x+hypoCos, bottom_y, z+hypoSin,
                               x-hypoCos, bottom_y, z+hypoSin,
                               commonPoint.x, commonPoint.y, commonPoint.z,

                               x-hypoCos, bottom_y, z+hypoSin,
                               x-hypoCos, bottom_y, z-hypoSin,
                               commonPoint.x, commonPoint.y, commonPoint.z
                                                                             };

    std::vector<Vertex> vertices(numVertices);
    glm::mat4 rotate(1.0f);
    glm::mat4 translate(1.f);

    translate = glm::translate(translate, glm::vec3(pos.x, pos.y, pos.z));
    rotate = glm::rotate(rotate, glm::radians(degrees), rotationAxis);
    glm::mat4 transform = translate * rotate;
    unsigned int vertexInd = 0;

    unsigned int norm_tmp = 0;
    unsigned int norm_ind = 0;
    glm::vec3 normBuffer1(1.f);
    glm::vec3 normBuffer2(1.f);
    for (int i = 0; i < 12; i++) {          
        Vertex v;
        glm::vec4 tmp = transform * glm::vec4(positions[vertexInd][0], positions[vertexInd][1], positions[vertexInd][2], 1);
        v.pos = glm::vec3(tmp.x, tmp.y, tmp.z);
        v.color = color;
        v.norm = glm::vec3(0.f);
        v.texCord = glm::vec2(0.f, 0.f);
        v.textureID = (float)textID;
        vertices[vertexInd] = v;
        
        glm::vec3 norm_mid = norm_mids[norm_ind];
        glm::vec4 tmp2 = transform * glm::vec4(norm_mid.x, norm_mid.y, norm_mid.z, 1);
        /* handle the norm */
        switch (norm_tmp)
        {
        case 0:
            normBuffer1 = glm::vec3(tmp.x, tmp.y, tmp.z) - glm::vec3(tmp2.x, tmp2.y, tmp2.z) ;
                break;
        case 1:
            normBuffer2 = commonPoint - glm::vec3(tmp2.x, tmp2.y, tmp2.z);
            break;
        case 2:
            glm::vec3 normal = glm::cross(normBuffer1, normBuffer2);
            vertices[vertexInd].norm = normal;
            vertices[vertexInd - 1].norm = normal;
            vertices[vertexInd - 2].norm = normal;
            norm_tmp = -1;
            norm_ind++;
            break;
        }
        norm_tmp++;
        vertexInd++;
    }
    return vertices;
}

void Pyramid::setTexture(std::string path)
{

}