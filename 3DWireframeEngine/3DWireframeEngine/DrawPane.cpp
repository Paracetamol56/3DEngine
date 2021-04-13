#include "DrawPane.h"

BEGIN_EVENT_TABLE(CDrawPane, wxPanel)

 // catch paint events
	EVT_PAINT(CDrawPane::paintEvent)

END_EVENT_TABLE()

void CDrawPane::paintEvent(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void CDrawPane::paintNow(CVector3D point1, CVector3D point2)
{
	wxClientDC dc(this);
	dc.SetPen(wxPen(wxColor(255, 255, 255), 100));
	dc.DrawLine(point1.getX(), point1.getY(), point2.getX(), point2.getY());
	render(dc);
}

void CDrawPane::render(wxDC& dc)
{
    /*dc.SetPen(wxPen(wxColor(255, 255, 255), 2));
    dc.DrawLine(300, 100, 700, 300);*/
}

// Constructor
CDrawPane::CDrawPane(wxFrame* parent) : wxPanel( parent )
{
}

// Destructor
CDrawPane::~CDrawPane()
{
}
