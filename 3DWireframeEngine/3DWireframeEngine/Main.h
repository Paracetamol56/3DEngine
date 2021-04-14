#pragma once

#include <wx/wx.h>
#include <array>
#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix.h"
#include "Mesh.h"

class CMain : public wxFrame
{
private:
	// Mesh
	CMesh m_mesh;

private:
	// Projection parametres
	float m_Near = 0.1f;
	float m_Far = 1000.0f;
	float m_Fov = 20.0f;
	float m_AspectRatio = (float)GetSize().GetY() / (float)GetSize().GetX();
	float m_FovRad = 1.0f / tanf(m_Fov * 0.5f / 180.0f * 3.14159f);
	float m_theta = 0.0f;
	float m_elapsedTime = 0.0f;

	// Projection matrix
	CMatrix<4> m_projMat;

public:
	// Public constructor and destructor
	CMain();
	~CMain();

	void Update(wxPaintEvent& event);

	DECLARE_EVENT_TABLE()
};

