#pragma once

#include <wx/wx.h>
#include "Triangle.h"
#include "Vector3D.h"
#include "Mesh.h"

class CMain : public wxFrame
{
private:
	CMesh m_mesh;

public:
	// Public constructor and destructor
	CMain();
	~CMain();
};

