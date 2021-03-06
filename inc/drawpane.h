#ifndef DRAW_PANE
#define DRAW_PANE
#include<vector>

#include "wx/wx.h"
#include "wx/sizer.h"

#include "drawobject.h"
#include "gui_ids.h"
#include "communication_panel.h"

class DrawPane : public wxPanel {
 
public:
    DrawPane(wxFrame* parent);

    void setDrawObject(DrawObject* draw_object);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void mouseDownLeft(wxMouseEvent& event);
    void mouseUpLeft(wxMouseEvent& event);
    void mouseMoved(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */
 
    DECLARE_EVENT_TABLE()

private:
    wxPoint offset;
    wxPoint last_mouse_pos;
    bool panOk;
    DrawObject* draw_object;
    const DrawObject* getComponentUnderCursor(wxPoint& curser_position);
};
#endif