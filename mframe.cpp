#include <wx/wx.h>
#include <iostream>
#include "mframe.h"
#include "main.h"

mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    SetSize(size_x, size_y);

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxCheckBox *keyboard = new wxCheckBox(panel, wxID_ANY, "Keyboard OFF", wxPoint((size_x / 2) - 100.f, size_y / 2), wxDefaultSize, wxALIGN_RIGHT);
}