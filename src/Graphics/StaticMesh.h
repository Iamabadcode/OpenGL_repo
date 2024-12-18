#pragma once
#include <vector>

#include "ElementBuffer.h"

class StaticMesh
{
private:
	static std::vector<AttribedVertexBuffer> pools;
public:
	StaticMesh(Layout layout, void* verticies, size_t vericies_size);

};
