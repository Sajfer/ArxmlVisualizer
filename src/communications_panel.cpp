#include "communication_panel.h"
#define BACKGROUND_COLOR wxColor(220, 220, 220)

CommunicationsPanel::CommunicationsPanel(wxWindow* parent): wxPanel(parent, COMMUNICATION_PANEL_ID) {
    SetBackgroundColour(BACKGROUND_COLOR);
    interfaces_on_selection.push_back(std::string("example1"));
    interfaces_on_selection.push_back(std::string("example2"));
    interfaces_on_selection.push_back(std::string("example3"));

    sizer = new wxBoxSizer(wxVERTICAL);

    wxClientDC dc(this);
    wxString title_str("Communication Paths");

    title_text = new wxStaticText(this,
        COMMUNICATION_PANEL_TITLE_ID,
        title_str);
    title_text->SetWindowStyle(wxALIGN_CENTRE_HORIZONTAL);

    sizer->Add(title_text, 1, wxALIGN_CENTRE_HORIZONTAL);
    this->SetSizer(sizer);
    this->Layout();
};

void CommunicationsPanel::setAvailableInterfaces(std::vector<std::string> interfaces_on_selection) {
    this->interfaces_on_selection = interfaces_on_selection;
}

void CommunicationsPanel::refreshContent() {

}