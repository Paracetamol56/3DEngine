#pragma once

#include "Triangle.h"
#include <list>

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
};

