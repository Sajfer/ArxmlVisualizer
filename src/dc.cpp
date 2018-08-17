// class MyApp: public wxApp
// {
//     bool OnInit();
 
//     wxFrame *frame;
//     BasicDrawPane * drawPane;
// public:
 
// };
 
// IMPLEMENT_APP(MyApp)
 
 
// bool MyApp::OnInit()
// {
//     wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
//     frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
 
//     drawPane = new BasicDrawPane( (wxFrame*) frame );
//     sizer->Add(drawPane, 1, wxEXPAND);
 
//     frame->SetSizer(sizer);
//     frame->SetAutoLayout(true);
 
//     frame->Show();
//     return true;
// } 