#pragma once

#include <wx/wx.h>
#include "Vector3D.h"
#include "Triangle.h"

class CDrawPane : public wxPanel
{
public:
	void paintEvent(wxPaintEvent& evt);
	void paintNow(CVector3D point1, CVector3D point2);

	void DrawTraingle(CTriangle, wxDC& dc);
	void render(wxDC& dc);

    DECLARE_EVENT_TABLE()

public:
	// Public constructor and destructor
	CDrawPane(wxFrame* parent);
	~CDrawPane();
};
