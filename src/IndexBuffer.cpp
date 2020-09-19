#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_RendererID); // PARAM1: How many buffers do you need, PARAM2: memory address of an unsigned int so that glGenBuffers can write an id to it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // here we are selecting (binding) a buffer. PARAM1: what is the purpose for the buffer, PARAM2: buffer id
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // PARAM1: target, PARAM2: size of buffer, PARAM3: pointer to data, PARAM4: hint to how this buffer is used.
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}