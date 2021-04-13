#include "Mesh.h"

// Constructor
CMesh::CMesh()
{
}

//Destructor
CMesh::~CMesh()
{
}

// Triangles getter
std::list<CTriangle> CMesh::getTrianlges()
{
	return m_triangles;
}

// Add a triangle to the list
void CMesh::addTriangle(CTriangle tri)
{
	m_triangles.push_back(tri);
}
