#include "Main.h"

BEGIN_EVENT_TABLE(CMain, wxFrame)

	EVT_MENU(myID_IMPORT, CMain::OnImport)
	EVT_MENU(wxID_EXIT, CMain::OnQuit)
	EVT_MENU(myID_SHOWINFO, CMain::OnShowPositionInfo)
	EVT_MENU(myID_SHOWNORMALS, CMain::OnShowNormals)
	EVT_MENU(wxID_ABOUT, CMain::OnAbout)

	EVT_KEY_DOWN(CMain::onKeyDown)
	EVT_MOUSEWHEEL(CMain::onMouseWheel)
	EVT_SIZE(CMain::onResize)
	EVT_CLOSE(CMain::onClose)

END_EVENT_TABLE()

// Constructor
CMain::CMain() : wxFrame(nullptr, wxID_ANY, "3D Engine", wxDefaultPosition, wxSize(1280, 720))
{
	// Set the window backgorud color to black
	SetBackgroundColour(wxColor(20, 20, 20));

	// Create the main device context
	m_dc = new wxClientDC(this);

	// ========= MENU BAR CREATION ========= //

	// Main menu bar
	m_mainMenuBar = new wxMenuBar();

	// File menu
	m_fileMenu = new wxMenu();

	m_fileMenu->Append(myID_IMPORT, _T("Import OBJ file\tCtrl+O"));
	m_fileMenu->AppendSeparator();
	m_fileMenu->Append(wxID_EXIT, _T("&Quit"));

	m_mainMenuBar->Append(m_fileMenu, _T("&File"));

	// Setting menu
	m_settingMenu = new wxMenu();

	m_settingMenu->Append(myID_SHOWINFO, _T("Show position info"));
	m_settingMenu->Append(myID_SHOWNORMALS, _T("Show normals"));

	m_mainMenuBar->Append(m_settingMenu, _T("&Settings"));

	// Help menu
	m_helpMenu = new wxMenu();

	m_helpMenu->Append(wxID_ABOUT, _T("&About\tF1"));

	m_mainMenuBar->Append(m_helpMenu, _T("&Help"));
	
	SetMenuBar(m_mainMenuBar);

	/*
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
	*/

	Update();

	Show();
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
			projPoints.at(i).m_z += m_zOffset;

			// Multiplying each point by the projection matrix
			projPoints.at(i) *= m_projMat;

			// Scale up the mesh
			projPoints.at(i) *= 1000.0f;

			// Add the translationVec to set the origin to the centre
			projPoints.at(i) += translationVec;
		}

		iMassCenter *= m_rotMat;
		iMassCenter.m_z += m_zOffset;
		iMassCenter *= m_projMat;
		iMassCenter *= 1000.0f;
		iMassCenter += translationVec;

		iNormal *= m_rotMat;
		iNormal.m_z += m_zOffset;
		iNormal *= m_projMat;
		iNormal *= 1000.0f;
		iNormal += translationVec;

		// Draw each edge of the triangle
		m_dc->SetPen(wxPen(wxColor(255, 255, 255), 2));
		m_dc->DrawLine(projPoints.at(0).m_x, projPoints.at(0).m_y, projPoints.at(1).m_x, projPoints.at(1).m_y);
		m_dc->DrawLine(projPoints.at(1).m_x, projPoints.at(1).m_y, projPoints.at(2).m_x, projPoints.at(2).m_y);
		m_dc->DrawLine(projPoints.at(2).m_x, projPoints.at(2).m_y, projPoints.at(0).m_x, projPoints.at(0).m_y);

		// Draw the normals
		if (m_showNormals)
		{
			m_dc->SetPen(wxPen(wxColor(255, 100, 0), 1));
			m_dc->DrawLine(iMassCenter.m_x, iMassCenter.m_y, iNormal.m_x, iNormal.m_y);
		}
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

		gizmoX.m_z += m_zOffset;
		gizmoY.m_z += m_zOffset;
		gizmoZ.m_z += m_zOffset;

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
		m_dc->DrawLine(origin.m_x, origin.m_y, gizmoX.m_x, gizmoX.m_y);
		m_dc->SetPen(wxPen(wxColor(20, 255, 20), 1));
		m_dc->DrawLine(origin.m_x, origin.m_y, gizmoY.m_x, gizmoY.m_y);
		m_dc->SetPen(wxPen(wxColor(20, 20, 255), 1));
		m_dc->DrawLine(origin.m_x, origin.m_y, gizmoZ.m_x, gizmoZ.m_y);

		// Draw the origin point in blue
		m_dc->SetPen(wxPen(wxColor(100, 100, 255), 2));
		m_dc->DrawLine(origin.m_x + 3.0f, origin.m_y, origin.m_x - 3.0f, origin.m_y);
		m_dc->DrawLine(origin.m_x, origin.m_y + 3.0f, origin.m_x, origin.m_y - 3.0f);
	}

	// Print upper left corner informativ text
	if (m_showInfo)
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

void CMain::OnQuit(wxCommandEvent& event)
{
	Destroy();
}

void CMain::OnImport(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(nullptr, _("Open a file"), "", "",
		"", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (input_stream.IsOk() == false)
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		wxMessageDialog WarnEmptyDialog(nullptr, "Cannot open file '%s'.", "WARNING", wxICON_EXCLAMATION | wxOK_DEFAULT | wxCENTER, wxDefaultPosition);
		return;
	}
	else
	{
		m_mesh.LoadFromObjectFile(std::string(openFileDialog.GetPath()));
	}

	updateRotation();
}

void CMain::OnShowPositionInfo(wxCommandEvent& event)
{
	m_showInfo = !m_showInfo;
	Update();
}

void CMain::OnShowNormals(wxCommandEvent& event)
{
	m_showNormals = !m_showNormals;
	Update();
}

void CMain::OnAbout(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser("https://github.com/Paracetamol56/3DWireframeEngine");
}
