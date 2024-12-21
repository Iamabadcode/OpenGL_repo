#include "ElementBuffer.h"




VertexBuffer::VertexBuffer(const VertexBuffer::Layout& layout, unsigned int usage)
	: m_vertex_buffer_id(NULL), m_attrib_array_id(NULL), m_cpu_vertex_cache(nullptr), m_cache_size(NULL), m_stride(0), m_layout(layout), m_usage(usage)
{
	unsigned int pointer = 0;
	
	for (int i = 0; i < m_layout.size(); i++)
	{
		m_stride += m_layout[i].count * GetGlTypeSize(m_layout[i].GL_Type);
	}

	GLCall(glGenBuffers(1, &m_vertex_buffer_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id));

	GLCall(glGenVertexArrays(1, &m_attrib_array_id));
	GLCall(glBindVertexArray(m_attrib_array_id));

	for(int i = 0; i < m_layout.size(); i++) 
	{
		
		GLCall(glVertexAttribPointer(
			i,
			m_layout[i].count,
			m_layout[i].GL_Type,
			m_layout[i].normalized ? GL_TRUE : GL_FALSE,
			m_stride,
			(void*)pointer
		));
		GLCall(glEnableVertexAttribArray(i));
		pointer += m_layout[i].count * GetGlTypeSize(m_layout[i].GL_Type);
	}
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	Debug::Log("Created vertex buffer", Debug::INFO);
}

VertexBuffer::~VertexBuffer()
{
	if(m_cpu_vertex_cache)	free(m_cpu_vertex_cache);

	GLCall(glDeleteBuffers(1, &m_vertex_buffer_id));
	GLCall(glDeleteVertexArrays(1, &m_attrib_array_id));

	Debug::Log("Released vertex buffer", Debug::INFO);
}

void VertexBuffer::SetData(void* data, unsigned int size)
{
	void* new_data_ptr = malloc(size); ASSERT(new_data_ptr);
	memcpy(new_data_ptr, data, size);
	if(m_cpu_vertex_cache) free(m_cpu_vertex_cache);
	m_cpu_vertex_cache = new_data_ptr;
	m_cache_size = size;
}

void VertexBuffer::AppendData(void* data, unsigned int size)
{
	void* new_data_ptr = malloc(m_cache_size + size); ASSERT(new_data_ptr);
	memcpy(new_data_ptr, m_cpu_vertex_cache, m_cache_size);
	memcpy(reinterpret_cast<char*>(new_data_ptr) + m_cache_size, data, size);
	if(m_cpu_vertex_cache) free(m_cpu_vertex_cache);
	m_cpu_vertex_cache = new_data_ptr;
	m_cache_size += size;
}

void VertexBuffer::BufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, m_cache_size, m_cpu_vertex_cache, m_usage);
}

const VertexBuffer::Layout& VertexBuffer::GetLayout() const
{
	return m_layout;
}

unsigned int VertexBuffer::attribute_array_id() const
{
	return m_attrib_array_id;
}

unsigned int VertexBuffer::VertexCount() const
{
	return m_cache_size / m_stride;
}

