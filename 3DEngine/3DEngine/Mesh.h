#pragma once

#include "Triangle.h"
#include "Vector3D.h"
#include <list>
#include <vector>
#include <strstream>
#include <fstream>

class CMesh
{
private:
	std::list<CTriangle> m_triangles = {};

public:
	// Public constructor and destructor
	CMesh();
	~CMesh();

	// Getters
	std::list<CTriangle> getTrianlges();

	// Setters
	void addTriangle( CTriangle tri );

	// OBJ loader
	bool LoadFromObjectFile(std::string sFilename);
};

