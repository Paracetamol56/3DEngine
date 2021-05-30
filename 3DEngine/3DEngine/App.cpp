/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

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
