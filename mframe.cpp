#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>
#include <memory>
#include "mframe.h"
#include "main.h"

bool isKeyOff = false;
int timeSpent = 0;
int timeSpent2 = 0;
int minutes = 0;
int minutes2 = 0;

mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(size_x, size_y), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)){
    SetBackgroundColour(wxColour(30, 30, 30));
    SetTransparent(230);
    
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    wxInitAllImageHandlers();
    
    //imagini
    wxImage vsIcon;
    if(vsIcon.LoadFile("../vscode.png")){
        wxImage scaledImage = vsIcon.Rescale(25, 25, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(vsIcon);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(10, 240), wxSize(wxDefaultSize));
    }

    wxImage konsole;
    if(konsole.LoadFile("../konsole.png")){
        wxImage scaledImage = konsole.Rescale(30, 30, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(konsole);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(10, 280), wxSize(wxDefaultSize));
    }

    wxImage cpu_icon;
    if(cpu_icon.LoadFile("../cpu.png")){
        wxImage scaledImage = cpu_icon.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(cpu_icon);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(-20, 20), wxSize(wxDefaultSize));
    }

    wxImage temp_icon;
    if(temp_icon.LoadFile("../temp.png")){
        wxImage scaledImage = temp_icon.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(temp_icon);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(-20, 60), wxSize(wxDefaultSize));
    }

    wxImage ram_icon;
    if(ram_icon.LoadFile("../ram.png")){
        wxImage scaledImage = ram_icon.Rescale(100, 100, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(ram_icon);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(-20, 100), wxSize(wxDefaultSize));
    }

    //time track
    timerText = new wxStaticText(panel, wxID_ANY, wxString::Format("%d m", timeSpent), wxPoint(360, 245));
    timerText2 = new wxStaticText(panel, wxID_ANY, wxString::Format("%d m", timeSpent2), wxPoint(360, 285));

    cpuTemperature = new wxStaticText(panel, wxID_ANY, wxString::Format("%s", cpuTemp), wxPoint(360, 100));
    ram_usage = new wxStaticText(panel, wxID_ANY, wxString::Format("%s", RAM), wxPoint(360, 140));
    cpu_usage = new wxStaticText(panel, wxID_ANY, wxString::Format("%s", CPU), wxPoint(360, 60));
    batery_procent = new wxStaticText(panel, wxID_ANY, wxString::Format("%s", BATERY), wxPoint(115, 397));

    timer.SetOwner(this);
    Bind(wxEVT_TIMER, &mainFrame::OnTimer, this);
    timer.Start(1000);
    
    //checkbox
    wxFont font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxCheckBox *keyboard = new wxCheckBox(panel, wxID_ANY, "Keyboard Cleaning  ", wxPoint(200, 500), wxSize(250, 25), wxCHK_CHECKED);
    keyboard->SetFont(font);
    keyboard->Bind(wxEVT_CHECKBOX, &mainFrame::isKeyboardOff, this);
    
    //panels1
    cpu_draw = new wxPanel(panel, wxID_ANY, wxPoint(50, 60), wxSize(300, 20));
    cpu_draw->SetBackgroundColour(wxColour(50, 50, 50));
    cpu_draw->Bind(wxEVT_PAINT, &mainFrame::draw, this);

    cpu_temp = new wxPanel(panel, wxID_ANY, wxPoint(50, 100), wxSize(300, 20));
    cpu_temp->SetBackgroundColour(wxColor(50, 50, 50));
    cpu_temp->Bind(wxEVT_PAINT, &mainFrame::draw, this);

    ram_draw = new wxPanel(panel, wxID_ANY, wxPoint(50, 140), wxSize(300, 20));
    ram_draw->SetBackgroundColour(wxColor(50, 50, 50));
    ram_draw->Bind(wxEVT_PAINT, &mainFrame::draw, this);

    batery_draw = new wxPanel(panel, wxID_ANY, wxPoint(50, 400), wxSize(50, 15));
    batery_draw->SetBackgroundColour(wxColor(50, 50, 50));
    batery_draw->Bind(wxEVT_PAINT, &mainFrame::draw, this);

    //panels2
    vs_time = new wxPanel(panel, wxID_ANY, wxPoint(50, 250), wxSize(300, 10));
    vs_time->SetBackgroundColour(wxColor(50, 50, 50));
    vs_time->Bind(wxEVT_PAINT, &mainFrame::drawTime, this);

    konsole_time = new wxPanel(panel, wxID_ANY, wxPoint(50, 290), wxSize(300, 10));
    konsole_time->SetBackgroundColour(wxColor(50, 50, 50));
    konsole_time->Bind(wxEVT_PAINT, &mainFrame::drawTime, this);
}

void mainFrame::drawTime(wxPaintEvent &event){
    wxWindow* source = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!source){return;}

    wxPaintDC dc(source);
    dc.SetPen(*wxWHITE_PEN);
   
    if(source == vs_time){
        wxBrush fill_time(wxColour(0, 128, 255));
        dc.SetBrush(fill_time);
        dc.DrawRoundedRectangle(0, 0, minutes * 3, 10, 3);
    }
    else if(source == konsole_time){
        wxBrush fill_time(wxColour(60, 60, 60));
        dc.SetBrush(fill_time);
        dc.DrawRoundedRectangle(0, 0, minutes2 * 3, 10, 3);
    } 
}

void mainFrame::draw(wxPaintEvent &event){
    wxWindow* source = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!source){return;}
    
    wxPaintDC dc(source);
   
    if(source == cpu_draw){
        dc.SetPen(*wxWHITE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);

        double cpu_value;
        remember_CPU.ToDouble(&cpu_value);
        dc.DrawRectangle(0, 0, cpu_value * 3, 20);
    }
    else if(source == cpu_temp){
        dc.SetPen(*wxWHITE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);

        double temp_value;
        remember_temp.ToDouble(&temp_value);
        dc.DrawRectangle(0, 0, temp_value * 3, 20);
    }
    else if(source == ram_draw){
        dc.SetPen(*wxWHITE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);

        double ram_value;
        remember_ram.ToDouble(&ram_value);
        dc.DrawRectangle(0, 0, ram_value * 3, 20);
    }
    else if(source == batery_draw){
        double batery_value;
        remember_batery.ToDouble(&batery_value);
        
        if(batery_value >= 75){
            dc.SetPen(*wxWHITE_PEN);
            wxBrush fill_time(wxColour(40, 198, 71));
            dc.SetBrush(fill_time);
        }
        else if(batery_value >= 50 && batery_value <= 74){
            dc.SetPen(*wxWHITE_PEN);
            wxBrush fill_time(wxColour(71, 232, 22));
            dc.SetBrush(fill_time); 
        }
        else if(batery_value >= 20 && batery_value <= 49){
            dc.SetPen(*wxWHITE_PEN);
            wxBrush fill_time(wxColour(228, 243, 14));
            dc.SetBrush(fill_time);
        }
        else if(batery_value >= 0 && batery_value <= 19){
            dc.SetPen(*wxWHITE_PEN);
            wxBrush fill_time(wxColour(255, 51, 51));
            dc.SetBrush(fill_time);
        }

        dc.DrawRectangle(0, 0, batery_value / 2, 15);
    }
}

void mainFrame::isKeyboardOff(wxCommandEvent& event){
    int id = event.GetId();
    bool checked = ((wxCheckBox*)event.GetEventObject())->IsChecked();
    if(checked){
        system("xinput disable 12");
        system("xinput disable 6");
        system("xinput disable 8");
        system("xinput disable 11");
        system("xinput disable 5");
    }
    else{
        system("xinput enable 12");
        system("xinput enable 6");
        system("xinput enable 8");
        system("xinput enable 11");
        system("xinput enable 5");
    }
}

void mainFrame::OnTimer(wxTimerEvent& event) {
    const char *cmd_batery = "cat /sys/class/power_supply/BAT0/capacity | awk '{print $1 \"%\"}'";
    const char *cmd_number_batery = "cat /sys/class/power_supply/BAT0/capacity";

    const char *cmd_cpu_temp = "sensors | grep 'Core 0' | awk '{print $3}' | tr -d '+°C'";
    const char *cmd_cpu = "top -bn1 | grep \"Cpu(s)\" | awk '{print $2 + $4}'";
    const char *cmd_ram = "free -h | awk '/Mem:/ {gsub(/[A-Za-z]/, \"\", $3); print $3}'";    const char *command = "xdotool search --name \"Visual Studio Code\"";
    const char *command2 = "xdotool search --name \"Konsole\"";
    int rezults = system(command);
    int rezults2 = system(command2);
    char read_cpu_temp[128];
    char read_cpu[128];
    char read_ram[128];

    char read_batery[128];
    char read_number_batery[128];

    //batery status
    std::unique_ptr<FILE, decltype(&pclose)> batery_pipe(popen(cmd_batery, "r"), pclose); 
    if(!batery_pipe){return;}

    while(fgets(read_batery, sizeof(read_batery), batery_pipe.get()) != nullptr){
        BATERY += read_batery;
    }
    if(ram_usage != nullptr){
        batery_procent->SetLabel(wxString::Format("%s", BATERY));
        BATERY = "";
    }
    
    std::unique_ptr<FILE, decltype(&pclose)> batery_number_pipe(popen(cmd_number_batery, "r"), pclose); 
    if(!batery_number_pipe){return;}
    
    while(fgets(read_number_batery, sizeof(read_number_batery), batery_number_pipe.get()) != nullptr){
        BATERY_NUMBER += read_number_batery;
    }
    if(ram_usage != nullptr){
        remember_batery = BATERY_NUMBER;
        BATERY_NUMBER = "";
    }


    std::unique_ptr<FILE, decltype(&pclose)> pipe3(popen(cmd_ram, "r"), pclose); 
    if(!pipe3){
        return;
    }
    while(fgets(read_ram, sizeof(read_ram), pipe3.get()) != nullptr){
        RAM += read_ram;
    }
    if(ram_usage != nullptr){
        ram_usage->SetLabel(wxString::Format("%s", RAM));
        remember_ram = RAM;
        RAM = "";
    }

    //read CPU usage
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd_cpu, "r"), pclose);
    if(!pipe){
        return;
    }
    while(fgets(read_cpu, sizeof(read_cpu), pipe.get()) != nullptr){
        CPU += read_cpu;
    }
    if(cpu_usage != nullptr){
        cpu_usage->SetLabel(wxString::Format("%s", CPU));
        remember_CPU = CPU;
        CPU = "";
    }

    //read the temperature
    std::unique_ptr<FILE, decltype(&pclose)> pipe2(popen(cmd_cpu_temp, "r"), pclose);
    if(!pipe2) {
        return;
    }
    while(fgets(read_cpu_temp, sizeof(read_cpu_temp), pipe2.get()) != nullptr) {
        cpuTemp += read_cpu_temp;
    }
    if(cpuTemperature != nullptr){
        cpuTemperature->SetLabel(wxString::Format("%s", cpuTemp));
        remember_temp = cpuTemp;
        cpuTemp = "";
    }
    
    //vs code timespent
    if(rezults == 0){
        if(timeSpent == 60){
            minutes += 1;
            timeSpent = 0;
        }
        timeSpent += 1;
        if(timerText != nullptr){
            timerText->SetLabel(wxString::Format("%d m", minutes));
        }
        else{
            std::cerr << "erroare" << '\n';
        }
    }
    else{std::cout << "nu merge";}

    //konsole timespent
    if(rezults2 == 0){
        if(timeSpent2 == 60){
            minutes2 += 1;
            timeSpent2 = 0;
        }
        timeSpent2 += 1;
        if(timerText2 != nullptr){
            timerText2->SetLabel(wxString::Format("%d m", minutes2));
        }
        else{
            std::cerr << "erroare" << '\n';
        }
    }
    cpu_draw->Refresh();
    cpu_temp->Refresh();
    ram_draw->Refresh();
    batery_draw->Refresh();
    vs_time->Refresh();
    konsole_time->Refresh();
}