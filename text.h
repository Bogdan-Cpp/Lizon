#ifndef TEXT_H
#define TEXT_H

#include <wx/wx.h>

class Text : public wxPanel{
    public:
    Text(wxFrame *parent);

    void textDraw(wxPaintEvent &event);

    wxDECLARE_EVENT_TABLE();
};

#endif