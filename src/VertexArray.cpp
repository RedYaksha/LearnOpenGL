#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	/* this is for a single vertex. */
	Bind(); 
	vb.Bind();

	/* setup layout */
	const auto& elements = layout.GetElements();

	/*
		Loop through all the vertex's attributes(elements) and specify which bytes are being defined as a single attribute.
	*/
	unsigned int offset = 0;
	int elements_size = elements.size();
	for (unsigned int i = 0; i < elements_size; i++)
	{
		const auto& element = elements[i]; // this is the abstract data representation of an attribute
		GLCall(glEnableVertexAttribArray(i)); //enables the attribute
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset)); // this modifies the current VAO's state, and specifies where the attribute is in the currently bound Vertex Buffer.
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type); // prepare offset for the next attribute
	}
	
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}