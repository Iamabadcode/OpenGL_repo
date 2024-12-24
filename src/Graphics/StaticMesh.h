#pragma once
#include <vector>

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
	static void FastDraw();
private:
	static unsigned int count;

	static std::vector<VertexBuffer> vertex_buffer_pools;
	static std::vector<IndexBuffer<unsigned int>> index_buffer_pools;


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