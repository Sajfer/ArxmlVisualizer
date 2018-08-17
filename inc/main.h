#include <wx/wx.h>
#include "drawpane.h"

class ArxmlVizualizer : public wxApp
{
  public:
    virtual bool OnInit();
  private:
    wxFrame* frame;
    DrawPane* drawPane;
};