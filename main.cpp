#include "main.h"
#include "button.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    Button *btnapp = new Button(wxT("Button"));
    btnapp->Show(true);

    return true;
}