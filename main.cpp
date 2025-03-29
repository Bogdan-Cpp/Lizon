#include <wx/wx.h>
#include <iostream>

float size_x = 1300.f;
float size_y = 750.f;

class Text : public wxPanel{
    public:
    Text(wxFrame *parent) : wxPanel(parent, wxID_ANY) {}

    void textDraw(wxPaintEvent &event){
        wxPaintDC text1(this);
        
        text1.DrawText("Lizon is a powerful settings app", wxPoint((size_x / 2) - 100.f, size_y / 2));
    }

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(Text, wxPanel)
    EVT_PAINT(Text::textDraw)
wxEND_EVENT_TABLE()

class Main : public wxApp {
public:
    virtual bool OnInit() {
        wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Lizon", wxDefaultPosition, wxSize(size_x, size_y));
        Text *panel = new Text(frame);
        
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(Main);