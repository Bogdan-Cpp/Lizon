#ifndef MFRAME_H
#define MFRAME_H

#include <wx/wx.h>
#include <cstdlib>

extern bool isKeyOff;

class mainFrame : public wxFrame{
    public:
    wxTextCtrl* commandLine;
    mainFrame(const wxString& title);

    void readInput(wxCommandEvent& event);
    void isKeyboardOff(wxCommandEvent& event);
};

#endif