#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>
#include <iostream>

extern float size_x;
extern float size_y;

class Main : public wxApp {
    public:
    virtual bool OnInit();
};

#endif