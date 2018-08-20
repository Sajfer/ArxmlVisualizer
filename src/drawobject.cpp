#include "drawobject.h"

DrawObject::DrawObject(const char* name, ArxmlType type) {
    this->name = std::string(name);
    this->type = type;
}
const std::string& DrawObject::getName() {
    return this->name;
}
const ArxmlType& DrawObject::getType() {
    return this->type;
}
const std::vector<DrawObject*>& DrawObject::getChildren() {
    return this->children;
}

void DrawObject::draw(wxDC& dc, int x, int y) {
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen( wxPen(wxColor(0,0,0), 5));
    dc.DrawRectangle(x, y, 200, 200);
    dc.DrawText(wxString(this->getName()), x, y);
}