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

bool CMesh::LoadFromObjectFile(std::string sFilename)
{
	std::ifstream f(sFilename);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<CVector3D> vertices;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		// New vertex
		if (line[0] == 'v')
		{
			CVector3D v;
			s >> junk >> v.m_x >> v.m_y >> v.m_z;
			vertices.push_back(v);
		}

		// New face
		if (line[0] == 'f')
		{
			int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			m_triangles.push_back({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
		}
	}

	return true;
}
