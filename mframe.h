#ifndef MFRAME_H
#define MFRAME_H

#include <wx/wx.h>
#include <cstdlib>

extern bool isKeyOff;
extern int timeSpent;
extern int timeSpent2;
extern int minutes;
extern int minutes2;

class mainFrame : public wxFrame{
    public:
    wxTextCtrl* commandLine;
    wxStaticText *timerText;
    wxStaticText *timerText2;
    wxStaticText *cpuTemperature;
    wxStaticText *cpu_usage;
    wxStaticText *ram_usage;
    wxTimer timer;
    wxString cpuTemp;
    wxString CPU;
    wxString RAM;
    
    mainFrame(const wxString& title);

    void readInput(wxCommandEvent& event);
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
};

#endif
