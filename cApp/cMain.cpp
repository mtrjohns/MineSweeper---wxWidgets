/*
	Start of the Graphical User Interface
*/

#include "cMain.h"

// (name of class that requires event, base class)
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	// (windows key id for button being clicked, function being called)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "wxWidgets", wxPoint(5, 50), wxSize(800, 600))
{
	// Create an Array of buttons
	btn = new wxButton* [nFieldWidth * nFieldHeight];

	// Use a sizer to arrange buttons to match screen size
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	// Array of Mines
	nField = new int[nFieldWidth * nFieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWidth; x++)
	{
		for (int y = 0; y < nFieldHeight; y++)
		{
			// create new button
			btn[y * nFieldWidth + x] = new wxButton(this, 10000 + (y * nFieldWidth + x));
			btn[y * nFieldWidth + x]->SetFont(font);
			// Add button to grid sizer
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			// Bind event handler
			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);

			// Default mine value
			nField[y * nFieldWidth + x] = 0;
		}
	}

	// Grid sizer to use
	this->SetSizer(grid);

	// dynamically restructure itself
	grid->Layout();

}

cMain::~cMain()
{
	// wxWidgets handles deletion of its own 'new' items

	// Array of buttons
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Calculate button coordinates
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldHeight;

	if (bFirstClick)
	{
		int mines = 30;

		while (mines)
		{
			// Place mines
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			// check to ensure no mines already at this coordinate
			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}

		bFirstClick = false;
	}

	// Disable the button from being pressed again
	btn[y * nFieldWidth + x]->Enable(false);

	// Check if the user has clicked a button with a mine present
	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox("EXPLOSIONNNNNN!!!! - Game Over!");

		// Reset the game
		bFirstClick = true;
		for(int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
			{
				nField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
	}
	else
	{
		// Count and display how many mines are neighbouring the selected button
		int mine_count = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + j)] == -1)
					{
						mine_count++;
					} 
				}

			}
		}

		// Update button label to display how many mines surrounding the cell
		if (mine_count > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}
