#pragma once

#include <vector>
#include "GL_util.h"


struct Attribute
{
	unsigned int GL_Type;
	unsigned int count;
	bool normalized;

	Attribute(int type, int count, bool norm)	: GL_Type(type), count(count), normalized(norm) {}

	bool operator==(const Attribute& other) const = default;	
};

class VertexBuffer
{
public:
	using Layout = typename std::vector<Attribute>;

	VertexBuffer(const Layout& layout, unsigned int usage);
	void Free();

	void SetData(void* data, unsigned int size);
	void AppendData(void* data, unsigned int size);
	void BufferData();

	inline void Bind() const { glBindVertexArray(m_attrib_array_id); }
	inline static void Unbind() { glBindVertexArray(0); }
	inline const Layout& GetLayout() const { return m_layout; }
	inline unsigned int attribute_array_id() const { return m_attrib_array_id; }
	inline unsigned int VertexCount() const { return m_cache_size / m_stride; }

private:
	Layout m_layout;
	void* m_cpu_vertex_cache;
	size_t m_cache_size;
	
	unsigned int m_attrib_array_id;
	unsigned int m_vertex_buffer_id;

	unsigned int m_stride;
	unsigned int m_usage;
};

