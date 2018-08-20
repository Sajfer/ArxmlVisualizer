#include <wx/wx.h>
#include <wx/cmdline.h>

#include "drawpane.h"

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

    std::string filePath;
};