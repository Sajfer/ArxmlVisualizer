#include "communication_panel.h"
#define BACKGROUND_COLOR wxColor(220, 220, 220)

CommunicationsPanel::CommunicationsPanel(wxWindow* parent): wxPanel(parent, COMMUNICATION_PANEL_ID) {
    SetBackgroundColour(BACKGROUND_COLOR);
};

void CommunicationsPanel::setAvailableInterfaces(std::vector<std::string> interfaces_on_selection) {
}
