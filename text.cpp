#include <wx/wx.h>
#include <iostream>
#include "text.h"
#include "main.h"

Text::Text(wxFrame *parent) : wxPanel(parent, wxID_ANY) {}
    
void Text::textDraw(wxPaintEvent &event){
    wxPaintDC text1(this);
    
    wxSize size = GetParent()->GetSize();
    size_x = size.GetWidth();
    size_y = size.GetHeight();

    text1.DrawText("Lizon is a settings app made for Linux", wxPoint((size_x / 2) - 110, size_y / 2));
}

wxBEGIN_EVENT_TABLE(Text, wxPanel)
    EVT_PAINT(Text::textDraw)
wxEND_EVENT_TABLE()