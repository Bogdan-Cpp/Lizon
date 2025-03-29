#include <wx/wx.h>
#include <iostream>

class Text : public wxPanel{
    public:
    Text(wxFrame *parent) : wxPanel(parent, wxID_ANY) {
        wxButton *button = new wxButton(this, wxID_ANY, "Subscribe", wxPoint(500, 10));
    }

    void textDraw(wxPaintEvent &event){
        wxPaintDC text1(this);
        
        text1.DrawText("Hello, world!", wxPoint(100, 100));
        text1.DrawText("Aplicatie", wxPoint(50, 10));
    }

    wxDECLARE_EVENT_TABLE();
};