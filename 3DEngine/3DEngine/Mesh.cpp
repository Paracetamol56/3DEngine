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

bool CMesh::LoadFromObjectFile(std::string sFilePath)
{
	std::ifstream file(sFilePath);
	if (file.is_open() == false)
		return false;

	// Emty old file
	m_triangles.empty();

	// Local cache of verts
	std::vector<CVector3D> vertices;

	while (file.eof() == false)
	{
		char line[256];
		file.getline(line, 256);

		std::strstream ssLine;
		ssLine << line;

		char junk;

		switch (line[0])
		{
		// If the line define a vertex (start with v)
		case 'v':
		{
			if(line[1] == ' ')
			{
				// New vertex
				CVector3D v;
				ssLine >> junk >> v.m_x >> v.m_y >> v.m_z;
				vertices.push_back(v);
			}
			else
			{
				// Other (not yet)
			}
			break;
		}
		// If the line define a face (start with f)
		case 'f':
		{
			// Drop first charactere
			ssLine >> junk;

			std::string tokens[9];
			unsigned int TokenCount = -1;

			while (!ssLine.eof())
			{
				char c = ssLine.get();
				if (c == ' ' || c == '/')
					++ TokenCount;
				else
					tokens[TokenCount].append(1, c);
			}

			CTriangle newTriangle(vertices[std::stoi(tokens[0]) - 1], vertices[std::stoi(tokens[3]) - 1], vertices[std::stoi(tokens[6]) - 1]);
			m_triangles.push_back(newTriangle);
			break;
		}
		default:
			break;
		}
	}

	return true;
}
