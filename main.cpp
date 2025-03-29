#include <wx/wx.h>
#include <iostream>
#include "main.h"
#include "text.h"

float size_x = 1300.f;
float size_y = 750.f;

bool Main::OnInit() {
    wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Lizon", wxDefaultPosition, wxSize(size_x, size_y));
    Text *panel = new Text(frame);

    frame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);