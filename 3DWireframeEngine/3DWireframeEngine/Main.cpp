#include "Main.h"

BEGIN_EVENT_TABLE(CMain, wxPanel)
	EVT_PAINT(CMain::Update)
END_EVENT_TABLE()

// Constructor
CMain::CMain() : wxFrame(nullptr, wxID_ANY, "3D Engine", wxDefaultPosition, wxSize(1280, 720))
{
	// ========= Example default cube mesh ========= //
	// Bottom face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(0.0f, 0.0f, 1.0f), CVector3D(0.0f, 0.0f, 0.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 0.0f, 0.0f)));
	// Front face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(0.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f), CVector3D(1.0f, 0.0f, 0.0f)));
	// Right face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(1.0f, 0.0f, 1.0f)));
	// Back face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f), CVector3D(0.0f, 0.0f, 1.0f)));
	// Left face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.0f, 1.0f), CVector3D(0.0f, 1.0f, 0.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 0.0f, 1.0f), CVector3D(0.0f, 1.0f, 0.0f), CVector3D(0.0f, 0.0f, 0.0f)));
	// Top face
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 1.0f, 0.0f), CVector3D(0.0f, 1.0f, 1.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(0.0f, 1.0f, 0.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(1.0f, 1.0f, 0.0f)));
	// ======== END Example default cube mesh =======//

	// Set the window backgorud color to black
	SetBackgroundColour(wxColor(20, 20, 20));

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

// Update function
void CMain::Update(wxPaintEvent& event)
{
	// Update the projection matrix
	m_projMat.setMatrixAt(0, 0, m_AspectRatio * m_FovRad);
	m_projMat.setMatrixAt(1, 1, m_FovRad);
	m_projMat.setMatrixAt(2, 2, m_Far / (m_Far - m_Near));
	m_projMat.setMatrixAt(3, 2, (-m_Far * m_Near) / (m_Far - m_Near));
	m_projMat.setMatrixAt(2, 3, 1.0f);
	m_projMat.setMatrixAt(3, 3, 0.0f);

	wxPaintDC dc(this);
	CVector3D translationVec((float)GetSize().GetX() / 2, (float)GetSize().GetY() / 2, 0.0f);
	for (CTriangle iTriangle : m_mesh.getTrianlges())
	{
		std::array<CVector3D, 3> projPoints = iTriangle.getPoints();

		// Multiplying each point by the projection matrix
		for (size_t i = 0; i < 3; i++)
		{
			projPoints.at(i) *= m_projMat;
		}

		// Add the translationVec to set the origin to the centre
		for (size_t i = 0; i < 3; i++)
		{
			projPoints.at(i) += translationVec;
		}

		dc.SetPen(wxPen(wxColor(255, 255, 255), 2));
		dc.DrawLine(projPoints.at(0).getX(), projPoints.at(0).getY(), projPoints.at(1).getX(), projPoints.at(1).getY());
		dc.DrawLine(projPoints.at(1).getX(), projPoints.at(1).getY(), projPoints.at(2).getX(), projPoints.at(2).getY());
		dc.DrawLine(projPoints.at(2).getX(), projPoints.at(2).getY(), projPoints.at(0).getX(), projPoints.at(0).getY());
	}
}
