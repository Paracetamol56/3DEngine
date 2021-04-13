#include "Main.h"

// Constructor
CMain::CMain() : wxFrame(nullptr, wxID_ANY, "WX Window template")
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

	// Adding a blank CDrawPane
	m_mainDrawPane = new CDrawPane(this);
}

// Destructor
CMain::~CMain()
{
}
