#include "App.h"

// Entry point definition
wxIMPLEMENT_APP(CApp);

// Constructor
CApp::CApp()
{
}

// Destructor
CApp::~CApp()
{
}

bool CApp::OnInit()
{
	m_mainFrame = new CMain;
	m_mainFrame->Show();

	return true;
}
