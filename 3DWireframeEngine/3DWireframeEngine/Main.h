#pragma once

#include <wx/wx.h>
#include <array>
#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix4.h"
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
	float m_Fov = 90.0f;
	float m_AspectRatio = (float)GetSize().GetX() / (float)GetSize().GetY();
	float m_FovRad = 1.0f / tanf(m_Fov * 0.5f / 180.0f * 3.14159f);

	// Projection matrix
	CMatrix4 m_projMat;

	// Rotation matrix
	CMatrix4 m_rotMat;

	// Main device context
	wxClientDC* m_dc;

	// Rotation angle
	float m_thetaX = 0.0f;
	float m_thetaZ = 0.0f;

public:
	// Public constructor and destructor
	CMain();
	~CMain();

public:
	// Update content
	void update();

	// Update rotation matrix
	void updateRotation();

	// Key down event
	void onKeyDown(wxKeyEvent& event);

	// Mouse wheel event
	void onMouseWheel(wxMouseEvent& event);

	// Resize event
	void onResize(wxSizeEvent& event);

	// Close event
	void onClose(wxCloseEvent& event);

	DECLARE_EVENT_TABLE()
};

