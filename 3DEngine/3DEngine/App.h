/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

#pragma once

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

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

#endif // APP_H_INCLUDED