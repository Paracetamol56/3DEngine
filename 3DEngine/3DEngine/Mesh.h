/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

#pragma once

#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include "Triangle.h"
#include "Vector3D.h"
#include <list>
#include <vector>
#include <string>
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

	// Default cube loader
	void LoadDefaultCube();

	// OBJ loader
	bool LoadFromObjectFile(std::string sFilename);
};

#endif // MESH_H_INCLUDED