#pragma once

#include <wx/wx.h>
#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Mesh.h"
#include "DrawPane.h"

class CMain : public wxFrame
{
private:
	// Mesh
	CMesh m_mesh;
	// Main draw pane
	CDrawPane*  m_mainDrawPane;

private:
	// Projection parametres
	float m_Near = 0.1f;
	float m_Far = 1000.0f;
	float m_Fov = 90.0f;
	float m_AspectRatio = (float)GetSize().GetY() / (float)GetSize().GetX();
	float m_FovRad = 1.0f / tanf(m_Fov * 0.5f / 180.0f * 3.14159f);

	// Projection matrix
	CMatrix<4> m_projMat;

public:
	// Public constructor and destructor
	CMain();
	~CMain();

	void Update();
};

