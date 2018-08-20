#include "main.h"
#include "drawpane.h"

#include "arxmlparser.h"

IMPLEMENT_APP(ArxmlVizualizer)

static const wxCmdLineEntryDesc cmdLineDesc[] = {
    { wxCMD_LINE_PARAM,  NULL, NULL, "input file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE },
    { wxCMD_LINE_NONE }
};


bool ArxmlVizualizer::OnInit() {

    if (!wxApp::OnInit())
        return false;

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame*) NULL, -1, wxT("Arxml Vizualizer"), wxPoint(50,50), wxSize(800,600));
    drawPane = new DrawPane((wxFrame*) frame);
    sizer->Add(drawPane, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();

    return true;
}

int ArxmlVizualizer::OnRun() {
    Arxml arxml(filePath);

    return 0;
}

void ArxmlVizualizer::OnInitCmdLine(wxCmdLineParser& parser) {
    parser.SetDesc (cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (wxT("-"));
}

bool ArxmlVizualizer::OnCmdLineParsed(wxCmdLineParser& parser) {

    // to get at your unnamed parameters use
    wxArrayString files;
    for (uint i = 0; i < parser.GetParamCount(); i++)
    {
        files.Add(parser.GetParam(i));
    }

    if(files.GetCount() == 0) {
        return false;
    }
    filePath = files.Item(0);

    return true;
}