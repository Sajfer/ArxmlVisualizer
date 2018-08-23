#include <wx/wx.h>
#include <wx/cmdline.h>

#include "drawpane.h"
#include "drawobject.h"
#include "communication_panel.h"

class ArxmlVizualizer : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnRun();
    virtual void OnInitCmdLine(wxCmdLineParser& parser);
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
  private:
    wxFrame* frame;
    DrawPane* drawPane;
    Arxml* model;
    DrawObject* root_draw_object;
    CommunicationsPanel* communication_panel;

    std::string filePath;
};