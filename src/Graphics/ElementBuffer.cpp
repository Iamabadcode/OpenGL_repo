#include <GL/glew.h>

#include "ElementBuffer.h"
#include "GL_util.h"

/*
* input: GL_type, count, normalized
* 
* 
*/

Layout::Layout(const std::vector<Layout::Attribute>& layout)
	:	contents(layout){}

Layout::~Layout()
{
	GLCall(glDeleteVertexArrays(1, &m_vertex_array));
}

AttribedVertexBuffer::AttribedVertexBuffer(const Layout& _layout, void* data, unsigned int size, unsigned int usage)
	:	layout(_layout)
{	
	unsigned int pointer = 0;
	unsigned int type_size = 0;
	unsigned int stride = 0;

	for (size_t i = 0; i < _layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(_layout.contents[i].GL_type);
		stride += _layout.contents[i].count * type_size;
	}

	GLCall(glGenVertexArrays(1, &m_vertex_array));
	GLCall(glBindVertexArray(m_vertex_array));

	GLCall(glCreateBuffers(1, &m_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));

	for (size_t i = 0; i < _layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(_layout.contents[i].GL_type);

		GLCall(glVertexAttribPointer(
			i,
			_layout.contents[i].count,
			_layout.contents[i].GL_type,
			_layout.contents[i].normalized ? GL_TRUE : GL_FALSE,
			stride,
			(void*)pointer
		));
		GLCall(glEnableVertexAttribArray(i));
		pointer += _layout.contents[i].count * type_size;
	}
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

AttribedVertexBuffer::AttribedVertexBuffer(const Layout& _layout, unsigned int usage)
	:	layout(_layout)
{
	unsigned int pointer = 0;
	unsigned int type_size = 0;
	unsigned int stride = 0;

	for (size_t i = 0; i < _layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(_layout.contents[i].GL_type);
		stride += _layout.contents[i].count * type_size;
	}

	GLCall(glGenVertexArrays(1, &m_vertex_array));
	GLCall(glBindVertexArray(m_vertex_array));

	GLCall(glCreateBuffers(1, &m_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));

	for (size_t i = 0; i < _layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(_layout.contents[i].GL_type);

		GLCall(glVertexAttribPointer(
			i,
			_layout.contents[i].count,
			_layout.contents[i].GL_type,
			_layout.contents[i].normalized ? GL_TRUE : GL_FALSE,
			stride,
			(void*)pointer
		));
		GLCall(glEnableVertexAttribArray(i));
		pointer += _layout.contents[i].count * type_size;
	}
}

AttribedVertexBuffer::AttribedVertexBuffer(void* data, unsigned int size, unsigned int usage)
	: layout({ {GL_FLOAT, 2, false} })
{
	unsigned int pointer = 0;
	unsigned int type_size = 0;
	unsigned int stride = 0;

	for (size_t i = 0; i < layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(layout.contents[i].GL_type);
		stride += layout.contents[i].count * type_size;
	}

	GLCall(glGenVertexArrays(1, &m_vertex_array));
	GLCall(glBindVertexArray(m_vertex_array));

	GLCall(glCreateBuffers(1, &m_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));

	for (size_t i = 0; i < layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(layout.contents[i].GL_type);

		GLCall(glVertexAttribPointer(
			i,
			layout.contents[i].count,
			layout.contents[i].GL_type,
			layout.contents[i].normalized ? GL_TRUE : GL_FALSE,
			stride,
			(void*)pointer
		));
		GLCall(glEnableVertexAttribArray(i));
		pointer += layout.contents[i].count * type_size;
	}
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

AttribedVertexBuffer::AttribedVertexBuffer(unsigned int usage)
	: layout({ {GL_FLOAT, 2, false} })
{
	
	unsigned int pointer = 0;
	unsigned int type_size = 0;
	unsigned int stride = 0;

	for (size_t i = 0; i < layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(layout.contents[i].GL_type);
		stride += layout.contents[i].count * type_size;
	}

	GLCall(glGenVertexArrays(1, &m_vertex_array));
	GLCall(glBindVertexArray(m_vertex_array));

	GLCall(glCreateBuffers(1, &m_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer));

	for (size_t i = 0; i < layout.contents.size(); i++)
	{
		type_size = GetGlTypeSize(layout.contents[i].GL_type);

		GLCall(glVertexAttribPointer(
			i,
			layout.contents[i].count,
			layout.contents[i].GL_type,
			layout.contents[i].normalized ? GL_TRUE : GL_FALSE,
			stride,
			(void*)pointer
		));
		GLCall(glEnableVertexAttribArray(i));
		pointer += layout.contents[i].count * type_size;
	}
	int size = 0;
	unsigned int data[] = {0};
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));

}

AttribedVertexBuffer::~AttribedVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_vertex_buffer));
	GLCall(glDeleteVertexArrays(1, &m_vertex_array));
}

void AttribedVertexBuffer::AddData(void* new_data, unsigned int new_data_size)
{
	void* resized_data = std::realloc(data, total_mem_size + new_data_size);
	ASSERT(resized_data);
	memcpy(reinterpret_cast<char*>(resized_data) + total_mem_size, new_data, new_data_size);
	std::free(data);
	std::free(new_data);
	data = resized_data;
}



void AttribedVertexBuffer::BufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER,  m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, total_mem_size, data, GL_STATIC_DRAW);
}


