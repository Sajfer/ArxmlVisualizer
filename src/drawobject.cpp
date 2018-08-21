#include "drawobject.h"
#include "arxmlparser.h"

#define COMPONENT_SIZE_X 200
#define COMPONENT_SIZE_Y 100
#define COMPONENT_PADDING_X 50
#define COMPONENT_PADDING_Y 25

DrawObject::DrawObject(const Arxml& arxml) {
    const Composition* root_comp = arxml.getComposition();
    name = root_comp->name;

    for (auto &component : root_comp->components) {
        addChild(new DrawObject(component));
    }
}

DrawObject::DrawObject(Component component) {
    name = component.name;
}

void DrawObject::addChild(DrawObject* child) {
    children.push_back(child);
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

struct RectangleSize {
    int x;
    int y;
    int nbr_row_col;
};

RectangleSize calculateRectangleSize(const DrawObject& draw_object, int text_height) {
    int nbr_children = draw_object.getChildren().size();
    int iRoot = static_cast<int>(sqrt(static_cast<float>(nbr_children)) + .5f); // Calculate the closest integer square root

    // Ensure we can always fit the number of children into the packaged structure
    if (iRoot*iRoot < nbr_children)
        iRoot++;

    RectangleSize rect_size = RectangleSize {COMPONENT_SIZE_X, COMPONENT_SIZE_Y, iRoot};

    if (iRoot > 0) {
        rect_size.x = iRoot*COMPONENT_SIZE_X + (iRoot+1)*COMPONENT_PADDING_X;
        rect_size.y = iRoot*COMPONENT_SIZE_Y + (iRoot+1)*COMPONENT_PADDING_Y + text_height;
    }
    return rect_size;
}

void DrawObject::draw(wxDC& dc, int x, int y) const {
    // Define name, text size and rectangle size
    auto name_text = wxString(this->getName());
    wxSize text_size = dc.GetTextExtent(name_text);
    auto rect_size = calculateRectangleSize(*this, text_size.GetHeight());

    // Draw Rectangle
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetPen( wxPen(wxColor(0,0,0), 5));
    dc.DrawRectangle(x, y, rect_size.x, rect_size.y);

    // Draw text
    int text_pos_x = x + rect_size.x/2 - text_size.GetWidth()/2;
    int text_pos_y = y + 10;
    dc.DrawText(name_text, text_pos_x, text_pos_y);

    // Draw Children
    int child_y = -1;
    for (uint i = 0; i < children.size(); ++i) {
        DrawObject* child = children[i];
        int child_x = i%rect_size.nbr_row_col;
        if (child_x == 0)
            child_y++;

        int x_pos = x + COMPONENT_PADDING_X + (COMPONENT_PADDING_X + COMPONENT_SIZE_X)*child_x;
        int y_pos = y + text_size.GetHeight() + COMPONENT_PADDING_Y + (COMPONENT_PADDING_Y + COMPONENT_SIZE_Y)*child_y;

        child->draw(dc, x_pos, y_pos);
    }
}