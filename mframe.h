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
    wxStaticText *timerText;
    wxStaticText *timerText2;
    wxStaticText *cpuTemperature;
    wxStaticText *cpu_usage;
    wxStaticText *ram_usage;
    wxPanel *cpu_draw;
    wxPanel *cpu_temp;
    wxPanel *ram_draw;
    wxPanel *vs_time;
    wxPanel *konsole_time;
    wxTimer timer;
    wxString cpuTemp;
    wxString CPU;
    wxString RAM;
    wxString remember_CPU;
    wxString remember_temp;
    wxString remember_ram;
    
    mainFrame(const wxString& title);
    
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void draw(wxPaintEvent &event);
    void drawTime(wxPaintEvent &event);
};

#endif