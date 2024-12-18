#include "StaticMesh.h"
#include "GL_util.h"

std::vector<AttribedVertexBuffer> StaticMesh::pools;

StaticMesh::StaticMesh(Layout layout, void* verticies, size_t vericies_size)
{
	int pool_index = -1;
	for (int i = 0; i < pools.size(); i++) {
		if (layout == pools[i].layout) {
			pool_index = i;
			break;
		}
	}
	if (pool_index == -1) {
		pools.emplace_back(layout, GL_STATIC_DRAW);
		pool_index = pools.size() - 1;
	}
	//Add to Element Arrays Data


}
