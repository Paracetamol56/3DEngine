#include "Main.h"

// Constructor
CMain::CMain() : wxFrame(nullptr, wxID_ANY, "3D Engine", wxDefaultPosition, wxSize(1280, 720))
{
	// ========= Example default cube mesh ========= //
	// Bottom face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f), CVector3D(0.0f, 1.0f, 0.0f)));
	// Front face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(0.0f, 0.0f, 1.0f), CVector3D(1.0f, 0.0f, 0.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 0.0f), CVector3D(1.0f, 0.0f, 1.0f), CVector3D(0.0f, 0.0f, 1.0f)));
	// Right face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(1.0f, 0.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 1.0f, 0.0f), CVector3D(1.0f, 0.0f, 0.0f), CVector3D(1.0f, 0.0f, 1.0f)));
	// Back face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 1.0f, 0.0f), CVector3D(0.0f, 1.0f, 1.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	// Left face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(0.0f, 1.0f, 0.0f), CVector3D(0.0f, 1.0f, 1.0f)));
	// Top face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f)));
	// ======== END Example default cube mesh =======//

	// Set the window backgorud color to black
	SetBackgroundColour(wxColor(20, 20, 20));

	// Adding a blank CDrawPane
	m_mainDrawPane = new CDrawPane(this);

	// Initialize the projection matrix
	m_projMat.setMatrixAt(0, 0, m_AspectRatio * m_FovRad);
	m_projMat.setMatrixAt(1, 1, m_FovRad);
	m_projMat.setMatrixAt(2, 2, m_Far / (m_Far - m_Near));
	m_projMat.setMatrixAt(3, 2, (- m_Far * m_Near) / (m_Far - m_Near));
	m_projMat.setMatrixAt(2, 3, 1.0f);
	m_projMat.setMatrixAt(3, 3, 0.0f);
}

// Destructor
CMain::~CMain()
{
}
