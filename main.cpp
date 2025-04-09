#include <wx/wx.h>
#include <iostream>
#include <cstdlib>
#include "main.h"
#include "mframe.h"

float size_x = 410;
float size_y = 500.f;

bool Main::OnInit() {
    mainFrame *frame = new mainFrame("Lizon");

    frame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);