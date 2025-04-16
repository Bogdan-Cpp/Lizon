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
    int volume_size_x;
    int volume_poz_x;
    int volume_poz_y;
    int volume2_size_x;
    int volume2_poz_x;
    int volume2_poz_y;

    int text_poz_x;
    int text_poz_y;
    int text2_poz_x;
    int text2_poz_y;

    int image_poz_x;
    int image_poz_y;
    int image2_poz_x;
    int image2_poz_y;
    
    wxStaticText *timerText;
    wxStaticText *timerText2;
    wxStaticText *cpuTemperature;
    wxStaticText *cpu_usage;
    wxStaticText *ram_usage;
    wxStaticText *batery_procent;
    wxStaticText *volume_procent;
    wxStaticText *volume_procent2;

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
    wxString CURRENT2_VOLUME;

    wxString remember_CPU;
    wxString remember_temp;
    wxString remember_ram;
    wxString remember_batery;
    wxString remember_volume;
    wxString remember_volume2;

    wxSlider *volume;
    wxSlider *volume2;

    wxStaticBitmap *imageBitmap;
    wxStaticBitmap *imageBitmap2;

    wxString dev_path;
    wxString release_path;
    wxString execPath;
    wxString execDir;
    
    wxString iconPath;
    
    mainFrame(const wxString& title);
    
    void volumeFunction2(wxCommandEvent &event);
    void volumeFunction(wxCommandEvent &event);
    void isKeyboardOff(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    void draw(wxPaintEvent &event);
    void drawTime(wxPaintEvent &event);
};

#endif