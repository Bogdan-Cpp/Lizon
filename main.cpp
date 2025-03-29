#include <wx/wx.h>
#include <iostream>
#include "main.h"
#include "mframe.h"

float size_x = 1300.f;
float size_y = 750.f;

bool Main::OnInit() {
    mainFrame *frame = new mainFrame("Lizon");

    frame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);