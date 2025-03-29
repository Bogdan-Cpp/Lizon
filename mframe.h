#ifndef MFRAME_H
#define MFRAME_H

#include <wx/wx.h>
#include <cstdlib>

extern std::string msg;

class mainFrame : public wxFrame{
    public:
    mainFrame(const wxString& title);

    private:
    void isKeyboardOff(wxCommandEvent& event);
};

#endif