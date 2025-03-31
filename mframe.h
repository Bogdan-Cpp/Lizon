#ifndef MFRAME_H
#define MFRAME_H

#include <wx/wx.h>
#include <cstdlib>

extern bool isKeyOff;
extern int timeSpent;
extern int minutes;

class mainFrame : public wxFrame{
    public:
    wxTextCtrl* commandLine;
    wxStaticText* timerText;
    wxTimer timer;
    mainFrame(const wxString& title);

    void readInput(wxCommandEvent& event);
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
};

#endif