#pragma once

#include <wx/wx.h>
#include "Triangle.h"

class CDrawPane : public wxPanel
{
public:
	void paintEvent(wxPaintEvent& evt);
	void paintNow();

	void DrawTraingle(CTriangle, wxDC& dc);
	void render(wxDC& dc);

    DECLARE_EVENT_TABLE()

public:
	// Public constructor and destructor
	CDrawPane(wxFrame* parent);
	~CDrawPane();
};
