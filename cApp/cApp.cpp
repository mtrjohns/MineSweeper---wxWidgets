/*
	Launcher class for wxWidgets
*/

#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	// Create initial GUI frame
	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}
