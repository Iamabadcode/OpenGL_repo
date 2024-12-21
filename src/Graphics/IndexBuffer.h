#pragma once
#include "GL_util.h"


template<typename index_type>
class IndexBuffer
{
public:
	IndexBuffer(unsigned int vertex_buffer_id, unsigned int shader_program_id, unsigned int usage);
	void Free();

	void SetData(index_type* data, unsigned int count);
	void AppendData(index_type* data, unsigned int count);
	void BatchShiftValue(unsigned int index, unsigned int val_count, unsigned int value_to_add);
	
	void BufferData();
	void Printout();
		
	void Draw();

	inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id); glUseProgram(m_shader_program_id); }
	inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	inline unsigned int shader_program_id() const { return m_shader_program_id; }
	inline unsigned int index_count() const { return m_index_count; }
private:
	unsigned int m_usage;
	index_type* m_cpu_index_cache;
	unsigned int m_index_count;

	unsigned int m_index_buffer_id;
	unsigned int m_shader_program_id;

	unsigned int m_array_buffer_id;

};


template<typename index_type>
IndexBuffer<index_type>::IndexBuffer(unsigned int vertex_buffer_id, unsigned int shader_program_id, unsigned int usage)
	: m_cpu_index_cache(nullptr), m_index_count(0), m_usage(usage), m_array_buffer_id(vertex_buffer_id), m_shader_program_id(shader_program_id)
{
	GLCall(glGenBuffers(1, &m_index_buffer_id));
	Debug::Log("Created index buffer", Debug::INFO);
}

template<typename index_type>
void IndexBuffer<index_type>::Free()
{
	if (m_cpu_index_cache) delete[] m_cpu_index_cache;
	GLCall(glDeleteBuffers(1, &m_index_buffer_id));

	Debug::Log("Released index buffer", Debug::INFO);
}

template<typename index_type>
void IndexBuffer<index_type>::SetData(index_type* data, unsigned int count)
{
	index_type* new_ptr = new index_type[count]; ASSERT(new_ptr); //Allocation failiure
	memcpy(new_ptr, data, count * sizeof(index_type));
	if (m_cpu_index_cache) delete[] m_cpu_index_cache;
	m_index_count = count;
	m_cpu_index_cache = new_ptr;
}

template<typename index_type>
void IndexBuffer<index_type>::AppendData(index_type* data, unsigned int count)
{
	if (!m_cpu_index_cache) { SetData(data, count); return; }
	index_type* new_ptr = new index_type[m_index_count + count]; ASSERT(new_ptr); //Allocation failiure
	memcpy(new_ptr, m_cpu_index_cache, m_index_count * sizeof(index_type));
	memcpy(reinterpret_cast<char*> (new_ptr) + (m_index_count * sizeof(index_type)), data, count * sizeof(index_type));
	delete[] m_cpu_index_cache;
	m_index_count += count;
	m_cpu_index_cache = new_ptr;
}

template<typename index_type>
inline void IndexBuffer<index_type>::BatchShiftValue(unsigned int starting_index, unsigned int val_count, unsigned int value_to_add)
{
	for(int i = starting_index; i < starting_index + val_count; i++)
	{
		m_cpu_index_cache[i] += value_to_add;
	}
}

template<typename index_type>
void IndexBuffer<index_type>::BufferData()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(index_type), m_cpu_index_cache, m_usage);
}

template<typename index_type>
inline void IndexBuffer<index_type>::Printout()
{
	for (int i = 0; i < m_index_count; i++) {
		std::cout << m_cpu_index_cache[i] << ", ";
	}
}

template<typename index_type>
void IndexBuffer<index_type>::Draw()
{
	glUseProgram(0);
	glBindVertexArray(m_array_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_id);

	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
}


