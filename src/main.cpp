#include "main.h"
#include "drawpane.h"

IMPLEMENT_APP(ArxmlVizualizer)

bool ArxmlVizualizer::OnInit()
{

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame*) NULL, -1, wxT("Arxml Vizualizer"), wxPoint(50,50), wxSize(800,600));
    drawPane = new DrawPane((wxFrame*) frame);
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();

    return true;
}