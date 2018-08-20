#include <wx/wx.h>
#include <wx/cmdline.h>

#include "drawpane.h"
#include "drawobject.h"

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

    std::string filePath;
};