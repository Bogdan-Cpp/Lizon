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
    wxPanel *cpu_draw;
    wxTimer timer;
    wxString cpuTemp;
    wxString CPU;
    wxString RAM;
    wxString remember_CPU;
    int temp = 10;
    
    mainFrame(const wxString& title);
    
    void readInput(wxCommandEvent& event);
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void draw(wxPaintEvent &event);
};

#endif
