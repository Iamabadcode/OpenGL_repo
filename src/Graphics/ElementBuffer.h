#pragma once
#include <vector>
#include "GL_util.h"


struct Attribute
{
	unsigned int GL_Type;
	unsigned int count;
	bool normalized;

	bool operator==(const Attribute& other) const = default;	
};

class VertexBuffer
{
public:
	using Layout = typename std::vector<Attribute>;

	VertexBuffer(const Layout& layout, unsigned int usage);
	~VertexBuffer();

	void Bind() const { glBindVertexArray(m_attrib_array_id); }
	void Unbind() const { glBindVertexArray(0); }
	
	void SetData(void* data, unsigned int size);
	void AppendData(void* data, unsigned int size);
	void BufferData();

	const Layout& GetLayout() const;
	unsigned int attribute_array_id() const;
	unsigned int VertexCount() const;

private:
	Layout m_layout;
	void* m_cpu_vertex_cache;
	size_t m_cache_size;
	
	unsigned int m_attrib_array_id;
	unsigned int m_vertex_buffer_id;

	unsigned int m_stride;
	unsigned int m_usage;
};

