#include "drawpane.h"
#include <iostream>

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(DrawPane::mouseMoved)
 EVT_LEFT_DOWN(DrawPane::mouseDown)
 EVT_LEFT_UP(DrawPane::mouseReleased)
 EVT_RIGHT_DOWN(DrawPane::rightClick)
 EVT_LEAVE_WINDOW(DrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(DrawPane::keyPressed)
 EVT_KEY_UP(DrawPane::keyReleased)
 EVT_MOUSEWHEEL(DrawPane::mouseWheelMoved)
 */
 
// catch paint events
EVT_PAINT(DrawPane::paintEvent)
EVT_MOTION(DrawPane::mouseMoved)
EVT_LEFT_DOWN(DrawPane::mouseDownLeft)
EVT_LEFT_UP(DrawPane::mouseUpLeft)
EVT_KEY_DOWN(DrawPane::keyPressed)
END_EVENT_TABLE()


// some useful events
/*
 void DrawPane::mouseMoved(wxMouseEvent& event) {}
 void DrawPane::mouseDown(wxMouseEvent& event) {}
 void DrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void DrawPane::mouseReleased(wxMouseEvent& event) {}
 void DrawPane::rightClick(wxMouseEvent& event) {}
 void DrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void DrawPane::keyPressed(wxKeyEvent& event) {}
 void DrawPane::keyReleased(wxKeyEvent& event) {}
 */
 
DrawPane::DrawPane(wxFrame* parent) : wxPanel(parent), panOk(false) {
    DrawObject* d_o = new DrawObject("Name", ArxmlType::component);
    this->draw_objects.push_back(d_o);
}

void DrawPane::mouseDownLeft(wxMouseEvent& event) {
    this->last_mouse_pos = (wxGetMousePosition() - this->GetScreenPosition());
    this->panOk = true;
}
void DrawPane::mouseUpLeft(wxMouseEvent& event) {
    this->panOk = false;
}

void DrawPane::mouseMoved(wxMouseEvent& event) {
    if (!this->panOk && !event.Dragging()) {
        return;
    }

    wxPoint mouse_pos = (wxGetMousePosition() - this->GetScreenPosition());
    this->offset += this->last_mouse_pos - mouse_pos;
    this->last_mouse_pos = mouse_pos;
    this->Refresh();
}

void DrawPane::keyPressed(wxKeyEvent& event) {
    if (!this->panOk && event.GetKeyCode() == 67) {
        this->offset.x = 0;
        this->offset.y = 0;
        this->Refresh();
    }
}
 
/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */
 
void DrawPane::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}
 
/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void DrawPane::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}
 
/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */
void DrawPane::render(wxDC&  dc) {
    for (auto current = this->draw_objects.begin(), end = this->draw_objects.end(); current != end; current++) {
        auto draw_object = *current;
        int position_x = this->offset.x + 100;
        int position_y = this->offset.y + 100;
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetPen( wxPen( wxColor(0,0,0), 5));
        dc.DrawRectangle( position_x, position_y, 50, 50);
        dc.DrawText(wxString(draw_object->getName()), position_x, position_y);
    }
}