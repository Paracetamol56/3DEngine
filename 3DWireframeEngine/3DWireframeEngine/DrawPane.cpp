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

void CDrawPane::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void CDrawPane::render(wxDC& dc)
{
	dc.SetBrush(wxBrush(wxColor(150, 150, 150), wxBRUSHSTYLE_SOLID));
    dc.SetPen(wxPen(wxColor(255, 255, 255), 2));
    dc.DrawLine(300, 100, 700, 300);
}

// Constructor
CDrawPane::CDrawPane(wxFrame* parent) : wxPanel( parent )
{
}

// Destructor
CDrawPane::~CDrawPane()
{
}
