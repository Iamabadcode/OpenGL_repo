#include "StaticMesh.h"
#include "GL_util.h"

unsigned int StaticMesh::count = 0;

std::vector<VertexBuffer> StaticMesh::vertex_buffer_pools;
std::vector<IndexBuffer<unsigned int>> StaticMesh::index_buffer_pools;

StaticMesh::StaticMesh(std::vector<Attribute> layout, void* mesh_vertex_data, unsigned int mem_size)
	: m_vertex_pool_num(-1), m_index_offset(0)
{
	count++;
	for (int i = 0; i < vertex_buffer_pools.size(); i++) 
	{
		if (layout == vertex_buffer_pools[i].GetLayout()) 
		{
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
	vertex_buffer_pools[m_vertex_pool_num].BufferData();
}

StaticMesh::~StaticMesh()
{
	if (m_vertex_pool_num >= 0)
	{
		Debug::Log("Staticmesh released", Debug::INFO);
		count--;
		if (count == 0)
		{
			for (int i = 0; i < index_buffer_pools.size(); i++) {
				index_buffer_pools[i].Free();
			}
			for (int i = 0; i < vertex_buffer_pools.size(); i++) {
				vertex_buffer_pools[i].Free();
			}
			
		}
		m_vertex_pool_num = -1;

	}
		
}

void StaticMesh::AddProgram(unsigned int program_id, unsigned int* index_buffer_data, unsigned int index_count)
{
	ASSERT(m_vertex_pool_num >= 0 && m_vertex_pool_num < vertex_buffer_pools.size());
	int assigned_pool = -1;
	for (int i = 0; i < index_buffer_pools.size(); i++) 
	{
		if (index_buffer_pools[i].shader_program_id() == program_id) 
		{
			assigned_pool = i;
			break;
		}
	}
	if (assigned_pool < 0) 
	{
		index_buffer_pools.push_back({ vertex_buffer_pools[m_vertex_pool_num].attribute_array_id(), program_id, GL_STATIC_DRAW });
		assigned_pool = index_buffer_pools.size() - 1;
	} 
	ASSERT(assigned_pool >= 0 && index_buffer_pools.size() > 0); 
	ASSERT(index_buffer_pools[assigned_pool].shader_program_id() == program_id);
	
	programs.emplace_back(assigned_pool, index_buffer_pools[assigned_pool].index_count(), index_count);

	index_buffer_pools[assigned_pool].AppendData(index_buffer_data, index_count);
	index_buffer_pools[assigned_pool].BatchShiftValue(programs[programs.size() - 1].starting_index, index_count, m_index_offset);

	index_buffer_pools[assigned_pool].BufferData();
}

void StaticMesh::DrawFullMesh()
{
	for (int i = 0; i < programs.size(); i++) 
	{
		vertex_buffer_pools[m_vertex_pool_num].Bind();
		index_buffer_pools[programs[i].index_pool_num].Bind();
		glDrawElements(GL_TRIANGLES, programs[i].index_count, GL_UNSIGNED_INT, (void*)(programs[i].starting_index * sizeof(unsigned int)));
	}
}

void StaticMesh::LoadAllBuffers()
{
	for(int i = 0; i < vertex_buffer_pools.size(); i++)
	{
		vertex_buffer_pools[i].BufferData();
	}
}