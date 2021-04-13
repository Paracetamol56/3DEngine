#pragma once

#include <wx/wx.h>
#include "Main.h"

class CApp : public wxApp
{
public:
	// Public constructor and destructor
	CApp();
	~CApp();

private:
	CMain* m_mainFrame = nullptr;

public:
	virtual bool OnInit();
};

