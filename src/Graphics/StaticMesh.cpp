#include "StaticMesh.h"


StaticMesh::vertex_buffer_group StaticMesh::vertex_buffer_pools;
StaticMesh::index_buffer_group StaticMesh::index_buffer_pool;

StaticMesh::StaticMesh(std::vector<Attribute> layout, void* mesh_vertex_data, unsigned int mem_size)
	: m_vertex_pool_num(-1), m_index_offset(0)
{
	for (int i = 0; i < vertex_buffer_pools.size(); i++) 
	{
		if (layout == vertex_buffer_pools[i].GetLayout()) {
			m_vertex_pool_num = i;	break;
		}
	}
	if (m_vertex_pool_num == -1) 
	{
		vertex_buffer_pools.emplace_back(layout, GL_STATIC_DRAW);
		m_vertex_pool_num = vertex_buffer_pools.size() - 1;
	}	
	ASSERT(vertex_buffer_pools.size() > 0);

	m_index_offset = vertex_buffer_pools[m_vertex_pool_num].VertexCount();
	vertex_buffer_pools[m_vertex_pool_num].AppendData(mesh_vertex_data, mem_size);

	std::cout << "Mesh created, number of current vertex pools is " << vertex_buffer_pools.size() << std::endl;
	std::cout << "size of current vertex pool is " << vertex_buffer_pools[m_vertex_pool_num].VertexCount() << " verticies." << std::endl;
}

StaticMesh::~StaticMesh()
{

}

void StaticMesh::AddProgram(unsigned int program_id, unsigned int* index_buffer_data, unsigned int index_count)
{
	int assigned_pool = -1;
	for (int i = 0; i < index_buffer_pool.size(); i++) {
		if (index_buffer_pool[i].shader_program_id() == program_id) {
			assigned_pool = i;
			break;
		}
	}
	if (assigned_pool < 0) {
		index_buffer_pool.emplace_back(vertex_buffer_pools[m_vertex_pool_num].attribute_array_id(), program_id, GL_STATIC_DRAW);
		assigned_pool = index_buffer_pool.size() - 1;
	} 
	ASSERT(assigned_pool >= 0 && index_buffer_pool.size() > 0); 
	ASSERT(index_buffer_pool[assigned_pool].shader_program_id() == program_id);
	
	programs.emplace_back(assigned_pool, index_buffer_pool[assigned_pool].index_count(), index_count);

	index_buffer_pool[assigned_pool].AppendData(index_buffer_data, index_count);
	index_buffer_pool[assigned_pool].BatchShiftValue(programs[programs.size() - 1].starting_index, index_count, m_index_offset);

	index_buffer_pool[0].BufferData();

	std::cout << "New Program added. Number of programs in this mesh is " << programs.size() << std::endl;
	std::cout << "number of Index Pools is " << index_buffer_pool.size() << ", size of this pool is " << index_buffer_pool[assigned_pool].index_count() << " indicies." << std::endl;
	index_buffer_pool[assigned_pool].Printout();
}

void StaticMesh::DrawFullMesh()
{
	for (int i = 0; i < programs.size(); i++) {
		vertex_buffer_pools[m_vertex_pool_num].Bind();
		index_buffer_pool[programs[i].index_pool_num].Bind();
		glDrawElements(GL_TRIANGLES, programs[i].index_count, GL_UNSIGNED_INT, (void*)programs[i].starting_index);
	}
}

void StaticMesh::LoadAllBuffers()
{
	for(int i = 0; i < vertex_buffer_pools.size(); i++)
	{
		vertex_buffer_pools[i].BufferData();
	}
}