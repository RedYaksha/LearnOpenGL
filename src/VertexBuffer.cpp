#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int usage)
{
    glGenBuffers(1, &m_RendererID); // PARAM1: How many buffers do you need, PARAM2: memory address of an unsigned int so that glGenBuffers can write an id to it.
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // here we are selecting (binding) a buffer. PARAM1: what is the purpose for the buffer, PARAM2: buffer id
    glBufferData(GL_ARRAY_BUFFER, size, data, usage); // PARAM1: target, PARAM2: size of buffer, PARAM3: pointer to data, PARAM4: hint to how this buffer is used.
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}