/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

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
	std::ifstream file(sFilename);
	if (file.is_open() == false)
		return false;

	// Local cache of verts
	std::vector<CVector3D> vertices;

	while (file.eof() == false)
	{
		char line[128];
		file.getline(line, 128);

		std::strstream ssLine;
		ssLine << line;

		char junk;

		switch (line[0])
		{
		case 'v':
		{
			// New vertex
			CVector3D v;
			ssLine >> junk >> v.m_x >> v.m_y >> v.m_z;
			vertices.push_back(v);
			break;
		}
		case 'f':
		{
			// New face
			int f[3];
			ssLine >> junk >> f[0] >> f[1] >> f[2];
			CTriangle newTriangle(vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1]);
			m_triangles.push_back(newTriangle);
			break;
		}
		default:
			break;
		}
	}

	return true;
}
