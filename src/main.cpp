#include "main.h"
#include "arxmlparser.h"
#include "communication_panel.h"

IMPLEMENT_APP(ArxmlVizualizer)

static const wxCmdLineEntryDesc cmdLineDesc[] = {
    { wxCMD_LINE_PARAM,  NULL, NULL, "input file", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE },
    { wxCMD_LINE_NONE }
};

bool ArxmlVizualizer::OnInit() {

    if (!wxApp::OnInit())
        return false;

    frame = new wxFrame((wxFrame*) NULL, -1, wxT("Arxml Vizualizer"), wxPoint(50,50), wxSize(800,600));
    
    wxBoxSizer* sizer_frame = new wxBoxSizer(wxHORIZONTAL);
    drawPane = new DrawPane(frame);
    communication_panel = new CommunicationsPanel(frame);

    sizer_frame->Add(drawPane, 4, wxEXPAND);
    sizer_frame->Add(communication_panel, 1, wxEXPAND);

    frame->SetSizer(sizer_frame);
    frame->SetAutoLayout(true);
    frame->Show();

    return true;
}

int ArxmlVizualizer::OnRun() {

    model = new Arxml(filePath);

    root_draw_object = new DrawObject(*model);

    drawPane->setDrawObject(root_draw_object);

    if (!wxApp::OnRun())
        return 0;

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
    for (uint i = 0; i < parser.GetParamCount(); i++) {
        files.Add(parser.GetParam(i));
    }

    if(files.GetCount() == 0) {
        return false;
    }
    filePath = files.Item(0);

    return true;
}