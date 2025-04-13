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
    bool isBatery;
    
    wxStaticText *timerText;
    wxStaticText *timerText2;
    wxStaticText *cpuTemperature;
    wxStaticText *cpu_usage;
    wxStaticText *ram_usage;
    wxStaticText *batery_procent;
    wxStaticText *volume_procent;

    wxPanel *panel;
    wxPanel *cpu_draw;
    wxPanel *cpu_temp;
    wxPanel *ram_draw;
    wxPanel *vs_time;
    wxPanel *konsole_time;
    wxPanel *batery_draw;

    wxTimer timer;

    wxString cpuTemp;
    wxString CPU;
    wxString RAM;
    wxString BATERY;
    wxString BATERY_NUMBER;
    wxString TOTAL_RAM;
    wxString CURRENT_VOLUME;

    wxString remember_CPU;
    wxString remember_temp;
    wxString remember_ram;
    wxString remember_batery;
    wxString remember_volume;

    wxSlider *volume;
    wxSlider *volume2;
    
    mainFrame(const wxString& title);
    
    void volumeFunction2(wxCommandEvent &event);
    void volumeFunction(wxCommandEvent &event);
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void draw(wxPaintEvent &event);
    void drawTime(wxPaintEvent &event);
};

#endif