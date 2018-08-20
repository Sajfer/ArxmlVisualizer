#include "drawobject.h"
#include "arxmlparser.h"

#define COMPONENT_SIZE_X 200
#define COMPONENT_SIZE_Y 100

DrawObject::DrawObject(const Arxml& arxml) {
    const Composition* root_comp = arxml.getComposition();
    name = root_comp->name;
}
const std::string& DrawObject::getName() const {
    return name;
}
const ArxmlType& DrawObject::getType() const {
    return type;
}
const std::vector<DrawObject*>& DrawObject::getChildren() const {
    return children;
}

void DrawObject::draw(wxDC& dc, int x, int y) const {
    // Draw Rectangle
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen( wxPen(wxColor(0,0,0), 5));
    dc.DrawRectangle(x, y, COMPONENT_SIZE_X, COMPONENT_SIZE_Y);

    // Draw text
    auto name_text = wxString(this->getName());
    wxSize text_size = dc.GetTextExtent(name_text);
    int text_pos_x = x + COMPONENT_SIZE_X/2 - text_size.GetWidth()/2;
    int text_pos_y = y + 10;
    dc.DrawText(name_text, text_pos_x, text_pos_y);

    // Draw Children
}