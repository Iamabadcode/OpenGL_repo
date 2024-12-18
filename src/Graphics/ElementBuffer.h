#pragma once
#include <vector>


class Layout
{
private:
	struct Attribute 
	{
	public:
		unsigned int GL_type;
		unsigned int count;
		bool normalized;

		bool operator==(const Attribute& other) const
		{
			if ((GL_type == other.GL_type) && (count == other.count) && (normalized == other.normalized)) {
				return true;
			}
			return false;
		}
	};
	unsigned int m_vertex_array;
	unsigned int m_stride;
public:
	std::vector<Attribute> contents;

	Layout(const std::vector<Attribute>&);
	~Layout();
	bool operator==(const Layout& other) const {

		if (other.contents == contents) {
			return true;
		}
		return false;
	}
};

class AttribedVertexBuffer {
private:
	
	unsigned int m_vertex_buffer;
public:
	Layout layout;

	void* data;
	unsigned int total_mem_size;

	unsigned int m_vertex_array;
	AttribedVertexBuffer(const Layout& _layout, void* _data, unsigned int _size, unsigned int _usage);
	AttribedVertexBuffer(void* _data, unsigned int _size, unsigned int _usage);
	AttribedVertexBuffer(const Layout& _layout, unsigned int _usage);
	AttribedVertexBuffer(unsigned int _usage);

	~AttribedVertexBuffer();

	void AddData(void* data, unsigned int size);


	void BufferData();
};