#include "Main.h"

BEGIN_EVENT_TABLE(CMain, wxPanel)
	EVT_KEY_DOWN(CMain::onKeyDown)
	EVT_SIZE(CMain::onResize)
	EVT_CLOSE(CMain::onClose)
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

	// Create the main device context
	m_dc = new wxClientDC(this);

	update();
}

// Destructor
CMain::~CMain()
{
}

// Update function
void CMain::update()
{
	m_dc->Clear();

	// Update the projection matrix
	m_FovRad = 1.0f / tanf(m_Fov / 2.0f * (180.0f / 3.14159f));

	m_projMat.setMatrixAt(0, 0, m_FovRad);
	m_projMat.setMatrixAt(1, 1, m_FovRad);
	m_projMat.setMatrixAt(2, 2, -m_Far / (m_Far - m_Near));
	m_projMat.setMatrixAt(3, 2, (-m_Far * m_Near) / (m_Far - m_Near));
	m_projMat.setMatrixAt(2, 3, -1.0f);

	// Drawing triangles
	CVector3D translationVec((float)GetSize().GetX() / 2, (float)GetSize().GetY() / 2, 0.0f);
	for (CTriangle iTriangle : m_mesh.getTrianlges())
	{
		std::array<CVector3D, 3> projPoints = iTriangle.getPoints();

		for (size_t i = 0; i < 3; i++)
		{
			// Offset
			projPoints.at(i).setZ(projPoints.at(i).getZ() * 3.0);
			// Multiplying each point by the projection matrix
			projPoints.at(i) *= m_projMat;
			// Multiplying each point by the rotation matrix
			projPoints.at(i) *= m_rotMat;
			// Scale up the mesh
			projPoints.at(i) *= 300.0f;
			// Add the translationVec to set the origin to the centre
			projPoints.at(i) += translationVec;
		}

		// Draw each edge of the triangle
		m_dc->SetPen(wxPen(wxColor(255, 255, 255), 2));
		m_dc->DrawLine(projPoints.at(0).getX(), projPoints.at(0).getY(), projPoints.at(1).getX(), projPoints.at(1).getY());
		m_dc->DrawLine(projPoints.at(1).getX(), projPoints.at(1).getY(), projPoints.at(2).getX(), projPoints.at(2).getY());
		m_dc->DrawLine(projPoints.at(2).getX(), projPoints.at(2).getY(), projPoints.at(0).getX(), projPoints.at(0).getY());
	}

	// Draw gizmo and origin
	{
		// Set the origin point
		CVector3D origin(0.0f, 0.0f, 0.0f);
		origin *= m_projMat;
		origin += translationVec;

		// Create 3 vectors for the gizmo
		CVector3D gizmoX(10.0f, 0.0f, 0.0f);
		CVector3D gizmoY(0.0f, 10.0f, 0.0f);
		CVector3D gizmoZ(0.0f, 0.0f, 10.0f);

		// Apply modifications to each vector
		gizmoX = gizmoX * m_projMat * m_rotMat + translationVec;
		gizmoY = gizmoY * m_projMat * m_rotMat + translationVec;
		gizmoZ = gizmoZ * m_projMat * m_rotMat + translationVec;

		// Draw the gizmo
		m_dc->SetPen(wxPen(wxColor(255, 20, 20), 1));
		m_dc->DrawLine(origin.getX(), origin.getY(), gizmoX.getX(), gizmoX.getY());
		m_dc->SetPen(wxPen(wxColor(20, 255, 20), 1));
		m_dc->DrawLine(origin.getX(), origin.getY(), gizmoY.getX(), gizmoY.getY());
		m_dc->SetPen(wxPen(wxColor(20, 20, 255), 1));
		m_dc->DrawLine(origin.getX(), origin.getY(), gizmoZ.getX(), gizmoZ.getY());

		// Draw the origin point in blue
		m_dc->SetPen(wxPen(wxColor(100, 100, 255), 2));
		m_dc->DrawLine(origin.getX() + 3.0f, origin.getY(), origin.getX() - 3.0f, origin.getY());
		m_dc->DrawLine(origin.getX(), origin.getY() + 3.0f, origin.getX(), origin.getY() - 3.0f);
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
	rotMatZ.setMatrixAt(0, 0, cosf(m_thetaZ));
	rotMatZ.setMatrixAt(0, 1, sinf(m_thetaZ));
	rotMatZ.setMatrixAt(1, 0, -sinf(m_thetaZ));
	rotMatZ.setMatrixAt(1, 1, cosf(m_thetaZ));
	rotMatZ.setMatrixAt(2, 2, 1.0f);
	rotMatZ.setMatrixAt(3, 3, 1.0f);

	m_rotMat.setZeros();

	// Multiply the two matrix together
	m_rotMat = rotMatX * rotMatZ;

	// Render with the new matrix
	update();
}

// Key down event handling
void CMain::onKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case wxKeyCode::WXK_LEFT:
	{
		m_thetaZ += 0.1f;
		break;
	}
	case wxKeyCode::WXK_RIGHT:
	{
		m_thetaZ -= 0.1f;
		break;
	}
	case wxKeyCode::WXK_UP:
	{
		m_thetaX += 0.1f;
		break;
	}
	case wxKeyCode::WXK_DOWN:
	{
		m_thetaX -= 0.1f;
		break;
	}
	default:
		break;
	}
	updateRotation();
}

// Resising event handling
void CMain::onResize(wxSizeEvent& event)
{
	m_AspectRatio = (float)GetSize().GetX() / (float)GetSize().GetY();
	updateRotation();
}

// Closing envent handling
void CMain::onClose(wxCloseEvent& event)
{
	if (wxMessageBox("You are about to close... continue closing?",
		"Please confirm",
		wxICON_QUESTION | wxYES_NO) != wxYES)
	{
		event.Veto();
		return;
	}

	Destroy();
}