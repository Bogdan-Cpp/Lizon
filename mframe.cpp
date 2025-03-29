#include <wx/wx.h>
#include <iostream>
#include <cstdlib>
#include "mframe.h"
#include "main.h"

std::string msg = "Keyboard ON";

mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title){
    SetSize(size_x, size_y);

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxCheckBox *keyboard = new wxCheckBox(panel, wxID_ANY, msg, wxPoint((size_x / 2) - 100.f, size_y / 2), wxDefaultSize, wxALIGN_RIGHT);

    keyboard->Bind(wxEVT_CHECKBOX, &mainFrame::isKeyboardOff, this);
}

void mainFrame::isKeyboardOff(wxCommandEvent& event){
    bool checked = ((wxCheckBox*)event.GetEventObject())->IsChecked();

    if(checked){
        system("xinput disable 12");
        msg = "Keyboard OFF";
    }
    else{
        system("xinput enable 12");
        msg = "Keyboard ON";
    }

    wxCheckBox *keyboard = (wxCheckBox*)event.GetEventObject();
    keyboard->SetLabel(msg);
}