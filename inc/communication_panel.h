#ifndef COMMUNICATION_PANE
#define COMMUNICATION_PANE
#include <wx/wx.h>

#include <vector>
#include <string>

#include "gui_ids.h"

class CommunicationsPanel: public wxPanel {
    public:
    CommunicationsPanel(wxWindow* parent);
    void setAvailableInterfaces(std::vector<std::string> interfaces_on_selection);
    void refreshContent();
    private:
    std::vector<std::string> interfaces_on_selection;
    wxStaticText* title_text;
    wxListBox* list_box;
    wxBoxSizer* sizer;
};
#endif