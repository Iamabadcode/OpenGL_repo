#pragma once
#include <vector>

#include "GL_util.h"
#include "ElementBuffer.h"
#include "IndexBuffer.h"



class StaticMesh
{
public:
	StaticMesh(std::vector<Attribute> layout, void* mesh_vertex_data, unsigned int mem_size);
	~StaticMesh();

	void AddProgram(unsigned int program_id, unsigned int* index_buffer_data, unsigned int index_count);
	
	void DrawFullMesh();

	static void LoadAllBuffers();

private:
	using vertex_buffer_group = std::vector<VertexBuffer>;
	using index_buffer_group = std::vector<IndexBuffer<unsigned int>>;
	
	static vertex_buffer_group vertex_buffer_pools;
	static index_buffer_group index_buffer_pool;

	int m_vertex_pool_num;
	unsigned int m_index_offset;

	
	struct drawn_Program
	{
		unsigned int index_pool_num;
		unsigned int starting_index; // in ibo
		unsigned int index_count;
	};
	std::vector<drawn_Program> programs;

};