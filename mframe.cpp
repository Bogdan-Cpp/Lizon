#include <wx/wx.h>
#include <iostream>
#include <cstdlib>
#include "mframe.h"
#include "main.h"

bool isKeyOff = false;

mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(size_x, size_y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)){
    SetBackgroundColour(wxColour(30, 30, 30));
    SetTransparent(230);

    wxPanel *panel = new wxPanel(this, wxID_ANY);
    
    commandLine = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 50), wxSize(300, 40), wxTE_PROCESS_ENTER | wxBORDER_NONE);
    commandLine->SetBackgroundColour(wxColour(50, 50, 50));
    commandLine->SetForegroundColour(wxColour(250, 250, 250));
    commandLine->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxFont font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxCheckBox *keyboard = new wxCheckBox(panel, wxID_ANY, "Keyboard Cleaning  ", wxPoint(200, 120), wxSize(250, 25), wxCHK_CHECKED);
    keyboard->SetFont(font);
    keyboard->Bind(wxEVT_CHECKBOX, &mainFrame::isKeyboardOff, this);
    commandLine->Bind(wxEVT_TEXT_ENTER, &mainFrame::readInput, this);
}
void mainFrame::readInput(wxCommandEvent& event){
    wxString input = commandLine->GetValue();
    if(input == "touchpad off"){
        system("xinput disable 4");
        system("xinput disable 9");
        system("xinput disable 10");
    }
    else if(input == "touchpad on"){
        system("xinput enable 4");
        system("xinput enable 9");
        system("xinput enable 10");
    }
}
void mainFrame::isKeyboardOff(wxCommandEvent& event){
    int id = event.GetId();
    bool checked = ((wxCheckBox*)event.GetEventObject())->IsChecked();
    if(checked){
        system("xinput disable 12");
        system("xinput disable 6");
        system("xinput disable 8");
        system("xinput disable 11");
        system("xinput disable 5");
    }
    else{
        system("xinput enable 12");
        system("xinput enable 6");
        system("xinput enable 8");
        system("xinput enable 11");
        system("xinput enable 5");
    }
}