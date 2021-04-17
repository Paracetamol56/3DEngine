#include "Main.h"

BEGIN_EVENT_TABLE(CMain, wxPanel)
	EVT_KEY_DOWN(CMain::onKeyDown)
	EVT_MOUSEWHEEL(CMain::onMouseWheel)
	EVT_SIZE(CMain::onResize)
	EVT_CLOSE(CMain::onClose)
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

	// Create the main device context
	m_dc = new wxClientDC(this);

	updateRotation();
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
	CVector3D translationVec((float)GetSize().GetX() / 2 + m_transX, (float)GetSize().GetY() / 2 + m_transY, 0.0f);

	for (CTriangle iTriangle : m_mesh.getTrianlges())
	{
		std::array<CVector3D, 3> projPoints = iTriangle.getPoints();
		CVector3D iMassCenter = iTriangle.getMassCenter();
		CVector3D iNormal = iTriangle.getNormal();
		iNormal += iMassCenter;

		for (size_t i = 0; i < 3; i++)
		{
			// Multiplying each point by the rotation matrix
			projPoints.at(i) *= m_rotMat;

			// Offset 
			projPoints.at(i).setZ(projPoints.at(i).getZ() + m_zOffset);

			// Multiplying each point by the projection matrix
			projPoints.at(i) *= m_projMat;

			// Scale up the mesh
			projPoints.at(i) *= 1000.0f;

			// Add the translationVec to set the origin to the centre
			projPoints.at(i) += translationVec;
		}

		iMassCenter *= m_rotMat;
		iMassCenter.setZ(iMassCenter.getZ() + m_zOffset);
		iMassCenter *= m_projMat;
		iMassCenter *= 1000.0f;
		iMassCenter += translationVec;

		iNormal *= m_rotMat;
		iNormal.setZ(iNormal.getZ() + m_zOffset);
		iNormal *= m_projMat;
		iNormal *= 1000.0f;
		iNormal += translationVec;

		// Draw each edge of the triangle
		m_dc->SetPen(wxPen(wxColor(255, 255, 255), 2));
		m_dc->DrawLine(projPoints.at(0).getX(), projPoints.at(0).getY(), projPoints.at(1).getX(), projPoints.at(1).getY());
		m_dc->DrawLine(projPoints.at(1).getX(), projPoints.at(1).getY(), projPoints.at(2).getX(), projPoints.at(2).getY());
		m_dc->DrawLine(projPoints.at(2).getX(), projPoints.at(2).getY(), projPoints.at(0).getX(), projPoints.at(0).getY());

		// Draw the normals
		m_dc->SetPen(wxPen(wxColor(255, 100, 0), 1));
		m_dc->DrawLine(iMassCenter.getX(), iMassCenter.getY(), iNormal.getX(), iNormal.getY());
	}

	// Draw gizmo and origin
	{
		// Set the origin point
		CVector3D origin(0.0f, 0.0f, 0.0f);
		origin *= m_projMat;
		origin += translationVec;

		// Create 3 vectors for the gizmo
		CVector3D gizmoX(1.0f, 0.0f, 0.0f);
		CVector3D gizmoY(0.0f, 1.0f, 0.0f);
		CVector3D gizmoZ(0.0f, 0.0f, 1.0f);

		// Apply modifications to each vector
		gizmoX *= m_rotMat;
		gizmoY *= m_rotMat;
		gizmoZ *= m_rotMat;

		gizmoX.setZ(gizmoX.getZ() + m_zOffset);
		gizmoY.setZ(gizmoY.getZ() + m_zOffset);
		gizmoZ.setZ(gizmoZ.getZ() + m_zOffset);

		gizmoX *= m_projMat;
		gizmoY *= m_projMat;
		gizmoZ *= m_projMat;

		gizmoX *= 1000.0f;
		gizmoY *= 1000.0f;
		gizmoZ *= 1000.0f;

		gizmoX += translationVec;
		gizmoY += translationVec;
		gizmoZ += translationVec;

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

	// Print upper left corner informativ text
	{
		m_dc->SetTextForeground(wxColor(255, 255, 255));
		m_dc->DrawText(wxString("RotXYZ: " + std::to_string(m_thetaX) + ", " + std::to_string(m_thetaY) + ", " + std::to_string(m_thetaZ)), 10, 10);
		m_dc->DrawText(wxString("PanXY: " + std::to_string(m_transX) + ", " + std::to_string(m_transY)), 10, 25);
		m_dc->DrawText(wxString("ZOffset: " + std::to_string(m_zOffset)), 10, 40);
	}
}

void CMain::updateRotation()
{
	// More infos : https://en.wikipedia.org/wiki/Rotation_matrix

	m_rotMat.setMatrixAt(0, 0, cosf(m_thetaX) * cosf(m_thetaY));
	m_rotMat.setMatrixAt(0, 1, cosf(m_thetaX) * sinf(m_thetaY) * sinf(m_thetaZ) - sinf(m_thetaX) * cosf(m_thetaZ));
	m_rotMat.setMatrixAt(0, 2, cosf(m_thetaX) * sinf(m_thetaY) * cosf(m_thetaZ) + sinf(m_thetaX) * sinf(m_thetaZ));

	m_rotMat.setMatrixAt(1, 0, sinf(m_thetaX) * cosf(m_thetaY));
	m_rotMat.setMatrixAt(1, 1, sinf(m_thetaX) * sinf(m_thetaY) * sinf(m_thetaZ) + cosf(m_thetaX) * cosf(m_thetaZ));
	m_rotMat.setMatrixAt(1, 2, sinf(m_thetaX) * sinf(m_thetaY) * cosf(m_thetaZ) - cosf(m_thetaX) * sinf(m_thetaZ));

	m_rotMat.setMatrixAt(2, 0, -sinf(m_thetaY));
	m_rotMat.setMatrixAt(2, 1, cosf(m_thetaY) * sinf(m_thetaZ));
	m_rotMat.setMatrixAt(2, 2, cosf(m_thetaY) * cosf(m_thetaZ));

	m_rotMat.setMatrixAt(3, 3, 1.0f);

	// Render with the new matrix
	update();
}

// Key down event handling
void CMain::onKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode())
	{
	case wxKeyCode::WXK_LEFT:
		m_thetaX += 0.1570796f;
		break;
	case wxKeyCode::WXK_RIGHT:
		m_thetaX -= 0.1570796f;
		break;
	case wxKeyCode::WXK_UP:
		m_thetaZ += 0.1570796f;
		break;
	case wxKeyCode::WXK_DOWN:
		m_thetaZ -= 0.1570796f;
		break;
	case wxKeyCode::WXK_NUMPAD4:
		m_transX -= 50.0f;
		break;
	case wxKeyCode::WXK_NUMPAD6:
		m_transX += 50.0f;
		break;
	case wxKeyCode::WXK_NUMPAD8:
		m_transY -= 50.0f;
		break;
	case wxKeyCode::WXK_NUMPAD2:
		m_transY += 50.0f;
		break;
	default:
		break;
	}
	updateRotation();
}

// Mouse wheel event handling
void CMain::onMouseWheel(wxMouseEvent& event)
{
	if (event.GetWheelRotation() > 0)
	{
		// Dezoom constraint when GetWheelRotation is positiv
		float testVal = m_zOffset + event.GetWheelRotation() / 100.0f;
		if (testVal < 1000.0f)
		{
			m_zOffset = testVal;
		}
	}
	else
	{
		// Dezoom constraint when GetWheelRotation is negativ
		float testVal = m_zOffset + event.GetWheelRotation() / 100.0f;
		if (testVal > 1.0f)
		{
			m_zOffset = testVal;
		}
	}

	update();
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