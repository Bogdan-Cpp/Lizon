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
        wxImage scaledImage = vsIcon.Rescale(70, 70, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(vsIcon);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(50, 600), wxSize(wxDefaultSize));
    }

    wxImage konsole;
    if(konsole.LoadFile("../konsole.png")){
        wxImage scaledImage = konsole.Rescale(70, 70, wxIMAGE_QUALITY_HIGH);
        wxBitmap bitmap(konsole);
        wxStaticBitmap *bitmapControl = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(50, 500), wxSize(wxDefaultSize));
    }

    //time track
    timerText = new wxStaticText(panel, wxID_ANY, wxString::Format("%d m in VSCode", timeSpent), wxPoint(150, 630));
    timerText2 = new wxStaticText(panel, wxID_ANY, wxString::Format("%d m in Konsole", timeSpent2), wxPoint(150, 530));

    cpuTemperature = new wxStaticText(panel, wxID_ANY, wxString::Format("CPU temp %s", cpuTemp), wxPoint(150, 400));
    ram_usage = new wxStaticText(panel, wxID_ANY, wxString::Format("RAM usage: %s", RAM), wxPoint(150, 300));
    cpu_usage = new wxStaticText(panel, wxID_ANY, wxString::Format("CPU usage: %s", CPU), wxPoint(150, 250));
    timer.SetOwner(this);
    Bind(wxEVT_TIMER, &mainFrame::OnTimer, this);
    timer.Start(1000);
    
    //command line
    commandLine = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(150, 50), wxSize(300, 40), wxTE_PROCESS_ENTER | wxBORDER_NONE);
    commandLine->SetBackgroundColour(wxColour(50, 50, 50));
    commandLine->SetForegroundColour(wxColour(250, 250, 250));
    commandLine->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    
    //checkbox
    wxFont font(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxCheckBox *keyboard = new wxCheckBox(panel, wxID_ANY, "Keyboard Cleaning  ", wxPoint(200, 120), wxSize(250, 25), wxCHK_CHECKED);
    keyboard->SetFont(font);
    keyboard->Bind(wxEVT_CHECKBOX, &mainFrame::isKeyboardOff, this);
    
    commandLine->Bind(wxEVT_TEXT_ENTER, &mainFrame::readInput, this);

    cpu_draw = new wxPanel(panel, wxID_ANY, wxPoint(250, 250), wxSize(300, 20));
    cpu_draw->SetBackgroundColour(wxColour(30, 30, 50));
    cpu_draw->Bind(wxEVT_PAINT, &mainFrame::draw, this);
}

void mainFrame::draw(wxPaintEvent &event){
    wxPaintDC dc(cpu_draw);
    dc.SetPen(*wxWHITE_PEN);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    double cpu_value;
    if(remember_CPU.ToDouble(&cpu_value)){
        std::cout << "succes\n";
    }
    else{
        std::cout << "esuat\n";
    }
    dc.DrawRectangle(0, 0, cpu_value * 3, 20);
    temp += 10;
    std::cout << temp << '\n';
}

void mainFrame::readInput(wxCommandEvent& event){
    wxString input = commandLine->GetValue();
    if(input == "touchpad off"){
        system("xinput disable 4");
        system("xinput disable 9");
        system("xinput disable 10");
    }
    else if(input == "touchpad on"){
        system("xinput enable 4");
        system("xinput enable 9");
        system("xinput enable 10");
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
    const char *cmd_cpu_temp = "sensors | grep 'Core 0' | awk '{print $3}' | tr -d '+°C'";
    const char *cmd_cpu = "top -bn1 | grep \"Cpu(s)\" | awk '{print $2 + $4}'";
    const char *cmd_ram = "free -h | awk '/Mem:/ {print $3}'";
    const char *command = "xdotool search --name \"Visual Studio Code\"";
    const char *command2 = "xdotool search --name \"Konsole\"";
    int rezults = system(command);
    int rezults2 = system(command2);
    char read_cpu_temp[128];
    char read_cpu[128];
    char read_ram[128];

    //reda RAM usage 
    std::unique_ptr<FILE, decltype(&pclose)> pipe3(popen(cmd_ram, "r"), pclose); 
    if(!pipe3){
        return;
    }
    while(fgets(read_ram, sizeof(read_ram), pipe3.get()) != nullptr){
        RAM += read_ram;
    }
    if(ram_usage != nullptr){
        ram_usage->SetLabel(wxString::Format("CPU usage: %s", RAM));
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
        cpu_usage->SetLabel(wxString::Format("CPU usage: %s", CPU));
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
        cpuTemperature->SetLabel(wxString::Format("CPU temp: %s", cpuTemp));
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
            timerText->SetLabel(wxString::Format("%d m in VSCode", minutes));
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
            timerText2->SetLabel(wxString::Format("%d m in Konsole", minutes2));
        }
        else{
            std::cerr << "erroare" << '\n';
        }
    }
    cpu_draw->Refresh();
}
