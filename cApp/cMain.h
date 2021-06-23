#pragma once
#include "wx\wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	// Dynamically changing type variables
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;

	int* nField = nullptr;
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

