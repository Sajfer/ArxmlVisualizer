#include "communication_panel.h"
#define BACKGROUND_COLOR wxColor(220, 220, 220)
#include <iostream> // Only for simple debugging

CommunicationsPanel::CommunicationsPanel(wxWindow* parent): wxPanel(parent, COMMUNICATION_PANEL_ID) {
    SetBackgroundColour(BACKGROUND_COLOR);

    sizer = new wxBoxSizer(wxVERTICAL);

    wxClientDC dc(this);
    wxString title_str("Communication Paths");

    title_text = new wxStaticText(this,
        COMMUNICATION_PANEL_TITLE_ID,
        title_str);
    sizer->Add(title_text, -1, wxALIGN_CENTRE_HORIZONTAL);

    wxArrayString choices;

    list_box = new wxListBox(this, COMMUNICATION_PANEL_LIST_ID, wxDefaultPosition, wxDefaultSize, choices);

    sizer->Add(list_box, 10, wxEXPAND);
    this->SetSizer(sizer);
    this->Layout();

    list_box->Connect(COMMUNICATION_PANEL_LIST_ID, wxEVT_LEFT_UP, wxMouseEventHandler(CommunicationsPanel::PortSelected), NULL, this);
};

void CommunicationsPanel::PortSelected(wxMouseEvent& WXUNUSED(event)){
    wxArrayInt result;
    this->list_box->GetSelections(result);
    std::cout << result[0] << std::endl;
}

void CommunicationsPanel::setAvailableConnections(std::vector<std::string> interfaces_on_selection) {
    this->interfaces_on_selection = interfaces_on_selection;
    refreshContent();
}

void CommunicationsPanel::refreshContent() {
    list_box->Clear();
    for (auto& choice : interfaces_on_selection) {
        list_box->Append(choice);
    }
}
