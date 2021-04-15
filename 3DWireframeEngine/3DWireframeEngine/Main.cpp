#include "Main.h"

BEGIN_EVENT_TABLE(CMain, wxPanel)
	EVT_PAINT(CMain::Update)
	EVT_KEY_DOWN(CMain::OnKeyDown)
	EVT_SIZE(CMain::OnResize)
END_EVENT_TABLE()

// Constructor
CMain::CMain() : wxFrame(nullptr, wxID_ANY, "3D Engine", wxDefaultPosition, wxSize(1280, 720))
{
	// ========= Example default cube mesh ========= //
	// Bottom face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, 1.0f), CVector3D(-1.0f, -1.0f, 1.0f), CVector3D(-1.0f, -1.0f, -1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, 1.0f), CVector3D(-1.0f, -1.0f, -1.0f), CVector3D(1.0f, -1.0f, -1.0f)));
	// Front face
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, -1.0f, -1.0f), CVector3D(-1.0f, 1.0f, -1.0f), CVector3D(1.0f, 1.0f, -1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, -1.0f, -1.0f), CVector3D(1.0f, 1.0f, -1.0f), CVector3D(1.0f, -1.0f, -1.0f)));
	// Right face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, -1.0f), CVector3D(1.0f, 1.0f, -1.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, -1.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(1.0f, -1.0f, 1.0f)));
	// Back face
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, -1.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(-1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(1.0f, -1.0f, 1.0f), CVector3D(-1.0f, 1.0f, 1.0f), CVector3D(-1.0f, -1.0f, 1.0f)));
	// Left face
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, -1.0f, 1.0f), CVector3D(-1.0f, 1.0f, -1.0f), CVector3D(-1.0f, 1.0f, -1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, -1.0f, 1.0f), CVector3D(-1.0f, 1.0f, -1.0f), CVector3D(-1.0f, -1.0f, -1.0f)));
	// Top face
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, 1.0f, -1.0f), CVector3D(-1.0f, 1.0f, 1.0f), CVector3D(1.0f, 1.0f, 1.0f)));
	m_mesh.addTriangle(CTriangle(CVector3D(-1.0f, 1.0f, -1.0f), CVector3D(1.0f, 1.0f, 1.0f), CVector3D(1.0f, 1.0f, -1.0f)));
	// ======== END Example default cube mesh =======//

	// Set the window backgorud color to black
	SetBackgroundColour(wxColor(20, 20, 20));
}

// Destructor
CMain::~CMain()
{
}

// Update function
void CMain::update(wxPaintEvent& event)
{
	// Update the rotation matrix
	updateRotation();

	// Create the main device context
	wxPaintDC dc(this);

	// Update the projection matrix
	m_projMat.setMatrixAt(0, 0, m_FovRad);
	m_projMat.setMatrixAt(1, 1, m_FovRad);
	m_projMat.setMatrixAt(2, 2, m_Far / (m_Far - m_Near));
	m_projMat.setMatrixAt(3, 2, (-m_Far * m_Near) / (m_Far - m_Near));
	m_projMat.setMatrixAt(2, 3, 1.0f);
	m_projMat.setMatrixAt(3, 3, 0.0f);

	// Drawing triangles
	CVector3D translationVec((float)GetSize().GetX() / 2, (float)GetSize().GetY() / 2, 0.0f);
	for (CTriangle iTriangle : m_mesh.getTrianlges())
	{
		std::array<CVector3D, 3> projPoints = iTriangle.getPoints();

		for (size_t i = 0; i < 3; i++)
		{
			// Multiplying each point by the projection matrix
			projPoints.at(i) *= m_projMat;
			// Scale up the mesh
			projPoints.at(i) *= 100.0f;
			// Add the translationVec to set the origin to the centre
			projPoints.at(i) += translationVec;
		}

		// Draw each edge of the triangle
		dc.SetPen(wxPen(wxColor(255, 255, 255), 2));
		dc.DrawLine(projPoints.at(0).getX(), projPoints.at(0).getY(), projPoints.at(1).getX(), projPoints.at(1).getY());
		dc.DrawLine(projPoints.at(1).getX(), projPoints.at(1).getY(), projPoints.at(2).getX(), projPoints.at(2).getY());
		dc.DrawLine(projPoints.at(2).getX(), projPoints.at(2).getY(), projPoints.at(0).getX(), projPoints.at(0).getY());
	}

	{
		// Set the origin point
		CVector3D origin(0.0f, 0.0f, 0.0f);
		origin *= m_projMat;
		origin += translationVec;

		// Draw the gizmo
		CVector3D gizmoX(10.0f, 0.0f, 0.0f);
		CVector3D gizmoY(0.0f, 10.0f, 0.0f);
		CVector3D gizmoZ(0.0f, 0.0f, 10.0f);
		gizmoX = gizmoX * m_projMat + translationVec;
		gizmoY = gizmoY * m_projMat + translationVec;
		gizmoZ = gizmoZ * m_projMat + translationVec;
		dc.SetPen(wxPen(wxColor(255, 20, 20), 2));
		dc.DrawLine(origin.getX(), origin.getY(), gizmoX.getX(), gizmoX.getY());
		dc.SetPen(wxPen(wxColor(20, 255, 20), 2));
		dc.DrawLine(origin.getX(), origin.getY(), gizmoY.getX(), gizmoY.getY());
		dc.SetPen(wxPen(wxColor(20, 20, 255), 2));
		dc.DrawLine(origin.getX(), origin.getY(), gizmoZ.getX(), gizmoZ.getY());

		// Draw the origin point in blue
		dc.SetPen(wxPen(wxColor(100, 100, 255), 2));
		dc.DrawLine(origin.getX() + 3.0f, origin.getY(), origin.getX() - 3.0f, origin.getY());
		dc.DrawLine(origin.getX(), origin.getY() + 3.0f, origin.getX(), origin.getY() - 3.0f);
	}
}

void CMain::updateRotation()
{
	CMatrix4 rotMatX;
	CMatrix4 rotMatZ;

	// Compute the X rotation matrix
	rotMatX.setMatrixAt(0, 0, 1.0f);
	rotMatX.setMatrixAt(1, 1, cosf(m_thetaX));
	rotMatX.setMatrixAt(1, 2, sinf(m_thetaX));
	rotMatX.setMatrixAt(2, 1, -sinf(m_thetaX));
	rotMatX.setMatrixAt(2, 2, cosf(m_thetaX));
	rotMatX.setMatrixAt(3, 3, 1.0f);

	// Compute the Z rotation matrix
	rotMatZ.setMatrixAt(0, 0, cosf(m_thetaX));
	rotMatZ.setMatrixAt(0, 1, sinf(m_thetaX));
	rotMatZ.setMatrixAt(1, 0, -sinf(m_thetaX));
	rotMatZ.setMatrixAt(1, 1, cosf(m_thetaX));
	rotMatZ.setMatrixAt(2, 2, 1.0f);
	rotMatZ.setMatrixAt(3, 3, 1.0f);

	m_rotMat.setZeros();

	// Multiply the two matrix together
	m_rotMat = rotMatX * rotMatZ;
}

// Key event handling
void CMain::OnKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case wxKeyCode::WXK_LEFT:
	{
		m_thetaX += 1.0f;
		break;
	}
	case wxKeyCode::WXK_RIGHT:
	{
		m_thetaX -= 1.0f;
		break;
	}
	default:
		break;
	}
}

void CMain::OnResize(wxSizeEvent& event)
{
	this->InvalidateBestSize();
	event.Skip();
}
