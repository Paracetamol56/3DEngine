#pragma once

#include <wx/wx.h>
#include "Triangle.h"
#include "Vector3D.h"
#include "Mesh.h"
#include "DrawPane.h"

class CMain : public wxFrame
{
private:
	// Mesh
	CMesh m_mesh;
	// Main draw pane
	CDrawPane*  m_mainDrawPane;

public:
	// Public constructor and destructor
	CMain();
	~CMain();
};

