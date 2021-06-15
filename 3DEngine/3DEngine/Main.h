/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Math�o Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

#pragma once

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/wfstream.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/colordlg.h>
#include <wx/colourdata.h>
#include <array>
#include <string>
#include "Triangle.h"
#include "Vector3D.h"
#include "Matrix4.h"
#include "Mesh.h"

// Define custom events
wxDEFINE_EVENT(myID_IMPORT, wxCommandEvent);
wxDEFINE_EVENT(myID_DEFAULTCUBE, wxCommandEvent);
wxDEFINE_EVENT(myID_SHOWINFO, wxCommandEvent);
wxDEFINE_EVENT(myID_SHOWNORMALS, wxCommandEvent);
wxDEFINE_EVENT(myID_SHOWGIZMO, wxCommandEvent);
wxDEFINE_EVENT(myID_SHOWORIGIN, wxCommandEvent);
wxDEFINE_EVENT(myID_RESET, wxCommandEvent);

class CMain : public wxFrame
{
private:
	// Menu
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_fileMenu;
	wxMenu* m_settingMenu;
	wxMenu* m_helpMenu;

	// GUI variables
	bool m_showInfo = true;
	bool m_showNormals = false;
	bool m_showGizmo = true;
	bool m_showOrigin = true;

	// Mesh
	CMesh m_mesh;

private:
	// Projection parametres
	float m_Near = 0.1f;
	float m_Far = 1000.0f;
	float m_Fov = 10.0f;
	float m_AspectRatio = (float)GetSize().GetX() / (float)GetSize().GetY();
	float m_FovRad = 1.0f / tanf(m_Fov * 0.5f / 180.0f * 3.14159f);

	float m_zOffset = 10.0f;

	// Projection matrix
	CMatrix4 m_projMat;

	// Rotation matrix
	CMatrix4 m_rotMat;

	// Main device context
	wxClientDC* m_dc;

	// Rotation angle
	float m_thetaX = 0.0f; // yaw
	float m_thetaY = 0.0f; // pitch
	float m_thetaZ = 0.0f; // roll

	// Pan translation
	float m_transX = 0.0f; // up/down
	float m_transY = 0.0f; // left/right

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

private:
	// Menu events
	void OnQuit(wxCommandEvent& event);
	void OnDefaultCube(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);
	void OnShowPositionInfo(wxCommandEvent& event);
	void OnShowNormals(wxCommandEvent& event);
	void OnShowGizmo(wxCommandEvent& event);
	void OnShowOrigin(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()
};

#endif // MAIN_H_INCLUDED